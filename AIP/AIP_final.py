# -*- coding: utf-8 -*-
"""
Created on Sat Dec  4 16:01:56 2021

@author: user
"""
import tkinter as tk  
import cv2
from tkinter.filedialog import askopenfilename, asksaveasfilename
import numpy as np
from PIL import Image, ImageTk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
from random import uniform

#宣告
interface = tk.Tk()
#標題
interface.title('API 61047055S')
#視窗大小
interface.geometry("1120x900")

global flag, text_flag
flag = 0
text_flag = 0

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
    else:
        label_text.config(text='輸入圖片')
        label_text2.config(text='輸出圖片')
        #載入圖片
        img = cv2.imdecode(np.fromfile(filename,dtype=np.uint8),cv2.IMREAD_COLOR)
        #resize後的灰階圖片 img_gray
        global img_gray
        img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        #清空
        global flag 
        if flag == 2:
            delt2()
            delt()  
            flag = 0
        elif flag:
            delt() 
            flag = 0
        #size[0]是高 size[1]是寬
        size = img_gray.shape
        Label.config(text = "影像格式: "+ str(nametext2) +"檔, " + "影像大小:" + str(size[1]) + "x" + str(size[0]))

        #輸出檔準備
        global img_pil_real
        img_pil_real = Image.fromarray(img_gray)
        
        #resize 
        h = float(500 / size[0])
        w = float(300 / size[1])

        factor = min(h, w)

        size_0 = float(size[0]*factor)
        size_1 = float(size[1]*factor)
        
        img_gray = cv2.resize(img_gray,(int(size_1),int(size_0)))
        #載入PIL格式
        global img_pil
        img_pil = Image.fromarray(img_gray)
        #載入ImageTk
        photo = ImageTk.PhotoImage(img_pil)
        #label顯示圖片
        label.configure(image=photo)
        label.image = photo
        label.place(x = 0, y = 150)
        
        label2.configure(image=photo)
        label2.image = photo
        label2.place(x = 550, y = 150)

#儲存圖片
def Save_picture(img):
    filename = asksaveasfilename(title = "選擇儲存檔案位置", filetypes = ([("All files", "*"),("JPEG", "*.jpg"),("PNG", "*.png"),("BMP", "*.BMP"),("PPM", "*.ppm")]), defaultextension = "*.*")
    if filename:
        img.save(filename)
    
#畫直方圖
def hist(filename, minimum, maximum, points, eq):  
    if eq != -1:
        label_text.config(text='輸入圖片')
        label_text2.config(text='輸出圖片')

    #消除figure用的flag
    global flag

    if flag == 2:
        label2.configure(image="")
        delt2() 
        delt() 
        flag = 0
    elif eq != 2:
        label2.configure(image="")
        if flag:   
            delt() 
            flag = 0
    flag = 1
    #灰階
    gray_graph = np.array(filename)
    if eq == 0:
        global img_pil
        img_pil = Image.fromarray(img_gray)
        #載入ImageTk
        photo = ImageTk.PhotoImage(img_pil)
        #label顯示圖片
        label.configure(image=photo)
        label.image = photo
        label.place(x = 0, y = 150)    
    
    #清空圖片
    #histogram 直方圖(gray)
    global figure
    figure = Figure(figsize=(5,3),dpi=100)
    plot = figure.add_subplot(1,1,1)

    x = np.linspace(minimum, maximum, points)
    y = np.zeros(points)
    for level in range(0,points-1):      
        point = (gray_graph == x[level])
        y[level] = point.sum()
    plot.bar(x,y)
    
    global toolbar
    if eq != 2:
        global canvas
        canvas = FigureCanvasTkAgg(figure,interface)
        canvas.draw()
        canvas.get_tk_widget().place(x = 550, y = 150)
        toolbar = NavigationToolbar2Tk(canvas, interface) 
        toolbar.place(x = 550, y = 500)
        toolbar.update()
    else:
        global canvas2
        canvas2 = FigureCanvasTkAgg(figure,interface)
        canvas2.draw()
        canvas2.get_tk_widget().place(x = 550, y = 450)
        toolbar.destroy()
        toolbar = NavigationToolbar2Tk(canvas2, interface) 
        toolbar.place(x = 550, y = 750)
        toolbar.update() 
        flag = 2
    if eq == 1:
        hist_equal(filename, minimum, maximum, points, y)

