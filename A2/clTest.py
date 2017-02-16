#!/usr/bin/pyton3

import sys

#get command line agruments

numArg = int(len(sys.argv))
if numArg >= 2:
	userName = "%s" % (sys.argv[1])

for i in range (2, numArg):
	userName = "%s %s" % (userName, sys.argv[i])

print (userName)

allSFile = "messages/allStreams.txt"
file_1 = open(allSFile,"r")
allSList = []
for line in file_1:
	allSList.append("%s"%line,end='')
print(allSList)

#open a file

#test_file = open("test.txt", 'r');