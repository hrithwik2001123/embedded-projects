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
from datetime import timedelta
from flask import Flask, request, jsonify
from werkzeug.utils import secure_filename
from datetime import datetime
import logging

ip = "192.168.29.222"

picam = Picamera2()
picam.preview_configuration.main.size = (480, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

try:
    con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
    cmd = con.cursor()
    print("DB connected")
except pymysql.Error as e:
    print("Error connecting to MySQL:", e)


app = Flask(__name__, static_folder='/home/pi/WILD_ANIMAL_PROVIDENCE/static')

logging.basicConfig(level=logging.INFO)

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


@app.route('/login', methods=['POST'])
def logincheck():
    try:
        con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
        cmd = con.cursor()
        print("DB connected")
    except pymysql.Error as e:
        print("Error connecting to MySQL:", e)

    data = request.json

    user = data.get("email")
    password = data.get("password")

    cmd.execute(
        "SELECT * FROM login WHERE username=%s AND password=%s",
        (user, password)
    )

    result = cmd.fetchone()

    if result is None:
        return jsonify({'status': 'failed'}), 500

    return jsonify({
        'status': 'success',
        'lid': result[0],
        'usertype': result[3]
    })


@app.route('/user', methods=['POST'])
def register_user():
    try:
        con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
        cmd = con.cursor()
        print("DB connected")
    except pymysql.Error as e:
        print("Error connecting to MySQL:", e)

    data = request.get_json(force=True)

    first_name = data.get("firstName")
    email = data.get("email")
    contact = data.get("contact")
    password = data.get("password")

    try:

        cmd.execute(
            "INSERT INTO login(username,password,usertype) VALUES(%s,%s,'user')",
            (email, password)
        )

        login_id = cmd.lastrowid

        cmd.execute(
            "INSERT INTO registration(first_name,email,contact,login_id) VALUES(%s,%s,%s,%s)",
            (first_name, email, contact, login_id)
        )

        con.commit()

        return jsonify({"task": "success"})

    except Exception as e:

        con.rollback()

        return jsonify({"task": "failed", "error": str(e)})

@app.route('/get_animals', methods=['GET'])
def get_animals():
    try:
        query = "SELECT image_name, date,time FROM image "
        cmd.execute(query)
        animals_data = cmd.fetchall()

        if animals_data:
            response = {
                "status": "success",
                "animals": animals_data,
            }
        else:
            response = {
                "status": "no_data",
                "message": "No animal intrusion data found for this user.",
            }

        return jsonify(response)
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})

@app.route("/getwether", methods=['POST', 'GET'])
def getwether():
    try:
        con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
        cmd = con.cursor()
        print("DB connected")
    except pymysql.Error as e:
        print("Error connecting to MySQL:", e)
    # Execute the query to get the latest entry
    cmd.execute("SELECT * FROM whether ORDER BY date DESC, time DESC LIMIT 1")
    row = cmd.fetchone()

    if not row:
        return jsonify({"status": "no_data"})

    # Get column names from the cursor
    row_headers = [x[0] for x in cmd.description]

    # Convert the tuple to a dictionary
    row_dict = dict(zip(row_headers, row))

    # Convert timedelta objects to string (JSON-serializable)
    for key, value in row_dict.items():
        if isinstance(value, timedelta):
            row_dict[key] = str(value)
        if isinstance(value, datetime):
            row_dict[key] = value.strftime("%Y-%m-%d")

    return jsonify({"status": "success", "data": row_dict})

