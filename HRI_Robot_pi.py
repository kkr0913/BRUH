#!/usr/bin/python3

from cvzone.HandTrackingModule import HandDetector
import cv2
import serial
import struct
import time

# UART Setup
com = serial.Serial()
com.port = "/dev/ttyS0"
com.baudrate = 115200
com.open()

# Get Video from ESP32-CAM Access Point
time.sleep(5)  # wait for AP connection
URL = "http://192.168.4.1"
cap = cv2.VideoCapture(URL + ":81/stream")
detector = HandDetector(detectionCon=0.5, maxHands=1)


def get_gesture():  # Function to detect hand gestures
    if totalFingers == 5:
        return 0, "Stop"
    elif totalFingers == 0 and joint_x < wrist_x:
        return 1, "Move Forward"
    elif totalFingers == 0 and joint_x > wrist_x:
        return 2, "Move Backward"
    elif totalFingers == 1 and fingers[0] == 1:
        if thumb_x < joint_x and abs(thumb_y - joint_y) <= 30:
            return 3, "Move Left"
        elif thumb_x > joint_x and abs(thumb_y - joint_y) <= 30:
            return 4, "Move Right"
        else:
            return 0, "Stop"
    elif totalFingers == 2 and fingers[1] * fingers[2] == 1:
        if index_x < middle_x:
            return 5, "Turn Left"
        else:
            return 6, "Turn Right"
    else:
        return 0, "Stop"


def get_handloc():  # Function to check whether the hand is too close to the edge of the frame
    if center_x < cap.get(3) * 0.25:
        return 1
    elif center_x > cap.get(3) * 0.75:
        return 2
    else:
        return 0


while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    gesture = (0, "Stop")
    handloc = 0

    if lmList:  # Hand is detected
        fingers = detector.fingersUp()
        totalFingers = fingers.count(1)
        wrist_x, wrist_y = lmList[0][0], lmList[0][1]
        joint_x, joint_y = lmList[3][0], lmList[3][1]
        thumb_x, thumb_y = lmList[4][0], lmList[4][1]
        index_x, index_y = lmList[8][0], lmList[8][1]
        middle_x, middle_y = lmList[12][0], lmList[12][1]
        center_x, center_y = lmList[9][0], lmList[9][1]
        gesture = get_gesture()
        handloc = get_handloc()
        cv2.putText(img, f'Fingers: {totalFingers}', (20, 120), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 0), 3)

    # Send serial data
    com.write(struct.pack("B", 10 * handloc + gesture[0]))

    # Display
    cv2.putText(img, gesture[1], (20, 70), cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 3)
    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
