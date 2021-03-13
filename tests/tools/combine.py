from os import listdir
from os.path import isfile, join
import glob

mypath = "./data/"
begining = "2"


files = [f for f in listdir(mypath) if (isfile(join(mypath, f)) and f[0] == begining)]

allText = ""

for f in sorted(files, key=lambda name: int(name.split(".")[1])):
    if isfile(join(mypath, f)):
        with open(mypath + f, 'r') as file:
            current = file.read()
            
            allText += current

lines = allText.split("\n")
finalText = ""
for i, line in enumerate(lines):
    if (line.startswith(",")):
        finalText = finalText[:-1]
    finalText += line + "\n"
    if (i % 10000 == 0):
        print(i, len(lines))


file = open("result.txt", 'w')
file.write(finalText)
file.close()