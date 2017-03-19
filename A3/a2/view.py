#!/usr/bin/python3

# view.py
# Author: Jessica Authier
# 2017/03/17

import sys
import os

class Post:
    def __init__(self, stream, author, date, text):
    	self.stream = stream
    	self.author = author
    	self.date = date
    	self.text = text

# return 0 if date1 is before date2
def compareDates(date1, date2):
	#check year first, then month then date then time
	d1 = date1.split(':')[1]
	d2 = date2.split(':')[1]
	h1 = d1.split(' ')
	h2 = d2.split(' ')
	t1 = "%s:%s:%s"%(h1[4], d1[2], d1[3])
	t2 = "%s:%s:%s"%(h2[4], d2[2], d2[3])
	#compare year
	check = compareInts(int(h1[3]), int(h2[3]))
	if check == 0:
		#check month
		check = compareInts(monthNum(h1[0]), monthNum(h2[0]))
		if check == 0:
			#check day
			check = compareInts(int(h1[2].split(',')[0]), int(h2[2].split(',')[0]))
			if check == 0:
				#check time 
				check = compareTime(t1, t2)
	
	if check == 1:
		return 0
	else :
		return 1

def compareTime(time1, time2):
	print(time2)
	print(time2)
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

def mergeTwoList(list1, list2):
	newList = []
	l1 = len(list1)
	l2 = len(list2)
	i = 0
	j = 0

	while i < l1 and j < l2:
		if compareDates(list1[i].date, list2[j].date) == 1:
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

def combineStreams(listOfList):
	#combine the lists
	list1 = listOfList[0]
	numPosts = len(list1)
	l = len(listOfList)

	for i in range(1, l):
		list2 = listOfList[i]
		list1 = mergeTwoList(list1, list2)
	
	print(list1)
	newList = redoKeys(list1)
	print(newList)
	temp = getTopPos(newList, cpList)
	topPos = temp[0]
	lastPost = temp[1]
	
	final = [newList, topPos,lastPost]
	return final

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
	if (len(userStreams)==0):
		return postList;
	#make the postList
	listOfList = [] # a list of lists
	for s in userStreams:
		# file names for the stream
		streamFile = "a2/messages/%sStream.txt"%s
		dataFile = "a2/messages/%sStreamData.txt"%s 
		usersFile = "a2/messages/%sStreamUsers.txt"%s
		# add the stream list to the list of lists
		listOfList.append(streamFileToList(streamFile,dataFile,s))
	#postList = combineStreams(listOfList)
	return postList

def sortByAuthor(postList):
	
	l = len(postList)
	if (l < 2):
		return postList;
	h = l//2
	list1 = postList[0:h]
	list2 = postList[h:]
	list1 = sortByAuthor(list1)
	list2 = sortByAuthor(list2)
	return merge(list1,list2)

def merge(list1, list2):
    newList = []
    i=0
    j=0
    k=0
    while i < len(list1) and j < len(list2):
        if list1[i].user < list2[j].user:
            newList[k]=list1[i]
            i=i+1
        else:
            newList[k]=list2[j]
            j=j+1
        k=k+1

    while i < len(list1):
        newList[k]=list1[i]
        i=i+1
        k=k+1

    while j < len(list2):
        newList[k]=list2[j]
        j=j+1
        k=k+1

def printPost (post):
	print("Stream: %s\nUser: %s\nDate: %s\n%s"%(post.stream, post.user, post.date, post.text))

def getUsersCurrentStream(user, stream):
	fn = "a2/messages/%sStreamUsers.txt"%stream
	file = open(fn,"r")
	for line in file:
		if user in line:
			pos = line.split(' ')
			return pos[1]
	return -1

def updateFile(stream, userName,inc):
	fileName = "a2/messages/%sStreamUsers.txt"%stream
	tempFile = "a2/messages/temp.txt"
	file = open(fileName, "r")
	temp = open(tempFile,"w")
	for line in file:
		hold = line.split(' ')
		if userName in line:
			temp.write("%s %d\n"%(hold[0],(int(hold[1])+inc)))
		else:
			temp.write(line)
	os.remove(fileName)
	os.rename(tempFile, fileName)

if __name__ == "__main__":
	#get command line agruments
	# there will be username, stream, whether next or previous was clicked and how the list is to be sorted
	# get the stream list and print the appropriate post to the screen, update files if needed
	userName = "%s" % (sys.argv[1])
	stream = "%s" % (sys.argv[2])
	action = "%s" % (sys.argv[3]) # -p -n -c -r
	sort = "%s" % (sys.argv[4]) # -d -a
	currentPost = "%s" % (sys.argv[5])

	postList = []
	if (stream == "all"):
		postList = getAllStreams(userName)
	else:
		postList = getStream(stream)
	
	if (sort == "-a"):
		postList = sortByAuthor(postList)
	cp = 0
	l = len(postList)
	# deal with the action
	if (action == "-p"): #previous
		if (int(currentPost)-1 >= 0):
			cp = int(currentPost)-1
			printPost(postList[cp])
		else:
			cp = int(currentPost)
			printPost(postList[cp])
	elif (action == "-n"): #next
		if (int(currentPost)+1 < l):
			cp = int(currentPost)+1
			printPost(postList[cp])
			if (sort != "-a"):
				if (cp > getUsersCurrentStream(userName, stream)):
					updateFile(stream, userName, 1)
		else:
			cp = int(currentPost)
			printPost(postList[cp])
	elif (action == "-c"): #current
		cp = int(currentPost)
		printPost(postList[cp])
	elif (action == "-r"): #most recent
		cp = l-1
		printPost(postList[cp])

	print(cp)
	#done
