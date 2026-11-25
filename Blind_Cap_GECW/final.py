
import RPi.GPIO as gpio
from gtts import gTTS
import pytesseract as pya
import face_recognition
from picamera2 import Picamera2
import os
import cv2
import time
import telepot
import threading
import numpy as np
import serial
from flask import *
from PIL import Image
from werkzeug.utils import secure_filename
from datetime import datetime
import logging

app=Flask(__name__)

UPLOAD_FOLDER = 'static/faces'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg'}

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

chat_id = 1895133244


command = 0
bot = telepot.Bot('8442045470:AAF_PadOriRxX84dVXbiXbZz-NoMjBFWseA')


picam = Picamera2()
picam.preview_configuration.main.size = (480, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

help_btn = 16
obj_btn = 20
ocr_btn = 21
face_btn = 26

GPIO_TRIGGER = 17
GPIO_ECHO = 18


flag1=0
flag2=0
flag3=0
flag4=0

classesFile = '/home/pi/Blind_Cap_GECW/coco.names'
classNames = []
with open(classesFile, 'rt') as f:
    classNames = f.read().rstrip('\n').split('\n')

modelconfig = '/home/pi/Blind_Cap_GECW/yolov3tiny.cfg'
modelweight = '/home/pi/Blind_Cap_GECW/yolov3tiny.weights'
net = cv2.dnn.readNetFromDarknet(modelconfig, modelweight)

known_face_encodings = []
known_face_names = []

logging.basicConfig(level=logging.INFO)


def load_known_faces():
    global known_face_encodings,known_face_names
    voter_image_dir = r'/home/pi/Blind_Cap_GECW/static/faces'
    for image_filename in os.listdir(voter_image_dir):
        voter_name = os.path.splitext(image_filename)[0]
        image_path = os.path.join(voter_image_dir, image_filename)
        voter_image = face_recognition.load_image_file(image_path)
        voter_face_encoding = face_recognition.face_encodings(voter_image)[0]
        known_face_encodings.append(voter_face_encoding)
        known_face_names.append(voter_name)
        print("face loaded")
load_known_faces()

def face_check():
    print("System is going to check face authentication")
    print("Please look at the camera")

    # Initialize system camera (use 0 for default camera)
    camera = cv2.VideoCapture(0)
    
    face_flag=0
    while face_flag==0:
        try:
            # Display camera preview for 5 seconds
            start_time = time.time()
            while time.time() - start_time < 5:
                frame = picam.capture_array()
                cv2.imshow('Live Detection', frame)
                cv2.waitKey(1)
            # Save the captured frame as an image
            cv2.imwrite("captured_image.jpg", frame)
            # Close all windows
            cv2.destroyAllWindows()
            # Read the saved image
            frame = cv2.imread("captured_image.jpg")
            

            # Find all face locations and face encodings in the current frame
            face_locations = face_recognition.face_locations(frame)
            face_encodings = face_recognition.face_encodings(frame, face_locations)

            for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
                # Compare face_encoding with known_face_encodings
                matches = face_recognition.compare_faces(known_face_encodings, face_encoding, tolerance=0.6)

                name = "Unknown"

                # Check if there's a match
                if True in matches:
                    match_index = matches.index(True)
                    name = known_face_names[match_index]
                    if name:
                        print(name)
                        speak(name)
                        face_flag=1
                else:
                    print(name)
                    speak(name)
                    face_flag=1
        except Exception as e:
            print(e)
    
    
                        
def main():
    global flag1,flag2,flag3,flag4
    gpio.setwarnings(False)
    gpio.setmode(gpio.BCM)
    gpio.setup(face_btn, gpio.IN)
    gpio.setup(ocr_btn, gpio.IN)
    gpio.setup(obj_btn, gpio.IN)
    gpio.setup(help_btn, gpio.IN)
    gpio.setup(GPIO_TRIGGER, gpio.OUT)
    gpio.setup(GPIO_ECHO, gpio.IN)

    global bot
    global chat_id
    bot.message_loop(handle)
    print('i am listening')
    bot.sendMessage(chat_id,"Welcome")
    
    speak("Welcome to the Smart Assistive System for the Blind")
    print("Welcome to the Smart Assistive System for the Blind")
    while True:
        help_val = gpio.input(help_btn)
        obj_val = gpio.input(obj_btn)
        ocr_val = gpio.input(ocr_btn)
        face_val = gpio.input(face_btn)

        if ocr_val == 0:
            flag1 = 1
        if ocr_val == 1 and flag1 == 1:
            flag1 = 0
            print("System is going to read text")
            speak("System is going to read text")
            readText()

        if obj_val == 0:
            flag2 = 1
        if obj_val == 1 and flag2 == 1:
            flag2 = 0
            print("System is going to detect objects in front of you")
            speak("System is going to detect objects in front of you")
            detect()

        if help_val == 0:
            flag3 = 1
        if help_val == 1 and flag3 == 1:
            flag3 = 0
            print("emergency")
            send_emergency_image()
            time.sleep(1)

        if face_val == 0:
            flag4 = 1
        if face_val == 1 and flag4 == 1:
            flag4 = 0
            print("System is going to check face")
            speak("System is going to check face")
            face_check()

def handle(msg):
    global chat_id
    global command
    global bot
    chat_id = msg['chat']['id']
    command = msg['text']
    print(chat_id)
    print(command)
    if command == 'hai':
        bot.sendMessage(chat_id,'Hai')
    else:
        bot.sendMessage(chat_id, 'Try something else') 

def send_emergency_image():
    global bot, chat_id

    try:
        speak("Sending emergency alert")

        start_time = time.time()
        while time.time() - start_time < 3:
            frame = picam.capture_array()
            cv2.imshow('Emergency Capture', frame)
            cv2.waitKey(1)

        image_path = "emergency.jpg"
        cv2.imwrite(image_path, frame)
        cv2.destroyAllWindows()

        bot.sendMessage(chat_id, "🚨 EMERGENCY ALERT 🚨")
        bot.sendPhoto(chat_id, photo=open(image_path, 'rb'))

        print("Emergency image sent")

    except Exception as e:
        print("Error sending emergency image:", e)


def readText():
    try:
        print("System is reading your image. Please wait.")
        #speak("System is reading your image. Please wait.")
        caps = cv2.VideoCapture(0)
        ocr_flag = 0
        while ocr_flag == 0:
            # Display camera preview for 5 seconds
            start_time = time.time()
            while time.time() - start_time < 5:
                frame = picam.capture_array()
                cv2.imshow('Live Detection', frame)
                cv2.waitKey(1)
            # Save the captured frame as an image
            cv2.imwrite("captured_image_ocr.jpg", frame)
            # Close all windows
            cv2.destroyAllWindows()
            frame = cv2.imread("captured_image.jpg")
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            gray = cv2.bilateralFilter(gray, 11, 17, 17)
            text = pya.image_to_string(gray, config='')
            if text:
                print(text)
                speak(text)
                ocr_flag=1
    except Exception as e:
        print("Warning:", e)
        caps.release()
        cv2.destroyAllWindows()

def readImg():
    try:
        print("System is reading your image. Please wait.")
        speak("System is reading your image. Please wait.")
        caps = cv2.VideoCapture(0)
        img_flag = 0
        while img_flag == 0:
            # Display camera preview for 5 seconds
            start_time = time.time()
            while time.time() - start_time < 5:
                frame = picam.capture_array()
                cv2.imshow('Live Detection', frame)
                cv2.waitKey(1)
            # Save the captured frame as an image
            cv2.imwrite("captured.jpg", frame)
            # Close all windows
            cv2.destroyAllWindows()
            img = Image.open("captured.jpg")
            inputs = processor(img, return_tensors="pt")
            out = model.generate(**inputs)
            caption = processor.decode(out[0], skip_special_tokens=True)
            print(caption)
            if caption:
                print(caption)
                speak(caption)
                img_flag=1
    except Exception as e:
        print("Warning:", e)
        caps.release()
        cv2.destroyAllWindows()


def speak(text):
    myobj = gTTS(text=text, lang='en', slow=False)
    myobj.save("/home/pi/Blind_Cap_GECW/speech.mp3")
    os.system("mpg321 /home/pi/Blind_Cap_GECW/speech.mp3")


def detect():
    cap = cv2.VideoCapture(0)
    obj_flag = 0
    dist = distance_check()
    while obj_flag == 0:
        # Display camera preview for 5 seconds
        start_time = time.time()
        while time.time() - start_time < 5:
            img = picam.capture_array()
            cv2.imshow('Live Detection', img)
            cv2.waitKey(1)
        # Save the captured frame as an image
        cv2.imwrite("captured_image.jpg", img)
        # Close all windows
        cv2.destroyAllWindows()
        img = cv2.imread("captured_image.jpg")
        blob = cv2.dnn.blobFromImage(img, 1/255, (320, 320), [0, 0, 0], 1, crop=False)
        net.setInput(blob)
        layerNames = net.getLayerNames()
        a = net.getUnconnectedOutLayers()
        outputNames = [layerNames[i[0] - 1] for i in net.getUnconnectedOutLayers()]
        outputs = net.forward(outputNames)
        h, w, c = img.shape
        bbox = []
        classids = []
        conf = []
        for output in outputs:
            for det in output:
                score = det[5:]
                classid = np.argmax(score)
                confidence = score[classid]
                if confidence > 0.4:
                    wd, ht = int(det[2] * w), int(det[3] * h)
                    x, y = int((det[0] * w) - wd / 2), int((det[1] * h) - ht / 2)
                    bbox.append([x, y, wd, ht])
                    classids.append(classid)
                    conf.append(float(confidence))
        indices = cv2.dnn.NMSBoxes(bbox, conf, 0.5, 0.3)
        for i in indices:
            i = i[0]
            box = bbox[i]
            x, y, w, h = box[0], box[1], box[2], box[3]
            res=classNames[classids[i]]
            print(res)
            speak(res + " detected in "+str(round(dist,2))+" centimeter")
            obj_flag = 1

def distance_check():
    gpio.output(GPIO_TRIGGER, False)
    time.sleep(0.00001)
    gpio.output(GPIO_TRIGGER, True)
    time.sleep(0.00001)
    gpio.output(GPIO_TRIGGER, False)
    start_time = time.time()
    stop_time = time.time()
    while gpio.input(GPIO_ECHO) == 0:
        start_time = time.time()
    while gpio.input(GPIO_ECHO) == 1:
        stop_time = time.time()
    time_elapsed = stop_time - start_time
    distance = (time_elapsed * 34300) / 2
    print(distance)
    return distance



if __name__ == "__main__":
    main()
    
