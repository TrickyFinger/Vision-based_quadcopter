from cross_locate import CrossLocate
from USBcamRead import USBcamStream
import matplotlib.pyplot as plt
import cv2
import numpy as np

cam = USBcamStream(src=0).start()

while(1):
    frame = cam.read()
    frame_org = CrossLocate(frame)
    frame_binary = frame_org.gray2binary(frame)
    try:
        lines, contours = frame_org.findContours(frame_binary, frame)
    except TypeError:
        continue
    else:
        k = cv2.waitKey(1)
        if k == 27:
            break

        cv2.imshow('cam', contours)
        print lines
        print '/n'

cv2.destroyAllWindows()
cam.stop()
