import cv2 
import numpy as np 
import os 
from PIL import Image 

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

recognizer = cv2.createLBPHFaceRecognizer()
