f = open("Spotify 2010 - 2019 Top 100.csv", "r", encoding='cp1252')
f2 = open("Spotify 2010 - 2019 Top 100(new).csv", "w")

for line in f:
    for i in range(len(line)):
        if(line[i]=="\t"):
            f2.write(",")
        elif(ord(line[i])>=32 and ord(line[i])<=126):
            f2.write(line[i])
    f2.write("\n")
    
f.close()
f2.close()