def hist_equal(filename, minimum, maximum, points, y):

    gray_graph = np.array(filename)
    size = gray_graph.shape
    label2.configure(image="")
    
    yc = np.zeros(points)
    y_min = 0
    yc[0] = y[0]
    for level in range(1,points-1):  
        yc[level] = yc[level-1] + y[level]
    
    H_min = yc[y_min]
    T = np.zeros(points)
    for level in range(0,points-1): 
        T[level] = np.round((yc[level]-H_min)/(size[0]*size[1]-H_min)*255)
    
    for i in range (0,size[0]):
        for j in range (0,size[1]):       
            gray_graph[i,j] = T[int(gray_graph[i,j])]
    
    global img_gray
    img_gray = gray_graph
    #輸出檔準備
    global img_pil_real
    img_pil_real = Image.fromarray(gray_graph)
    img_pil = Image.fromarray(gray_graph)
    #載入ImageTk
    photo = ImageTk.PhotoImage(img_pil)    
    label2.configure(image=photo)
    label2.image = photo
    label2.place(x = 0, y = 450)

    hist(gray_graph, minimum, maximum, points, 2)
    
#刪除畫布    
def delt():
    canvas.get_tk_widget().destroy()
    toolbar.destroy()
    
def delt2():
    canvas2.get_tk_widget().destroy()

#sigma輸入
def button_event():
    global myentry
    if myentry.get() == '':
        tk.messagebox.showerror('message', '未輸入數字')
    elif int(myentry.get()) > 60:
        tk.messagebox.showerror('message', '請輸入小於60的數字')
    elif int(myentry.get()) < 0:
        tk.messagebox.showerror('message', '請輸入大於0的數字')
        
def validate(P):
    if str.isdigit(P) or P == '':
        return True
    else:
        return False

#noise
def noise(filename):
    label_text.config(text='輸出圖片')
    label_text2.config(text='高斯白雜訊直方圖')
    global flag
    if flag == 2:
        delt2()
        delt()  
        flag = 0
    elif flag:
        delt() 
        flag = 0
    #灰階圖片
    gray_graph = np.array(filename)
    
    #重新帶入input圖片
    global img_pil
    img_pil = Image.fromarray(gray_graph)
    #載入ImageTk
    photo = ImageTk.PhotoImage(img_pil)
    #label顯示圖片
    label.configure(image=photo)
    label.image = photo
    label.place(x = 0, y = 150)  
    
    #清空圖片  
    label.configure(image="")   
    label2.configure(image="")
    
    #修改灰階圖片 加入高斯白雜訊
    #size[0]是高 size[1]是寬
    height, width = gray_graph.shape

    Gaussian_graph = np.zeros(shape = (height, width))
    Gaussian_hist = np.zeros(shape = (height, width))
    #邊界不用處理
    #得到sigma
    sigma = int(myentry.get())
    if (width % 2) == 0:
        for i in range(0, height):
            for j in range(0, width, 2):
                phi = uniform(0,1)
                r = uniform(0,1)
                z1 = sigma*np.cos(2*np.pi*phi)*np.sqrt((-2)*np.log(r))
                z2 = sigma*np.sin(2*np.pi*phi)*np.sqrt((-2)*np.log(r))
                Gaussian_hist[i, j] = z1
                Gaussian_hist[i, j+1] = z2
                Gaussian_graph[i, j] = np.round(gray_graph[i, j] + z1)
                Gaussian_graph[i, j+1] = np.round(gray_graph[i, j+1] + z2)
    #要處理邊界
    else:
        for i in range(0, height):
            for j in range(0, width-1, 2) :
                phi = uniform(0,1)
                r = uniform(0,1)
                z1 = sigma*np.cos(2*np.pi*phi)*np.sqrt((-2)*np.log(r))
                z2 = sigma*np.sin(2*np.pi*phi)*np.sqrt((-2)*np.log(r))
                Gaussian_hist[i, j] = z1
                Gaussian_hist[i, j+1] = z2
                Gaussian_graph[i, j] = np.round(gray_graph[i, j] + z1)
                Gaussian_graph[i, j+1] = np.round(gray_graph[i, j+1] + z2)
            phi = uniform(0,1)
            r = uniform(0,1)              
            z1 = sigma*np.cos(2*np.pi*phi)*np.sqrt((-2)*np.log(r)) 
            Gaussian_hist[i, width-1] = z1
            Gaussian_graph[i, width-1] = np.round(gray_graph[i, width-1] + z1)    
    #矯正
    for i in range(0, height):
        for j in range(0, width) :
            if Gaussian_graph[i, j] > 255:
                Gaussian_graph[i, j] = 255
            elif Gaussian_graph[i, j] <= 0:
                Gaussian_graph[i, j] = 0
                
    global img_gray
    img_gray = Gaussian_graph
    global img_pil_real
    img_pil = Image.fromarray(Gaussian_graph)
    img_pil_real = img_pil.convert("L")
    photo = ImageTk.PhotoImage(img_pil)
    #label顯示圖片
    label.configure(image=photo)
    label.image = photo
    label.place(x = 0, y = 150)
    
    #畫直方圖
    #Gaussian_hist_around = np.around(Gaussian_hist, decimals=1)
    Gaussian_hist_around = np.around(Gaussian_hist)
    hist(Gaussian_hist_around , -250, 250, 501, -1)
        
