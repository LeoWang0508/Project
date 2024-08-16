# -*- coding: utf-8 -*-
"""
Created on Sat Jan  8 14:49:02 2022

@author: user
"""

#import packages
import cv2
import imutils as im
from matplotlib import pyplot as plt
import numpy as np
import pytesseract
import tkinter as tk 
from tkinter.filedialog import askopenfilename, asksaveasfilename
from PIL import Image, ImageTk

interface = tk.Tk()
interface.title('API 61047055S')
interface.geometry("900x700")
pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"
#開啟圖片
def Open_picture():
    global filename
    #圖片路徑
    filename = askopenfilename(title="選擇圖片",filetypes = ([("All files", "*"),("JPEG", "*.jpg"),("PNG", "*.png"),("BMP", "*.BMP"),("PPM", "*.ppm")]))
    nametext1 = filename.split("/")[-1]
    nametext2 = nametext1.split(".")[-1]
    if nametext2 not in {'jpg','png','BMP','ppm'}:
        Label.config(text = "不支持該檔案格式")
        label.configure(image="")
        label2.configure(image="")
        label3.configure(image="")    
        
    else:
        label3.configure(image="")    
        #載入圖片
        global img, img_gray
        img = cv2.imdecode(np.fromfile(filename,dtype=np.uint8),cv2.IMREAD_COLOR)

        #size[0]是高 size[1]是寬
        global size
        size = img.shape
        Label.config(text = "影像格式: "+ str(nametext2) +"檔, " + "影像大小:" + str(size[1]) + "x" + str(size[0]))
        #BGR轉RGB
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        #輸出檔準備
        global img_pil_real
        img_pil_real = Image.fromarray(img)
        
        #resize 
        h = float(500 / size[0])
        w = float(400 / size[1])
        factor = min(h, w)

        size_0 = float(size[0]*factor)
        size_1 = float(size[1]*factor)
        
        img = cv2.resize(img,(int(size_1),int(size_0)))
        #載入PIL格式
        global img_pil
        img_pil = Image.fromarray(img)
        #載入ImageTk
        
        photo = ImageTk.PhotoImage(img_pil)
        #label顯示圖片
        label.configure(image=photo)
        label.image = photo
        label.place(x = 0, y = 150)
    
        label2.configure(image=photo)
        label2.image = photo
        label2.place(x = 450, y = 150)
        
#儲存圖片
def Save_picture(img):
    filename = asksaveasfilename(title = "選擇儲存檔案位置", filetypes = ([("All files", "*"),("JPEG", "*.jpg"),("PNG", "*.png"),("BMP", "*.BMP"),("PPM", "*.ppm")]), defaultextension = "*.*")
    if filename:
        img.save(filename)       
        
def license_plate(filename):
    # Read the image file
    image = np.array(img)

    # Resize the image - change width to 500
    newwidth = 500#
    #image = im.resize(image, width=newwidth)#
    image = cv2.resize(image,(600,400))
    # RGB to Gray scale conversion
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)#

    # Noise removal with iterative bilateral filter(removes noise while preserving edges)
    d, sigmaColor, sigmaSpace = 13,15,15 #11 17 17
    filtered_img = cv2.bilateralFilter(gray, d, sigmaColor, sigmaSpace)

    # Find Edges of the grayscale image
    lower, upper = 30, 200 #170 200
    edged = cv2.Canny(filtered_img, lower, upper)

    # Find contours based on Edges
    cnts,hir = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    cnts=sorted(cnts, key = cv2.contourArea, reverse = True)[:10]
    NumberPlateCnt = None

    # loop over our contours to find the best possible approximate contour of number plate
    count = 0
    NumberPlateCnt=[]
    for c in cnts:
        peri = cv2.arcLength(c, True)
        #s = show()
        s = 1
        epsilon = s * 0.018 * peri #0.01
        approx = cv2.approxPolyDP(c, epsilon, True)
        
        if len(approx) == 4:  # Select the contour with 4 corners
            NumberPlateCnt = approx #This is our approx Number Plate Contour
            break

    if len(NumberPlateCnt):
        cv2.drawContours(image, [NumberPlateCnt], -1, (255,0,0), 2)

        mask = np.zeros(gray.shape,np.uint8)
        new_image = cv2.drawContours(mask,[NumberPlateCnt],0,255,-1)
        new_image = cv2.bitwise_and(image,image,mask=mask)

        (x, y) = np.where(mask == 255)
        (topx, topy) = (np.min(x), np.min(y))
        (bottomx, bottomy) = (np.max(x), np.max(y))
        Cropped = gray[topx:bottomx+1, topy:bottomy+1]
        
        #ocr
        h = float(500 / size[0])
        w = float(400 / size[1])
        factor = min(h, w)

        size_0 = float(size[0]*factor)
        size_1 = float(size[1]*factor)

        Cropped = cv2.cvtColor(Cropped, cv2.COLOR_BGR2RGB)    
        blur_img = cv2.GaussianBlur(Cropped, (0, 0), 15)     
        Cropped = cv2.addWeighted(Cropped, 1.5, blur_img, -0.5, 0)

        text = pytesseract.image_to_string(Cropped, lang='eng', config='--psm 8 --oem 3 -c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789')
        
        #resize       
        image = cv2.resize(image,(int(size_1),int(size_0)))   
    
        global img_pil_real
        img_pil = Image.fromarray(image)
        img_pil_real =  Image.fromarray(image)
        photo = ImageTk.PhotoImage(img_pil)          
        label2.configure(image=photo)
        label2.image = photo
        label2.place(x = 450, y = 150)
        
        img_pil = Image.fromarray(Cropped)
        photo = ImageTk.PhotoImage(img_pil) 
        label3.configure(image=photo)
        label3.image = photo
        label3.place(x = 100, y = 550)
        
    else:   
        text = "找不到車牌"
        
    text = "車牌號碼: " + text
    Label2.config(text = text)
    
#s1 = tk.Scale(interface, from_=1, to=20, orient="horizontal")
#s1.place(x=450, y= 0)

#def show():
#    return s1.get()

#按鈕 布局
input_btn = tk.Button(interface,text="選擇檔案",bg="sky blue", font=('Arial',12),width = 15, height = 2, command = Open_picture)
input_btn.place(x=0,y=0) 

output_btn = tk.Button(interface,text="儲存檔案",bg="springgreen", font=('Arial',12),width = 15, height = 2, command = lambda : Save_picture(img_pil_real))
output_btn.place(x=290,y=0) 

car_btn = tk.Button(interface,text="車牌辨識",bg="#ED9121", font=('Arial',12),width = 15, height = 2, command = lambda : license_plate(filename))
car_btn.place(x=145,y=0) 

#input圖片
label = tk.Label(interface,image="")
label.pack()

#output圖片
label2 = tk.Label(interface,image="")
label2.pack()

label3 = tk.Label(interface,image="")
label3.pack()

#訊息欄位
Label = tk.Label(interface, text = "", font=('Arial',20))
Label.place(x = 0, y = 50)

Label2 = tk.Label(interface, text = "", font=('Arial',20))
Label2.place(x = 450, y = 600)

#資訊說明欄
label_text = tk.Label(interface,text="輸入圖片",bg="sky blue", font=('Arial',12),relief="solid")
label_text.place(x = 0, y = 120)
label_text2 = tk.Label(interface,text="輸出圖片",bg="springgreen", font=('Arial',12), relief="solid")
label_text2.place(x =450, y = 120)

interface.mainloop()