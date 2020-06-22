import cv2
import numpy as np

img = cv2.imread("~/map-fusion/mapping_result_data/robot_frame_0_0_0.txt.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
edges = cv2.Canny(gray, 50, 150, apertureSize=3)

lines = cv2.HoughLines(edges, 1, np.pi/180, 200)

while(True):
    cv2.imshow('img', img)
    cv2.imshow('gray', gray)
    cv2.imshow('edges', edges)
    cv2.imshow('lines', lines)

    if cv2.waitKey(0) == ord('q'):
        break

cv2.destroyWindow()

