import cv2 
import numpy as np 
import face_recognition

video_capture = cv2.VideoCapture(0)

def generate_face_encodings(file):
    with open(file, "r") as f:
        lines = f.readlines()

    known_face_encodings = []
    for line in lines:
        matricula = line.strip()
        image_path = f"./image/{matricula}.jpg"
        image = face_recognition.load_image_file(image_path)
        encoding = face_recognition.face_encodings(image)[0]
        known_face_encodings.append(encoding)

    return known_face_encodings

def read_file(file):
    with open(file, "r") as f:
        lines = f.readlines()
    return [line.strip() for line in lines]

known_face_names = read_file("mat.txt")

known_face_encodings = generate_face_encodings("mat.txt")

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
            name = "Desconhecido"
            # Escolhe a face mais proxima
            face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)
            if matches[best_match_index]:
                name = known_face_names[best_match_index]
            face_names.append(name)            
        if "Unknown" not in face_names:
            with open("resultado.txt", "w") as f:
                for name in face_names:
                    index = known_face_names.index(name)
                    f.write(name + " " + str(index) + "\n")
            break
    process_this_frame = not process_this_frame

