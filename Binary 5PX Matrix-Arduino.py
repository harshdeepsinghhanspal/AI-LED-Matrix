import cv2
import numpy as np
import serial

# Initialize Serial Communication with Arduino
arduino = serial.Serial('COM8', 9600)  # Change 'COM8' to the correct port of Arduino

#No of PIXELS aka LEDs in LED Matrix
px_val = 4

w = 480
h = 480
capture = cv2.VideoCapture(0)
capture.set(3,w)
capture.set(4,h)

while (True):

    (ret, frame) = capture.read()

    grayFrame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    (thresh, blackAndWhiteFrame) = cv2.threshold(grayFrame, 127, 255, cv2.THRESH_BINARY)

    cv2.imshow('video bw', blackAndWhiteFrame)
    cv2.imshow('video original', frame)

    resizedBnW = cv2.resize(blackAndWhiteFrame, (px_val, px_val))

    binaryMatrix = np.where(resizedBnW == 255, 1, 0)
    print("5x5 Binary Matrix:")
    print(binaryMatrix)

    flattened = binaryMatrix.flatten()
    data_string = ','.join(map(str, flattened))

    # Send the values to Arduino
    arduino.write(f"{data_string}\n".encode())

    if cv2.waitKey(1) == 27:
        break

capture.release()
cv2.destroyAllWindows()