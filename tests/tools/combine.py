from os import listdir
from os.path import isfile, join

mypath = "./output/"

onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

allText = ""

for f in sorted(listdir(mypath), key=len):
    if isfile(join(mypath, f)):
        with open("./output/" + f, 'r') as file:
            allText += file.read()

file = open("result.txt", 'w')
file.write(allText)
file.close()