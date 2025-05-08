
# this script accesses data from reddit api and feeds it to the serial port
# from where Arduino reads it and displays

# ====================================================================
# if you want to run this script keep this instructions in mind


# ==================================================================================
# if you want to run this script keep this instructions in mind
# 
# *** setting up the serial port ***
# here I just get a list of all available ports and use the first one, this may not
# work for you, in that case you replace "ports[0].device" with the name of the port
# your device is connected to
# 
# *** setting up the reddit scrapper ***
# here you need to have a text file containing all the information this reddit scrapper
# needs from reddit post url to username and password, check out comments in that portion
# of the code for more details
# 
# *** this loop fetches the data and sends it to the serial device ***
# this portion doesn't need much change if you don't want to change the format of
# the serial data but still there is a commented print statement for debug purpose, if
# activated it will print the serial data sent to the port
# ==================================================================================


import serial

import serial.tools.list_ports as serial_list

import time

import requests


# ==============================================================
# setting up the serial port
# ==============================================================


# accessing a list of available ports

ports = serial_list.comports()	# get the list of available ports

if(not ports):

	print("No ports available")

	quit()

# we have a port, opening it, "ports[0].device" name of first port
# if it doesn't work for you replace "ports[0].device" with the name
# of the port your device is connected to

arduino = serial.Serial(ports[0].device, 9600);


# ==============================================================
# setting up the reddit scrapper
# ==============================================================


# secrets.txt holds the necessary data, one data per line, starting from url to password
# I keep secrets.txt in .venv so that git doesn't track it, remember it contains all the
# sensitive infos, so it must not be a part of this repo

with open(".venv/secrets.txt", "rt") as secrets:

	# load necessary keys and ids from the file

	api_key = secrets.readline().strip()

	video_id = secrets.readline().strip()

	channel_id = secrets.readline().strip()


# ==============================================================
# this loop fetches the data and sends it to the serial device
# ==============================================================


# the loop from where we call the reddit api at a interval of 1 seconds

# run this loop as long as serial port is available

while(True):
	
	# sending string to this port, break the loop if unable to send

	try:

		v_response = requests.get(url = "https://www.googleapis.com/youtube/v3/videos", params = {"part": "snippet,statistics", "id" : video_id, "key" : api_key})

		c_response = requests.get(url = "https://www.googleapis.com/youtube/v3/channels", params = {"part": "statistics", "id" : channel_id, "key" : api_key})

		# getting video data

		video = v_response.json()["items"][0]

		# the title

		title = video["snippet"]["title"]

		# the stats

		stats = video["statistics"]

		views = stats["viewCount"]

		likes = stats["likeCount"]

		comments = stats["commentCount"]

		# getting channel data

		channel = c_response.json()

		# no. of subscribers

		subs = channel["items"][0]["statistics"]["subscriberCount"]

		# preparing the serial string

		serial_str = f"{views},{likes},{comments},{subs},{title}\n".encode()
		
		arduino.write(serial_str)	# encode is used to change the string into byte stream

	except:

		print("No Internet Connection Or Port is no longer connected")

		break
	
	# print(serial_str)	# debug

	time.sleep(1)


# closing the serial port

arduino.close()