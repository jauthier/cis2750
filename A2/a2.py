#!/usr/bin/pyton3

import sys
import os

def printPosts(postList, topPos, lastPost):
	#clear and print
	os.system('clear')
	print(postList)
	# display 22 lines of the posts and a line of controls
	numPosts = len(postList)
	#start with lastpost + 1
	currentPost = int(lastPost)
	post = postList[currentPost]
	# display what you can of the post
	for post in postList:
		print(post)
		count = 0;
		hold = list(post.values())
		for i in range(topPos, topPos+21):
			if i in post: # make sure the key is in the dict
				print(hold[count])
				count += 1
			else:
				break


	print("U-Up    D-Down    O-Order Toggle    M-Mark All    C-Check new    S-New Stream")

def streamFileToList(streamFile, dataFile, stream):
	# get the number of entries and where they end
	fpData = open(dataFile,"r")
	dataList = fpData.readlines()
	numPosts = len(dataList)
	# read in the stream file and put the posts in a list
	fpStream = open(streamFile,"r")
	streamFileList = fpStream.readlines()
	postStart = 0
	count  = 0
	streamList = []
	# make a dict for each post
	for i in range(0,numPosts):
		postList = {}
		postEnd = int(dataList[i]) #get the last line of the post
		line = "Stream: %s\n"%stream
		postList.update({count:line})
		count += 1
		for j in range(postStart,postEnd):
			postList.update({count : streamFileList[j]})
			count += 1
		streamList.append(postList)
		postStart = postEnd + 1
	
	print(streamList)
	return streamList

def getStream(streamList):
	os.system('clear')
	check = 0
	while check == 0:

		print("Which stream would you like to view?");
		for stream in streamList:
			print (stream +" ", end='');
		print("all");
		#get the users choice
		choice = input().rstrip('\n')
		if choice == "all":
			check = 1
		else:
			for line in streamList:
				if choice == line:
					check = 1

	postList = [] # a list of all the posts
	lastPRList = [] # a list of the users current pos in each stream file they are viewing

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
			#get the last post the user read
			f = open(usersFile, "r")
			for str in f:
				if userName in str:
					parse = str.split(":")
					lastPostRead = parse[1].split(' ')[1]
					lastPostRead = lastPostRead.split('\n')[0]
					lastPRList.append(int(lastPostRead))

		hold = combineStreams(listOfList, lastPRList)
		postList = hold[0]
		topPos = hold[1]
		lastPostRead = hold[2]


	else:
		#open the streamUsers file and get the users location
		fn = "messages/%sStreamUsers.txt"%choice
		f = open(fn, "r")
		for str in f:
			if userName in str:
				parse = str.split(" ")
				lastPostRead = parse[1]

		streamFile = "messages/%sStream.txt"%choice
		dataFile = "messages/%sStreamData.txt"%choice
		postList = streamFileToList(streamFile, dataFile, choice)
		hold = open(dataFile).readlines()[int(lastPostRead)-1]
		topPos =  int(hold) + 1

	rList = [postList, topPos, lastPostRead, choice]
	return rList

if __name__ == "__main__":
	#get command line agruments

	userName = ""
	numArg = int(len(sys.argv))
	if numArg >= 2:
		userName = "%s" % (sys.argv[1])
	else:
		print("Please enter you username.")
		sys.exit(0)

	for i in range (2, numArg):
		userName = "%s %s" % (userName, sys.argv[i])

	#puts all the streams into a list
	allSFile = "messages/allStreams.txt"
	file_1 = open(allSFile,"r")
	allSList = []
	for line in file_1:
		line = line.rstrip('\n')
		allSList.append("%s"%line)
	file_1.close()

	#check each streamUser file
	userStreams = []
	for stream in allSList:
		usersFile = "messages/%sStreamUsers.txt"%stream
		streamFile = "messages/%sStream.txt"%stream
		f = open(usersFile,"r")
		sf = open(streamFile, "r").readlines()
		if userName in f.read():
			if len(sf) != 0: #if the stream is empty it wont be added
				userStreams.append("%s"%stream)
	f.close()
	
	rList = getStream(userStreams)
	postList = rList[0]
	topPos = rList[1]
	lastPostRead = rList[2]
	choice = rList[3]

	printPosts(postList, topPos, lastPostRead)
	uI = input().rstrip('\n')
	while uI != "q":
		if uI == "U": #up arrow
			topPos = topPos - 1
			printPosts(postList,topPos, lastPostRead)
		elif uI == "D": #down arrow
			topPos = topPos + 1
			printPosts(postList,topPos, lastPostRead)
		elif uI == "O": #sort by author
			print("O")
		elif uI == "M": #mark all as read
			#update file(s)
			print("M")
		elif uI == "C": #check for new messages
			print("C")
		elif uI == "S": # let user select a new stream
			print("S")
			hold = getStream(userStreams)
			postList = hold[0]
			topPos = hold[1]
			lastPostRead = hold[2]
			printPosts(postList, topPos, lastPostRead)

		uI = input().rstrip('\n')

	#done