def button_event2():
    global myentry2
    if myentry2.get() == '':
        tk.messagebox.showerror('message', '未輸入數字')
    elif int(myentry2.get()) > 9:
        tk.messagebox.showerror('message', '請輸入小於9的數字')
    elif int(myentry2.get()) < 1:
        tk.messagebox.showerror('message', '請輸入大於1的數字')

def harr_dwt(filename):
    label_text.config(text='輸入圖片')
    label_text2.config(text='輸出圖片')
    gray = np.array(filename)
    
    #重新帶入input圖片
    global img_pil
    img_pil = Image.fromarray(gray)
    #載入ImageTk
    photo = ImageTk.PhotoImage(img_pil)
    #label顯示圖片
    label.configure(image=photo)
    label.image = photo
    label.place(x = 0, y = 150)   
    
    gray = cv2.resize(gray,(512,512))  
    

    #消除figure用的flag
    label2.configure(image="")
    global flag
    if flag == 2:
        delt2()
        delt()  
        flag = 0
    elif flag:
        delt() 
        flag = 0
    global temp
    temp = []
    #得到圈數
    times = int(myentry2.get())
    harr_img = dwt(gray, times)

    for i in range(times):
        #LL = harr_img.pop(0)  LH = harr_img.pop(0)  HL = harr_img.pop(0)  HH = harr_img.pop(0)
        merge1 = np.concatenate((harr_img.pop(0),harr_img.pop(0)), axis=1)
        merge2 = np.concatenate((harr_img.pop(0),harr_img.pop(0)), axis=1)
        merge = np.concatenate((merge1,merge2), axis=0)
        harr_img.insert(0, merge)
        
    h = float(500 / merge.shape[0])
    w = float(300 / merge.shape[1])

    factor = min(h, w)

    size_0 = float(merge.shape[0]*factor)
    size_1 = float(merge.shape[1]*factor)
        
    merge = cv2.resize(merge,(int(size_1),int(size_0)))
    global img_gray
    img_gray = merge
    global img_pil_real
    img_pil = Image.fromarray(merge)
    img_pil_real = img_pil.convert("L")
    photo = ImageTk.PhotoImage(img_pil)    
    label2.configure(image=photo)
    label2.image = photo
    label2.place(x = 550, y = 150)
    
def dwt(gray, times):
    #右下左下右上左上
    coe = ([1, -1, -1, 1], [1, -1, 1, -1], [1, 1, -1, -1], [1, 1, 1, 1])
    H = int(gray.shape[0]/2)
    W = int(gray.shape[1]/2)

    for k in range (4):
        dwt_img = np.zeros(shape = (H, W))
        for i in range(H):
            for j in range(W):
                #a, b, c, d
                dwt_img[i, j] = coe[k][0]*gray[int(i*2), int(j*2)]  + coe[k][1]*gray[int(i*2 + 1), int(j*2)] + coe[k][2]*gray[int(i*2), int(j*2 + 1)] + coe[k][3]*gray[int(i*2 + 1), int(j*2 + 1)]
        
        m = np.max(dwt_img)
        n = -np.min(dwt_img)
        if m > n:
            maximum = m
        else:
            maximum = n
       #灰階照片的值都偏小需要normalize     
        for i in range(dwt_img.shape[0]):
            for j in range(dwt_img.shape[1]):
                if dwt_img[i, j] < 0:
                    dwt_img[i, j] = - dwt_img[i, j]
                dwt_img[i, j] = np.round(255 * (dwt_img[i, j] / maximum))
                
        temp.insert(0, dwt_img)
    if times == 1:
        return temp
    else:
        temp2 = temp.pop(0)
        return dwt(temp2, (times-1))  

