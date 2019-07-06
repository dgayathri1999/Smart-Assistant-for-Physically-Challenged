import numpy as np
import cv2
import serial
ser = serial.Serial('/dev/ttyACM0',9600)
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
camera=cv2.VideoCapture(1)
numerator=0
denominator=0
ard=0
count_r=0
count_l=0
count_f=0
while True:
	ret, frame = camera.read()
	roi=frame
	frame=cv2.flip(frame,1)
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.3, 5)
	if (len(faces)!=0):
		for (x,y,w,h) in faces:
			cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),1)
			cv2.line(frame,(int(x+w/4.2),int(y+h/2.2)),(int(x+w/2.5),int(y+h/2.2)),(0,255,0),1)
			cv2.line(frame,(int(x+w/4.2),int(y+h/3)),(int(x+w/2.5),int(y+h/3)),(0,255,0),1)
			cv2.line(frame,(int(x+w/4.2),int(y+h/3)),(int(x+w/4.2),int(y+h/2.2)),(0,255,0),1)
			cv2.line(frame,(int(x+w/2.5),int(y+h/3)),(int(x+w/2.5),int(y+h/2.2)),(0,255,0),1)
			d=10920.0/float(w)
			x1=int(x+w/4.2)+1 
			x2=int(x+w/2.5)
			y1=int(y+h/3)+1
			y2=int(y+h/2.2)
			roi=frame[y1:y2,x1:x2]
			gray=cv2.cvtColor(roi,cv2.COLOR_BGR2GRAY)
			equ = cv2.equalizeHist(gray)
			thres=cv2.inRange(equ,0,20)
			kernel = np.ones((3,3),np.uint8)
			dilation = cv2.dilate(thres,kernel,iterations = 2)
			erosion = cv2.erode(dilation,kernel,iterations = 3)
			contours, hierarchy = cv2.findContours(erosion,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
			if len(contours)==2 :
				numerator+=1
				M = cv2.moments(contours[1])
				if M['m00']!=0:
					cx = int(M['m10']/M['m00'])
					cy = int(M['m01']/M['m00'])
					cv2.line(roi,(cx,cy),(cx,cy),(0,0,255),3)
			elif len(contours)==1:
				numerator+=1
				M = cv2.moments(contours[0])
				if M['m00']!=0:
					cx = int(M['m10']/M['m00'])
					cy = int(M['m01']/M['m00'])
					cv2.line(roi,(cx,cy),(cx,cy),(0,0,255),3)
			else:
				denominator+=1
			ran=x2-x1
			mid=ran/2
			if (cx<mid-10):
				count_l+=1
				if (count_l%5==0 and ard!='l'):
					print ("looking left")
					ard = 'l'
					y=ard.encode('ascii')
					ser.write(y)
			elif (cx>mid+10):
				count_r+=1
				if (count_r%5==0 and ard!='r'):
					print ("looking right")
					ard ='r'
					y=ard.encode('ascii')
					ser.write(y)
			elif (mid-10<cx<mid+10):
				count_f+=1
				if (count_f%5==0 and ard!='f'):
					print ("looking forward")
					ard = 'f'
					y=ard.encode('ascii')
					ser.write(y)
	else:
		if(ard != 's'):
			print ("stop")
			ard = 's'
			y=ard.encode('ascii')
			ser.write(y)
	cv2.imshow("frame",frame)
	if cv2.waitKey(30)==27 & 0xff:
		break
camera.release()
print ("accurracy=",(float(numerator)/float(numerator+denominator))*100)
cv2.destroyAllWindows()
