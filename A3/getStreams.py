#!/usr/bin/python3

# getStreams.py
# Author: Jessica Authier
# 2017/03/18

import sys
import os

def getStreams(user):
	#puts all the streams into a list
	allSFile = "a2/messages/allStreams.txt"
	file_1 = open(allSFile,"r")
	allSList = []
	for line in file_1:
		line = line.rstrip('\n')
		allSList.append("%s"%line)
	file_1.close()

	#check each streamUser file
	userStreams = []
	for stream in allSList:
		usersFile = "a2/messages/%sStreamUsers.txt"%stream
		streamFile = "a2/messages/%sStream.txt"%stream
		f = open(usersFile,"r")
		sf = open(streamFile, "r").readlines()
		if userName in f.read():
			if len(sf) != 0: #if the stream is empty it wont be added
				print("%s"%stream)
		f.close()

if __name__ == "__main__":
	user = "%s" % sys.argv[1]
	getStreams(user)