def button_event3():
    global myentry3
    if myentry3.get() == '':
        tk.messagebox.showerror('message', '未輸入數字')
    elif int(myentry3.get()) != 3 and int(myentry3.get()) != 5:
        tk.messagebox.showerror('message', '請輸入3或5')

        
text_var = []
entries = []
def get_mat():
    matrix = np.zeros(shape=(3,3))
    for i in range(3):
        for j in range(3):
            matrix[i][j] = int(text_var[i][j].get())
    d = int(text_var[i][j+1].get())
    for i in range(3):
        for j in range(3):
            matrix[i][j] /= d
    return matrix

x2 = 0
y2 = 0
for i in range(3):
    text_var.append([])
    entries.append([])
    for j in range(3):
        text_var[i].append(tk.StringVar())
        entries[i].append(tk.Entry(interface, textvariable=text_var[i][j],width=3))
        entries[i][j].place(x=800 + x2, y=60 + y2)
        x2 += 30
        if i == 2 and j == 2:
            text_var[i].append(tk.StringVar())
            entries[i].append(tk.Entry(interface, textvariable=text_var[i][j+1],width=3))
            entries[i][j+1].place(x=800 +x2, y=60 +y2)
            x2 += 30            
    y2 += 30
    x2 = 0

text_var2 = []
entries2 = []
def get_mat2():
    matrix2 = np.zeros(shape=(5,5))
    for i in range(5):
        for j in range(5):
            matrix2[i][j] = int(text_var2[i][j].get())
    d = int(text_var2[i][j+1].get())
    for i in range(5):
        for j in range(5):
            matrix2[i][j] /= d
    return matrix2

x3 = 0
y3 = 0
for i in range(5):
    text_var2.append([])
    entries2.append([])
    for j in range(5):
        text_var2[i].append(tk.StringVar())
        entries2[i].append(tk.Entry(interface, textvariable=text_var2[i][j],width=3))
        entries2[i][j].place(x=925 + x3, y=0 + y3)
        x3 += 30
        if i == 4 and j == 4:
            text_var2[i].append(tk.StringVar())
            entries2[i].append(tk.Entry(interface, textvariable=text_var2[i][j+1],width=3))
            entries2[i][j+1].place(x=925 +x3, y=0 + y3)
            x3 += 30            
    y3 += 30
    x3 = 0
    
def conv2d(filename):  
    label2.configure(image="")
    global flag
    if flag == 2:
        delt2()
        delt()  
        flag = 0
    elif flag:
        delt() 
        flag = 0
    
    gray_graph = np.array(filename)
    
    #重新帶入input圖片
    global img_pil
    img_pil = Image.fromarray(gray_graph)
    #載入ImageTk
    photo = ImageTk.PhotoImage(img_pil)
    #label顯示圖片
    label.configure(image=photo)
    label.image = photo
    label.place(x = 0, y = 150)  
    
    #size[0]是高 size[1]是寬
    image_row, image_col = gray_graph.shape
    size = int(myentry3.get())
    if size == 3:
        filter_matrix = get_mat()
    elif size == 5:
        filter_matrix = get_mat2()
    filter_row, filter_col = filter_matrix.shape
    result_matrix = np.zeros((image_row, image_col))
    padding = np.zeros((int(filter_row/2), image_col))
    padding_matrix = np.vstack((padding, gray_graph, padding))
    padding = np.zeros((padding_matrix.shape[0], int(filter_col/2)))
    padding_matrix = np.column_stack((padding, padding_matrix, padding))
    
    for i in range (int(filter_row/2), padding_matrix.shape[0]-int(filter_row/2)) :
        for j in range (int(filter_col/2), padding_matrix.shape[1]-int(filter_col/2)):
            result = 0
            for r in range (0, filter_row):
                for c in range (0, filter_col):
                    result += filter_matrix[r, c] * padding_matrix[i-int(filter_row/2)+r, j-int(filter_col/2)+c]
            result_matrix[i-int(filter_row/2), j-int(filter_col/2)] = abs(result)
            
    global img_gray
    img_gray = result_matrix
    global img_pil_real
    img_pil = Image.fromarray(result_matrix)
    img_pil_real = img_pil.convert("L")
    photo = ImageTk.PhotoImage(img_pil)    
    label2.configure(image=photo)
    label2.image = photo
    label2.place(x = 550, y = 150)  

