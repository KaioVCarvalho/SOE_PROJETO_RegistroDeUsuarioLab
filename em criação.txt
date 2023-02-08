### Instalações necessárias 
pip install dlib

pip intall pillow

pip intal face_recongnition -no - cache-dir


#### Configurar um diretório Face_images:

Face_Images deve ter subdiretórios com o nome da pessoa que deve ser reconhecida e algumas fotos de exemplo dela dentro dele.

Você deve renomear a pasta com o nome da pessoa que você está reconhecendo 5 fotos para cada pessoa.

#### Importando bibliotecas 

import cv2 #For Image processing

import numpy as np #For converting Images to Numerical array

import os #To handle directories

from PIL import Image #Pillow lib for handling images

##### USANDO haarcascade_frontalface_default.xml para detectar os rostos nas imagens.


 Certifique-se de ter colocado este arquivo xml na pasta do projeto, caso contrário, ocorrerá um erro. 

Encontrado nesse link:
https://github.com/kipr/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml



face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

recognizer = cv2.createLBPHFaceRecognizer()


https://www.lojamundi.com.br/Reconhecimento-facial-em-tempo-real-com-Raspberry-Pi-e-OpenCV


https://medium.com/cwi-software/reconhecimento-facial-com-raspberry-pi-c4f8579dd640


https://github.com/camilaheinzmann/face-recognition-iot


https://github.com/ageitgey/face_recognition/blob/master/examples/facerec_from_webcam.py
