#!/usr/bin/pyton3

import sys

#get command line agruments

numArg = int(len(sys.argv))
if numArg >= 2:
	userName = "%s" % (sys.argv[1])

for i in range (2, numArg):
	userName = "%s %s" % (userName, sys.argv[i])

#puts all the streams into a list
allSFile = "messages/allStreams.txt"
file_1 = open(allSFile,"r")
allSList = []
for line in file_1:
	line = line.rstrip('\n')
	allSList.append("%s"%line)

#check each streamUser file
userStreams = []
for stream in allSList:
	fileName = "messages/%sStreamUsers.txt"%stream
	f = open(fileName,"r")
	if stream in f.read():
		userStreams.append("%s"%stream)

print (userStreams)




#open a file

#test_file = open("test.txt", 'r');