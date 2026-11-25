import RPi.GPIO as GPIO
import time
import threading
import os
import numpy as np
import cv2
import serial
import random
import datetime
import Adafruit_DHT
import pymysql
from picamera2 import Picamera2
picam = Picamera2()
picam.preview_configuration.main.size = (480, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

# MySQL database connection
try:
    con = pymysql.connect(host='10.235.204.225', port=3306, user='root', passwd='root', charset='utf8', db='first')
    cmd = con.cursor()
    print("DB connected successfully")
except Exception as e:
    print("Not connected to DB:", e)

os.system("sudo service motion stop")

# GPIO Pin Setup
buzzer = 16
pump = 21
light=20
dht_pin = 4
soil = 6
pir = 13
sensor = Adafruit_DHT.DHT11
command = 0
temperature = 0
soil_status = None
pir_status = None
soil_flag=0

# YOLO model setup
classesFile = '/home/pi/WILD_ANIMAL_PROVIDENCE/coco.names'
classNames = []
with open(classesFile, 'rt') as f:
    classNames = f.read().rstrip('\n').split('\n')

result = "NONE"
modelconfig = '/home/pi/WILD_ANIMAL_PROVIDENCE/yolov3tiny.cfg'
modelweight = '/home/pi/WILD_ANIMAL_PROVIDENCE/yolov3tiny.weights'
net = cv2.dnn.readNetFromDarknet(modelconfig, modelweight)


def main():
    global result
    global res
    global soil_status
    global temperature
    global humidity

    # GPIO setup
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(buzzer, GPIO.OUT)
    GPIO.setup(pump, GPIO.OUT)
    GPIO.setup(light, GPIO.OUT)
    GPIO.setup(soil, GPIO.IN)
    GPIO.setup(pir, GPIO.IN)
    GPIO.output(buzzer, False)
    GPIO.output(pump, False)
    GPIO.output(light, False)
    threading.Thread(target=controll).start()


def capture_image():
    # Capture and save the image when PIR sensor detects motion
    timestamp = time.strftime("%Y%m%d_%H%M%S")  # Create a unique filename based on the timestamp
    image_filename = f"/home/pi/WILD_ANIMAL_PROVIDENCE/images/captured_image_{timestamp}.jpg"

    start_time = time.time()
    while time.time() - start_time < 5:
        frame = picam.capture_array()
        cv2.imshow('Live Detection', frame)
        cv2.waitKey(1)
    cv2.destroyAllWindows()
            # Save the captured frame as an image
    cv2.imwrite(image_filename, frame)

    # Insert image filename into database
    #try:
     #   query = "INSERT INTO imagedata (image_name) VALUES (%s)"
      #  cmd.execute(query, (image_filename,))
      #  con.commit()
       # print("Image filename saved to database.")
    #except Exception as e:
       # print(f"Error inserting image filename into DB: {e}")

    return image_filename  # Return the image file path


def controll():
    global result
    global res
    global soil_status
    global temperature
    global humidity

    count = 0
    cnt = 0
    global soil_flag
    while True:

        # Read temperature and humidity from the DHT11 sensor
        humidity, temperature = Adafruit_DHT.read_retry(sensor, dht_pin)

        if humidity is not None and temperature is not None:
            print(f"Temperature: {temperature:.1f}°C | Humidity: {humidity}%")
        else:
            print("Failed to retrieve data from sensor!")
        time.sleep(2)

        # Read soil and PIR sensor status
        soil_reading = GPIO.input(soil)
        pir_reading = GPIO.input(pir)
        if  soil_reading==1 and soil_flag==0:
            soil_flag=1
            GPIO.output(pump, True)
        if  soil_reading==0 and soil_flag==1:
            soil_flag=0
            GPIO.output(pump,False)
            
        print(f"Soil reading: {soil_reading}, PIR reading: {pir_reading}")

        if pir_reading == 1:  # PIR sensor triggered (motion detected)
            print("Motion detected, capturing image...")
            # Capture an image when PIR is triggered
            image_file = capture_image()

            if image_file:  # Only proceed if the image was successfully captured
                # Run object detection (YOLO) on the captured image
                obj = detect(image_file)
                print(f"Detected object: {obj}")

                if obj != "NONE":
                    GPIO.output(buzzer, True)
                    GPIO.output(light,True)
                    time.sleep(10)
                    GPIO.output(buzzer, False)
                    GPIO.output(light,False)
            else:
                print("Failed to capture image, skipping detection.")

        else:
            # Reset outputs when no motion detected
            GPIO.output(buzzer, False)

        # Check soil status and update database
        soil_status = "HIGH" if soil_reading == 0 else "LOW"
        try:
            cmd.execute(f"INSERT INTO whether VALUES (NULL, '{temperature}', '{humidity}', '{soil_status}', CURDATE(), CURTIME())")
            con.commit()
        except Exception as e:
            print(f"Error inserting data into DB: {e}")


def detect(image_file):
    # Load YOLO model and perform detection on the captured image
    print("Running object detection...")

    # Read the image
    img = cv2.imread(image_file)

    if img is None:  # Check if the image was loaded successfully
        print(f"Error: Could not read image file {image_file}")
        return "NONE"  # Return "NONE" if the image is invalid

    h, w, c = img.shape

    # Pre-process image for YOLO
    blob = cv2.dnn.blobFromImage(img, 1 / 255, (320, 320), [0, 0, 0], 1, crop=False)
    net.setInput(blob)

    # Get the output layer names
    layerNames = net.getLayerNames()
    outputNames = [layerNames[i - 1] for i in net.getUnconnectedOutLayers()]

    # Perform a forward pass to detect objects
    outputs = net.forward(outputNames)

    bbox = []
    classids = []
    conf = []

    # Process the detected objects
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

    # Apply Non-Maximum Suppression to remove redundant boxes
    indices = cv2.dnn.NMSBoxes(bbox, conf, 0.5, 0.3)

    result = "NONE"
    if len(indices) > 0:
        for i in indices.flatten():
            box = bbox[i]
            x, y, w, h = box[0], box[1], box[2], box[3]
            res = classNames[classids[i]]

            # If detected object is one of the target animals
            if res in ["cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe"]:
                print(f"Detected {res}")
                result = res
                break

    return result




if __name__ == "__main__":
    main() 