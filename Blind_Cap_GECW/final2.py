
import RPi.GPIO as gpio
from gtts import gTTS
import pytesseract
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
import serial
import pynmea2

app=Flask(__name__)

PRESET_LAT = 10.8505
PRESET_LON = 76.2710 

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

    camera = cv2.VideoCapture(0)
    
    face_flag=0
    while face_flag==0:
        try:
            
            start_time = time.time()
            while time.time() - start_time < 5:
                frame = picam.capture_array()
                cv2.imshow('Live Detection', frame)
                cv2.waitKey(1)
            cv2.imwrite("captured_image.jpg", frame)
            cv2.destroyAllWindows()
            frame = cv2.imread("captured_image.jpg")
            
            face_locations = face_recognition.face_locations(frame)
            face_encodings = face_recognition.face_encodings(frame, face_locations)

            for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
                matches = face_recognition.compare_faces(known_face_encodings, face_encoding, tolerance=0.6)

                name = "Unknown"

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
def get_gps_location():
    """Get GPS location with immediate fallback if not available"""
    try:
        gps = serial.Serial("/dev/serial0", baudrate=115200, timeout=3)
        
        for attempt in range(3):
            line = gps.readline().decode('ascii', errors='replace')
            if line.startswith('$GPGGA'):
                msg = pynmea2.parse(line)
                if hasattr(msg, 'latitude') and hasattr(msg, 'longitude'):
                    if msg.latitude and msg.longitude and msg.latitude != 0:
                        print(f"✅ GPS acquired: {msg.latitude}, {msg.longitude}")
                        return msg.latitude, msg.longitude
            time.sleep(1)
        
        print("⚠️ GPS not available, using preset location")
        return PRESET_LAT, PRESET_LON
        
    except Exception as e:
        print(f"⚠️ GPS error: {e}")
        print(f"📌 Using preset location: {PRESET_LAT}, {PRESET_LON}")
        return PRESET_LAT, PRESET_LON


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
        
        latitude, longitude = get_gps_location()
        
        # Create location message
        location_text = f"📍 Location: {latitude}, {longitude}"
        maps_link = f"https://maps.google.com/?q={latitude},{longitude}"
        
        # Send all emergency info
        bot.sendMessage(chat_id, "🚨 EMERGENCY ALERT 🚨")
        bot.sendMessage(chat_id, location_text)
        bot.sendMessage(chat_id, f"🗺️ {maps_link}")
        bot.sendPhoto(chat_id, photo=open(image_path, 'rb'))
        
        print(f"✅ Emergency sent - Location: {latitude}, {longitude}")
        speak("Emergency alert sent with location")
        
    except Exception as e:
        print(f"❌ Error sending emergency: {e}")
        # Fallback: send just location
        try:
            latitude, longitude = get_gps_location()
            maps_link = f"https://maps.google.com/?q={latitude},{longitude}"
            bot.sendMessage(chat_id, "🚨 EMERGENCY ALERT 🚨")
            bot.sendMessage(chat_id, f"📍 {latitude}, {longitude}")
            bot.sendMessage(chat_id, f"🗺️ {maps_link}")
            speak("Location sent")
        except:
            speak("Failed to send alert")
def readText():
    try:
        print("System is reading your image. Please wait.")
        #speak("System is reading your image. Please wait.")
        
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
            
            # Read the captured image
            frame = cv2.imread("captured_image_ocr.jpg")
            
            # Convert to grayscale
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            
            # Apply preprocessing to improve OCR
            gray = cv2.bilateralFilter(gray, 11, 17, 17)
            gray = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
            
            # Extract ALL text from the image
            text = pytesseract.image_to_string(gray, config='')
            
            # Remove extra whitespace and newlines
            text = text.strip()
            
            if text:
                print("Extracted Text:")
                print("=" * 50)
                print(text)
                print("=" * 50)
                speak(text)
                ocr_flag = 1
            else:
                print("No text detected. Capturing again...")
                time.sleep(1)
                
    except Exception as e:
        print("Warning:", e)
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
    obj_flag = 0
    dist = distance_check()
    
    while obj_flag == 0:
        try:
            # Display camera preview for 5 seconds and capture
            print("Detecting objects...")
            start_time = time.time()
            frame = None
            
            while time.time() - start_time < 5:
                frame = picam.capture_array()
                cv2.imshow('Object Detection - Looking for objects', frame)
                cv2.waitKey(1)
            
            if frame is None:
                print("Failed to capture image")
                continue
                
            # Save the captured frame
            cv2.imwrite("captured_image_obj.jpg", frame)
            cv2.destroyAllWindows()
            
            # Read the image for processing
            img = cv2.imread("captured_image_obj.jpg")
            
            if img is None:
                print("Failed to load captured image")
                continue
            
            # Prepare image for YOLO
            blob = cv2.dnn.blobFromImage(img, 1/255, (320, 320), [0, 0, 0], 1, crop=False)
            net.setInput(blob)
            
            # Get output layers
            layerNames = net.getLayerNames()
            outputNames = [layerNames[i - 1] for i in net.getUnconnectedOutLayers()]
            outputs = net.forward(outputNames)
            
            h, w, c = img.shape
            bbox = []
            classids = []
            conf = []
            
            # Process detections
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
            
            # Apply non-maximum suppression
            indices = cv2.dnn.NMSBoxes(bbox, conf, 0.5, 0.3)
            
            if len(indices) > 0:
                for i in indices:
                    i = i[0] if isinstance(i, (list, np.ndarray)) else i
                    box = bbox[i]
                    x, y, wd, ht = box[0], box[1], box[2], box[3]
                    detected_object = classNames[classids[i]]
                    print(f"Detected: {detected_object} at distance {round(dist, 2)} cm")
                    speak(f"{detected_object} detected in {round(dist, 2)} centimeters")
                    obj_flag = 1
                    break
            else:
                print("No objects detected")
                speak("No objects detected")
                obj_flag = 1  # Exit after one attempt or keep trying?
                # If you want to keep trying until object detected, use:
                # obj_flag = 0
                # time.sleep(1)
                
        except Exception as e:
            print(f"Error in detection: {e}")
            speak("Error in object detection")
            obj_flag = 1
            cv2.destroyAllWindows()

def distance_check():
    try:
        gpio.output(GPIO_TRIGGER, False)
        time.sleep(0.00001)
        gpio.output(GPIO_TRIGGER, True)
        time.sleep(0.00001)
        gpio.output(GPIO_TRIGGER, False)
        
        start_time = time.time()
        stop_time = time.time()
        
        # Timeout to prevent infinite loop
        timeout = time.time() + 1  # 1 second timeout
        
        while gpio.input(GPIO_ECHO) == 0 and time.time() < timeout:
            start_time = time.time()
            
        while gpio.input(GPIO_ECHO) == 1 and time.time() < timeout:
            stop_time = time.time()
            
        time_elapsed = stop_time - start_time
        
        if time_elapsed > 0:
            distance = (time_elapsed * 34300) / 2
            print(f"Distance: {distance} cm")
            return distance
        else:
            return 100  # Return default distance if measurement fails
            
    except Exception as e:
        print(f"Distance measurement error: {e}")
        return 100


if __name__ == "__main__":
    main()
    
