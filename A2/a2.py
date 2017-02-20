#!/usr/bin/pyton3

import sys
import os

def combineStreams(listOfList, dataList):
	#combine the first two
	list1 = listOfList[0]
	numPosts = len(list1)
	cpList = []
	if numPosts > int(dataList[0]):
		cpList.append(list1[dataList[0]]) #get the current post of the first stream
	l = len(listOfList)

	for i in range(1, l):
		list2 = listOfList[i]
		numPosts = len(list2)
		if numPost > int(dataList[i]):
			cpList.append(list2[int(dataList[i])])	
		list1 = mergeTwoList(list1, list2)
	
	print(list1)
	newList = redoKeys(list1)
	print(newList)
	temp = getTopPos(newList, cpList)
	topPos = temp[0]
	lastPost = temp[1]
	
	final = [newList, topPos,lastPost]
	return final

def mergeTwoList(list1, list2):
	newList = []
	l1 = len(list1)
	l2 = len(list2)
	i = 0
	j = 0

	while i < l1 and j < l2:
		if compareDates(list1[i][2], list2[j][2]) == 1:
			#post1 was posted before post2
			newList.append(list1[i])
			i += 1
		else:
			newList.append(list2[j])
			j += 1
	if i < l1: #list2 ran out first
		while i < l1:
			newList.append(list1[i])
			i += 1
	else: #list1 ran out first
		while j < l2:
			newList.append(list2[j])
			j += 1
	return newList

def redoKeys(listOfDicts):
	numPosts = len(listOfDicts)
	count = 0
	newList = []
	for post in listOfDicts:
		newDict = {}
		l = len(post)
		for i in range(0,l):
			temp = list(post.values())
			newDict.update({count : temp[i]})
			count += 1
		newList.append(newDict)
	return newList

def getTopPos(postList, cpList):
	numPosts = len(postList)
	# if the user has read everything
	if len(cpList) == 0:
		return [postList[numPosts -1].keys()[0],numPosts -1]

	#find the earliest post from cpList
	cp1 = cpList[0]

	for i in range(1,len(cpList)):
		cp2 = cpList[i]
		if compareDate(cp1[2], cp2[2]) == 1:
			cp1 = cp2
	#find cp1 in the postList
	count = 1
	for p in postList:
		print("%d"%len(p))
		val = list(p.values())
		print("%d"%len(val))
		if val[0] == cp1[0]:
			if val[1] == cp1[1]:
				if val[2] ==  cp1[2]:
					return [p.keys()[0], 1]
		count += 1

	return [postList[numPosts -1].keys()[0],numPosts -1]


# return 0 if date1 is before date2
def compareDates(date1, date2):
	#check year first, then month then date then time
	d1 = date1.split(' ,')
	d2 = date2.split(' ,')

	#compare year
	check = compareInts(int(d1[2].split(',')[0]), int(d2[2].split(',')[0]))
	if check == 0:
		#check month
		check = compareInts(monthNUm(d1[0]), monthNum(d2[0]))
		if check == 0:
			#check day
			check = compareInts(int(d1[1]), int(d2[1]))
			if check == 0:
				#check time 
				check = compareTime(d1[3], d2[3])
	if check == 1:
		return 0
	else :
		return 1

def compareTime(time1, time2):
	t1 = time1.split(':')
	t2 = time2.split(':')
	# compare hour
	check =  compareInts(t1[0], t2[0])
	if check == 0:
		#compare minute
		check = compareInts(t1[1],t2[1])
		if check == 0:
			#compare seconds
			check = compareInts(t1[2],t2[2])

	if check == 1:
		return 1
	else :
		return 2

def monthNum(m):
	if m == "Jan":
		return 1
	elif m == "Feb":
		return 2
	elif m == "Mar":
		return 3
	elif m == "Apr":
		return 4
	elif m == "May":
		return 5
	elif m == "June":
		return 6
	elif m == "July":
		return 7
	elif m == "Aug":
 		return 8
	elif m == "Sept":
		return 9
	elif m == "Oct":
		return 10
	elif m == "Nov":
		return 11
	elif m == "Dec":
		return 12
	else:
		return -1

def compareInts(num1, num2):
	if num1 < num2:
		return 1
	elif num1 > num2:
		return 2
	else:
		return 0


def updateFile(stream, userName,inc):
	fileName = "messages/%sStreamUsers.txt"%stream
	tempFile = "messages/temp.txt"
	file = open(fileName, "r")
	temp = open(tempFile,"w")
	for line in file:
		hold = line.split(' ')
		if userName in line:
			temp.write("%s %d"%hold[0],(int(hold[1])+inc))
		else:
			temp.write(line)
	remove(fileName)
	move(tempFile, fileName)

def printPosts(postList, topPos, lastPost):
	#clear and print
	os.system('clear')
	check = 0

	# display 22 lines of the posts and a line of controls
	count = 0
	for post in postList:
		l = len(post)
		for i in post:
			if i >= int(topPos) and count < int(topPos)+22:
				print(post.get(i),end='')
				count += 1
		ckeck += 1
	print("U-Up    D-Down    O-Order Toggle    M-Mark All    C-Check new    S-New Stream")
	return check - int(lastPostRead) 


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
		postStart = postEnd
	
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
		if int(lastPostRead) == 0:
			topPos = 0
		else:
			hold = open(dataFile).readlines()[int(lastPostRead)-1]
			topPos =  int(hold) + 1
		temp = open(dataFile).readlines()
		lastLine = temp[len(temp)-1]

	rList = [postList, topPos, lastPostRead, choice, lastLine]
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
	lastLine = rList[4]

	moreRead = printPosts(postList, topPos, lastPostRead)
	if moreRead > 0 and choice  "all":
		updateFile(choice, userName, moreRead)
	uI = input().rstrip('\n')
	while uI != "q":
		if uI == "U": #up arrow
			if topPos - 1 != 0:
				topPos = topPos - 1
			moreRead = printPosts(postList,topPos, lastPostRead)
			if moreRead > 0 and choice = "all":
				updateFile(choice, userName, moreRead)
		elif uI == "D": #down arrow
			if topPos + 1 < lastLine - 23:
				topPos = topPos + 1
			moreRead = printPosts(postList,topPos, lastPostRead)
			if moreRead > 0 and choice = "all":
				updateFile(choice, userName, moreRead)
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