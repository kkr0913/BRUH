from cvzone.HandTrackingModule import HandDetector
import cv2
import serial
import time
import struct

com = serial.Serial()
com.port = "COM5"
com.baudrate = 115200
com.open()

# URL = "http://192.168.4.1"
# cap = cv2.VideoCapture(URL + ":81/stream")
cap = cv2.VideoCapture(1)
cap.set(3, 1280)
cap.set(4, 720)
detector = HandDetector(detectionCon=0.5, maxHands=1)


def get_gesture():
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
    elif totalFingers == 1 and fingers[2] == 1:
        return 0, "Fuck You"
    else:
        return 0, "Stop"


while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    gesture = (0, "Stop")

    if lmList:
        fingers = detector.fingersUp()
        totalFingers = fingers.count(1)
        wrist_x, wrist_y = lmList[0][0], lmList[0][1]
        joint_x, joint_y = lmList[3][0], lmList[3][1]
        thumb_x, thumb_y = lmList[4][0], lmList[4][1]
        index_x, index_y = lmList[8][0], lmList[8][1]
        middle_x, middle_y = lmList[12][0], lmList[12][1]
        gesture = get_gesture()
        cv2.putText(img, f'Fingers: {totalFingers}', (20, 120), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 0), 3)

    com.write(struct.pack("B", gesture[0]))
    # Display
    cv2.putText(img, gesture[1], (20, 70), cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 3)
    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
