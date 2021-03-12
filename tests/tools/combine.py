from os import listdir
from os.path import isfile, join
import glob

mypath = "./data/"
begining = "2"


files = [f for f in listdir(mypath) if (isfile(join(mypath, f)) and f[0]=="2")]

allText = b""

for f in sorted(files, key=lambda name: int(name.split(".")[1])):
    #print(f)
    if isfile(join(mypath, f)):
        with open(mypath + f, 'rb') as file:
            allText += file.read()



file = open("result.txt", 'wb')
file.write(allText)
file.close()