#!/usr/bin/python3

# getCp.py
# Author: Jessica Authier
# 2017/03/17

import sys
import os

def getUsersCurrentStream(user, stream):
    fn = "a2/messages/%sStreamUsers.txt"%stream
    file = open(fn,"r")
    for line in file:
        if user in line:
            pos = line.split(' ')
            return pos[1]
    return -1

# command line parameters: user, stream, sort
if __name__ == "__main__":

    userName = "%s" % (sys.argv[1])
    stream = "%s" % (sys.argv[2])
    sort = "%s" % (sys.argv[3])

    if (stream != "all" and sort == "-d"):
        print( getUsersCurrentStream(userName, stream),end="")
    elif (stream != "all" and sort == "-r"):
        dataFile = "a2/messages/%sStreamData.txt"
        file = open(dataFile, "r").readlines()
        print (len(file)-1,end="")

