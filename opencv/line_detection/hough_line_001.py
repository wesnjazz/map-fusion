import cv2
import numpy as np

img = cv2.imread("/home/dpark/map-fusion/mapping_result_data/robot_frame_0_0_0.txt.jpg")
edges = cv2.Canny(img, 5, 150, apertureSize=7)

lines = cv2.HoughLines(edges, 1, np.pi/180, 200)
for line in lines:
    rho,theta = line[0]
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho
    x1 = int(x0 + 1000*(-b))
    y1 = int(y0 + 1000*(a))
    x2 = int(x0 - 1000*(-b))
    y2 = int(y0 - 1000*(a))
    cv2.line(img,(x1,y1),(x2,y2),(0,0,255),2)

cv2.namedWindow('img', cv2.WINDOW_NORMAL)
cv2.resizeWindow('img', 1024, 768)
cv2.namedWindow('edges', cv2.WINDOW_NORMAL)
cv2.resizeWindow('edges', 1024, 768)

while True:
    cv2.imshow('img', img)
    cv2.imshow('edges', edges)

    if cv2.waitKey(0) == ord('q'):
        break

cv2.destroyAllWindows()

