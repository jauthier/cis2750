#!/usr/bin/pyton3

import sys
import os

class Post:
    def __init__(self, stream, author, date, text):
    	self.stream = stream
    	self.author = author
    	self.date = date
    	self.text = text

# reads a stream file and puts its contents into a list of posts
def streamFileToList(streamFile, dataFile, stream):

	# get the number of entries and where they end
	fpData = open(dataFile,"r")
	dataList = fpData.readlines()
	numPosts = len(dataList)
	# read in the stream file and put the posts in a list
	fpStream = open(streamFile,"r")
	streamFileList = fpStream.readlines()
	postStart = 0
	postList = []
	
	for i in range(0,numPosts):
		postEnd = int(dataList[i]) #get the last line of the post

		tokens = streamFileList[postStart].split(":")
		postStart +=1
		user = tokens[1][1:]
		date = streamFileList[postStart][6:]
		postStart +=1
		text = ""
		for j in range(postStart,postEnd):
			text = text + streamFileList[postStart]

		newPost = Post(stream, user, date, text)
		postList.append(newPost)
		postStart = postEnd
	
	return postList

def getStream(stream):
	os.system('clear')
	postList = [] # a list of all the posts
	# file names
	streamFile = "a2/messages/%sStream.txt"%stream
	dataFile = "a2/messages/%sStreamData.txt"%stream
	# get the list of the posts
	postList = streamFileToList(streamFile, dataFile, stream)
	return postList

def getAllStreams(userName):
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
				userStreams.append("%s"%stream)
	f.close()

	postList = [] # a list of all the posts
	#make the postList
	if choice == "all":
		listOfList = [] # a list of lists
		for s in streamList:
			# file names for the stream
			streamFile = "messages/%sStream.txt"%s
			dataFile = "messages/%sStreamData.txt"%s 
			usersFile = "messages/%sStreamUsers.txt"%s
			# add the stream list to the list of lists
			listOfList.append(streamFileToList(streamFile,dataFile,s))
		postList = combineStreams(listOfList)
	return postList


if __name__ == "__main__":
	#get command line agruments
	# there will be username, stream, whether next or previous was clicked and how the list is to be sorted
	# get the stream list and print the appropriate post to the screen, update files if needed
	userName = "%s" % (sys.argv[1])
	stream = "%s" % (sys.argv[2])
	action = "%s" % (sys.argv[3])

	postList = []
	if (stream == "all"):
		postList = getAllStreams(userName)
	else:
		postList = getStream(stream)
	
	# deal with the action


	#done