@app.route("/get_notifications", methods=['POST', 'GET'])
def getnotifications():
    try:
        con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
        cmd = con.cursor()
        print("DB connected")
    except pymysql.Error as e:
        print("Error connecting to MySQL:", e)
    
    # Execute the query
    cmd.execute("select * from notification ")
    rows = cmd.fetchall()
    print(rows, 'jjjjjjjjjjjjjjjjjjjj')

    # Get column names from the description of the cursor
    row_headers = [x[0] for x in cmd.description]  # x[0] gives column names

    # Create a list of dictionaries where each dictionary corresponds to a row
    json_data = []
    for result in rows:
        row_dict = dict(zip(row_headers, result))

        # Convert timedelta objects to strings or another JSON-serializable format
        for key, value in row_dict.items():
            if isinstance(value, timedelta):
                row_dict[key] = str(value)  # Convert timedelta to string (e.g., '1 day, 2:03:04')

        json_data.append(row_dict)

    print(json_data, 'ffffffffffffffff')

    # Return the JSON data as a response
    return jsonify(json_data)

@app.route('/get_previous_readings', methods=['GET'])
def get_previous_readings():
    try:
        con = pymysql.connect(host=ip, port=3306, user='root', password='root', db='first', charset='utf8')
        cmd = con.cursor()
        print("DB connected")
    except pymysql.Error as e:
        print("Error connecting to MySQL:", e)
    
        # Fetch last 5 entries ordered by date and time descending
    cmd.execute("SELECT * FROM whether ORDER BY date DESC, time DESC LIMIT 5")
    rows = cmd.fetchall()

        # Get column names
    columns = [col[0] for col in cmd.description]

        # Prepare JSON response
    readings = []
    for row in rows:
        row_dict = dict(zip(columns, row))
            # Convert timedelta to string
        for key, value in row_dict.items():
            if isinstance(value, timedelta):
                row_dict[key] = str(value)
        readings.append(row_dict)

    return jsonify({'status': 'success', 'readings': readings})
 


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
    threading.Thread(target=connect).start()


def capture_image():
    global frame
    timestamp = time.strftime("%Y%m%d_%H%M%S")
    image_filename = f"/home/pi/WILD_ANIMAL_PROVIDENCE/images/captured_image_{timestamp}.jpg"

    start_time = time.time()
    while time.time() - start_time < 5:
        frame = picam.capture_array()
        cv2.imshow('Live Detection', frame)
        cv2.waitKey(1)
    cv2.destroyAllWindows()
    cv2.imwrite(image_filename, frame)

    return image_filename


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
    global frame
    print("Running object detection...")
    img = cv2.imread(image_file)
    if img is None:
        print(f"Error: Could not read image file {image_file}")
        return "NONE"
    h, w, c = img.shape
    blob = cv2.dnn.blobFromImage(img, 1 / 255, (320, 320), [0, 0, 0], 1, crop=False)
    net.setInput(blob)
    layerNames = net.getLayerNames()
    outputNames = [layerNames[i - 1] for i in net.getUnconnectedOutLayers()]
    outputs = net.forward(outputNames)
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
    result = "NONE"
    if len(indices) > 0:
        for i in indices.flatten():
            box = bbox[i]
            x, y, w, h = box[0], box[1], box[2], box[3]
            res = classNames[classids[i]]
            if res in ["cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe"]:
                print(f"Detected {res}")
                timestamp = time.strftime("%Y%m%d_%H%M%S")
                image_filename = f"/home/pi/WILD_ANIMAL_PROVIDENCE/static/images/captured_image_{timestamp}.jpg"
                cv2.imwrite(image_filename, frame)
                new_image_filename=f"static/images/captured_image_{timestamp}.jpg"
                try:
                    query = "INSERT INTO notification (animal_type, date,time) VALUES (%s, CURDATE(),CURTIME())"
                    cmd.execute(query, (res))
                    querys = "INSERT INTO image (image_name,date,time) VALUES (%s,CURDATE(),CURTIME())"
                    cmd.execute(querys, (new_image_filename))
                    con.commit()
                    print("Image filename saved to database.")
                except Exception as e:
                    print(e)
                result = res
                break

    return result




def connect():
    app.run(host='0.0.0.0', port=5000)

if __name__ == "__main__":
    main()