#simga輸入
mylabel = tk.Label(interface,text="請輸入sigma的數字 0~60")
mylabel.place(x = 0, y = 93)
vcmd = (interface.register(validate), '%P')
myentry = tk.Entry(interface, validate='key', validatecommand = vcmd, width = 3)
myentry.place(x = 150, y= 95)
mybutton = tk.Button(interface, text='確定', command = button_event)
mybutton.place(x = 185, y = 90)

#dwt圈數輸入
mylabel2 = tk.Label(interface,text="請輸入圈數 1~9")
mylabel2.place(x = 230, y = 93)
vcmd2 = (interface.register(validate), '%P')
myentry2 = tk.Entry(interface, validate='key', validatecommand = vcmd, width = 3)
myentry2.place(x = 330, y= 95)
mybutton2 = tk.Button(interface, text='確定', command = button_event2)
mybutton2.place(x = 365 , y = 90)

#矩陣大小
mylabel3 = tk.Label(interface,text="矩陣大小(3 or 5)")
mylabel3.place(x = 450, y = 93)
vcmd3 = (interface.register(validate), '%P')
myentry3 = tk.Entry(interface, validate='key', validatecommand = vcmd, width = 3)
myentry3.place(x = 550, y= 95)
mybutton3 = tk.Button(interface, text='確定', command = button_event3)
mybutton3.place(x = 585, y = 90)

#按鈕 布局
input_btn = tk.Button(interface,text="選擇檔案",bg="sky blue", font=('Arial',12),width = 12, height = 2, command = Open_picture)
input_btn.place(x=0,y=0) 

hist_btn = tk.Button(interface,text="繪製直方圖",bg="#ED9121", font=('Arial',12),width = 12, height = 2, command = lambda : hist(img_gray, 0, 256, 257, 0)) 
hist_btn.place(x=118,y=0) 

noise_btn = tk.Button(interface,text="繪製高斯直方圖",bg="#ED9121", font=('Arial',12),width = 12, height = 2, command = lambda : noise(img_gray)) 
noise_btn.place(x=236,y=0) 

histeq_btn = tk.Button(interface,text="直方圖均化",bg="#ED9121", font=('Arial',12),width = 12, height = 2, command = lambda : hist(img_gray, 0, 256, 257, 1))
histeq_btn.place(x=354,y=0) 

conv2d_btn = tk.Button(interface,text="convolution",bg="#FF8888", font=('Arial',12),width = 12, height = 2, command = lambda : conv2d(img_gray))
conv2d_btn.place(x=562,y=0)

dwt_btn = tk.Button(interface,text="小波轉換",bg="#FF8888", font=('Arial',12),width = 12, height = 2, command = lambda : harr_dwt(img_gray))
dwt_btn.place(x=680,y=0) 

output_btn = tk.Button(interface,text="儲存檔案",bg="springgreen", font=('Arial',12),width = 12, height = 2, command = lambda : Save_picture(img_pil_real))
output_btn.place(x=798,y=0) 

#input圖片
label = tk.Label(interface,image="")
label.pack()

#output圖片
label2 = tk.Label(interface,image="")
label2.pack()

#資訊說明欄
label_text = tk.Label(interface,text="輸入圖片",bg="sky blue", font=('Arial',12),relief="solid")
label_text.place(x = 0, y = 120)
    
label_text2 = tk.Label(interface,text="輸出圖片",bg="springgreen", font=('Arial',12), relief="solid")
label_text2.place(x =550, y = 120)

#訊息欄位
Label = tk.Label(interface, text = "", font=('Arial',20))
Label.place(x = 0, y = 50)

Label2d = tk.Label(interface, text="Enter matrix :", font=('Arial',12))
Label2d.place(x = 700, y = 55)

Label2d2 = tk.Label(interface, text="(右下角為分母必填)")
Label2d2.place(x = 690, y = 75)

interface.mainloop()