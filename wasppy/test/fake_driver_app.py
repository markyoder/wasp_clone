#!/usr/bin/env python
#write three columns data here
#def rst_render():
import random
seed = 0
with open("fake_app_input", "r") as input:
    seed = int(input.readline())
random.seed(seed)
def rnd_string(iCol):
    strLine=""
    for x in range(iCol):
        strLine=strLine + str(random.randint(1,101)*random.randint(1,x+2)*0.25) + " "
    return strLine + "\n"

tmpFile = open("fake_driver_app.csv","w")
tmpFile.write("x: "+rnd_string(3)) 
tmpFile.write("v: "+rnd_string(2)) 
tmpFile.write("x: "+rnd_string(3)) 
tmpFile.write(rnd_string(4)) 
tmpFile.write(rnd_string(4)) 
tmpFile.write(rnd_string(4)) 
tmpFile.close()

