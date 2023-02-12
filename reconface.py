import cv2 
import numpy as np 
import face_recognition

video_capture = cv2.VideoCapture(0)

# Carregando e reconhecendo a face do usuário 1.
user1_image = face_recognition.load_image_file("./img/180065416.jpg")
user1_face_encoding = face_recognition.face_encodings(user1_image)[0]

# Carregando e reconhecendo a face do usuário 2.
user2_image = face_recognition.load_image_file("./img/180034090.jpg")
user2_face_encoding = face_recognition.face_encodings(user2_image)[0]

# Criando array de associação das facer reconhecidas.
known_face_encodings = [
    user1_face_encoding,
    user2_face_encoding
]
known_face_names = [
    "180065416",
    "180034090"
]

# Initialize some variables
face_locations = []
face_encodings = []
face_names = []
process_this_frame = True


while True:
    # Captura de um print da webcam
    ret, frame = video_capture.read()

    if process_this_frame:
        # Redimensionando o print pra acelerar o processamento
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)

        # convertendo imagem pra RGB
        rgb_small_frame = small_frame[:, :, ::-1]
        
        # Encontrando faces no frame da webcam
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)

        face_names = []
        for face_encoding in face_encodings:
            # Comparando faces encontradas com Faces conhecidas.
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"

            # Escolhe a face mais proxima
            face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)
            if matches[best_match_index]:
                name = known_face_names[best_match_index]

            face_names.append(name)

    process_this_frame = not process_this_frame


#    # Display the results
#    for (top, right, bottom, left), name in zip(face_locations, face_names):
#        # Scale back up face locations since the frame we detected in was scaled to 1/4 size
#        top *= 4
#        right *= 4
#        bottom *= 4
#        left *= 4
#
#        # Draw a box around the face
#        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
#
#        # Draw a label with a name below the face
#        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
#        font = cv2.FONT_HERSHEY_DUPLEX
#        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
#
#    # Display the resulting image
#    cv2.imshow('Video', frame)
#
#    # Hit 'q' on the keyboard to quit!
#    if cv2.waitKey(1) & 0xFF == ord('q'):
#        break
#
## Release handle to the webcam
#video_capture.release()
#cv2.destroyAllWindows()
