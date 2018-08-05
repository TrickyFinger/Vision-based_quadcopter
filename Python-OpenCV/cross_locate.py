import numpy as np
import cv2

class CrossLocate:
    def __init__(self, frame_src):
        rows, cols, chs = frame_src.shape
        #print rows, cols

    #convert gray image to binary image
    def gray2binary(self, frame_src):
        gray = cv2.cvtColor(frame_src, cv2.COLOR_BGR2GRAY)
        ret, binary = cv2.threshold(gray, 160, 255, cv2.THRESH_BINARY)
        img_blurred = cv2.medianBlur(binary, 5)
        return img_blurred

    #find contours, apply erosion and dilation to fill in small holes
    def findContours(self, binary_img, frame_draw):
        #erosion = cv2.erode(binary_img, (2, 2), iterations=2)
        dilation = cv2.dilate(binary_img, (5, 5), iterations=2)
        #canny edges detection
        edges = cv2.Canny(dilation, 50, 150, apertureSize=3)
        #hough lines detection
        lines = cv2.HoughLinesP(edges, 1, np.pi / 180, 100, 100, 30)

        try:
            lines2D = lines[:, 0, :]
        except TypeError:
            print 0
        else:
            for x1, y1, x2, y2 in lines2D:
                cv2.line(frame_draw, (x1, y1), (x2, y2), (0, 0, 255), 2)
            return lines2D, frame_draw

    #get the coordinate of the cross center
    def centerCoordinate(self, lines2D):
        #create a matrix km to store the info of each line, k=ramp, m = distence to 0 in y axis
        rows, _ = lines2D.shape
        km = np.zeros(rows, 2)

        nums = 0
        for x1, y1, x2, y2 in lines2D:
            km[nums][0] = (y2-y1)/(x2-x1)
            km[nums][1] = (x2*y1-x1*y2)/(x2-x1)
            nums += 1

        #blur the ks and ds to reduce the number of lines
        for i in range(0, nums-1, 1):
            for j in range(i+1, nums, 1):
                if abs(km[i][0]-k[j][0]) < 2:
                    k[j] = k[i]
                    if abs(d[i]-d[j]) < 3:
                        d[j] = d[i]

