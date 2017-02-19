#!/usr/bin/pyton3

import sys
import os

if __name__ == "__main__":
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
	file_1.close()

	#check each streamUser file
	userStreams = []
	for stream in allSList:
		fileName = "messages/%sStreamUsers.txt"%stream
		f = open(fileName,"r")
		if userName in f.read():
			userStreams.append("%s"%stream)
	f.close()
	
	choice = getStream(userStreams)
	postList = []

	#show the posts
	if choice != "all":
		print("all")
		#get the last post they saw with the earliest date
		#order the posts in order of date

		#make a list of lists
		listOfList = []
		for s in userStreams:
			streamFile = "messages/%sStream.txt"%s
			dataFile = "messages/%sStreamData.txt"%s 
			listOfList.append(streamFileToList(streamFile,dataFile,s))

		postList = combineStreams(listOfList)


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
		topPos = open(dataFile).readlines()[lastPostRead-1] + 1
	

	printPosts(postList, topPos)
	uI = input().rstrip('\n')
	while uI != "q":
		if uI == "^[[A": #up arrow
			topPos = topPos - 1
			printPosts(postList,topPos)
		elif uI == "^[[B": #down arrow
			topPos = topPos + 1
			printPosts(postList,topPos)
		elif uI == "O": #sort by author

		elif uI == "M": #mark all as read

		elif uI == "C": #check for new messages

		elif uI == "S": # let user select a new stream
			#get stream then redo if else bit above

		uI = input().rstrip('\n')

	#done

def getStream(streamList):
	os.system('clear')
	print("Which stream would you like to view?");
	for stream in streamList:
		print (stream +" ", end='');
	print("all");
	#get the users choice
	choice = input().rstrip('\n')
	return choice

def printPosts(postList, topPos, lastPost):
	#clear and print
	os.system('clear')
	# display 22 lines of the posts and a line of controls
	numPosts = len(postList)
	#start with lastpost + 1
	currentPost = lastPost + 1
	post = postList[currentPost]
	# display what you can of the post
	for i in range(topPos, topPos+21):
		if i in post: # make sure the key is in the dict
			print(post[i])
		else:
			currentPost += 1
			post = postList[currentPost]
			print(post[i])

	print("Up Arrow    Down Arrow    O-Order Toggle    M-Mark All    C-Check new    S-New Stream")


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
	for i in range(len(streamFileList)):
		postList = {}
		postEnd = dataList[i]
		line = "Stream: %s\n"%stream
		postList.update(count:line)
		count += 1
		for j in range(postStart,postEnd):
			postList.update(count : streamFileList[j])
			count += 1
		streamList[i] = postList
		postStart = postEnd + 1
	return streamList

def combineStreams(listOfList):
	#order posts by data





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
