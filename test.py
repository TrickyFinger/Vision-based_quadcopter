
import numpy as np
import cv2
import matplotlib.pyplot as plt
import time


img_org = cv2.imread('cross.jpg')

gray = cv2.cvtColor(img_org, cv2.COLOR_BGR2GRAY)
ret, mask = cv2.threshold(gray, 180, 255, cv2.THRESH_BINARY)
img = cv2.medianBlur(mask, 5)

erosion = cv2.erode(img, (5, 5))
dilation = cv2.dilate(erosion, (5, 5))

edges = cv2.Canny(dilation, 50, 150, apertureSize = 3)
lines = cv2.HoughLinesP(edges, 1, np.pi/180, 20)

lines2D = lines[:, 0, :]
for x1, y1, x2, y2 in lines2D:
    cv2.line(edges, (x1,y1), (x2,y2), (0,255,0), 3)

print lines2D.shape
plt.imshow(edges)



plt.show()
