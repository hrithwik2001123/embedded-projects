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

try:
    con = pymysql.connect(host='192.168.29.222', port=3306, user='root', password='root', db='first', charset='utf8')
    cmd = con.cursor()
    print("DB connected")
except pymysql.Error as e:
    print("Error connecting to MySQL:", e)


app = Flask(__name__, static_folder='/home/pi/WILD_ANIMAL_PROVIDENCE/static')

user_login_id=1

logging.basicConfig(level=logging.INFO)

picam = Picamera2()
picam.preview_configuration.main.size = (480, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

buzzer = 16
pump = 21
dht_pin = 4
soil = 6
pir = 13

sensor = Adafruit_DHT.DHT11

temperature = 0
soil_status = None
pir_status = None

frame= ""
pump_status = {"state": "OFF"}

classesFile = '/home/pi/WILD_ANIMAL_PROVIDENCE/coco.names'
classNames = []
with open(classesFile, 'rt') as f:
    classNames = f.read().rstrip('\n').split('\n')

result = "NONE"
modelconfig = '/home/pi/WILD_ANIMAL_PROVIDENCE/yolov3tiny.cfg'
modelweight = '/home/pi/WILD_ANIMAL_PROVIDENCE/yolov3tiny.weights'
net = cv2.dnn.readNetFromDarknet(modelconfig, modelweight)


def main():
    global user_login_id
    global result
    global res
    global soil_status
    global temperature
    global humidity
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(buzzer, GPIO.OUT)
    GPIO.setup(pump, GPIO.OUT)
    GPIO.setup(soil, GPIO.IN)
    GPIO.setup(pir, GPIO.IN)
    GPIO.output(buzzer, False)
    GPIO.output(pump, False)
    threading.Thread(target=controll).start()
    threading.Thread(target=connect).start()

@app.route('/login', methods=['POST'])
def logincheck():

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

@app.route('/updateProfile/<int:user_id>', methods=['PUT'])
def update_profile(user_id):
    try:
        data = request.get_json()
        first_name = data.get('firstname')
        last_name = data.get('lastname')
        address = data.get('address')
        location = data.get('location')
        phone_number = data.get('phone')

        if not all([first_name, last_name, phone_number]):
            return jsonify({'message': 'First name, last name, and phone number are required!'}), 400

        cmd.execute("""
            UPDATE registration 
            SET first_name = %s, 
                last_name = %s, 
                address = %s, 
                location = %s, 
                phonenumber = %s 
            WHERE login_id = %s
        """, (first_name, last_name, address, location, phone_number, user_id))

        con.commit()

        return jsonify({
            'message': 'Profile updated successfully',
            'firstname': first_name,
            'lastname': last_name,
            'address': address,
            'location': location,
            'phone': phone_number
        }), 200

    except Exception as e:
        print(e)
        con.rollback()
        return jsonify({'message': f'Error updating profile: {str(e)}'}), 500

@app.route('/get_notifications/<user_id>', methods=['GET'])
def get_notifications(user_id):
    try:
        query = '''
            SELECT animal_name, timestamp
            FROM notifications
            WHERE user_id = %s
            ORDER BY timestamp DESC
        '''

        cmd.execute(query, (user_id,))
        notifications = cmd.fetchall()

        if notifications:
            return jsonify({'status': 'success', 'notifications': notifications}), 200
        else:
            return jsonify({'status': 'success', 'notifications': []}), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'error', 'message': str(e)}), 500
    
@app.route('/get_animals/<user_id>', methods=['GET'])
def get_animals(user_id):
    try:
        query = "SELECT animal_name, animal_image, timestamp FROM animals WHERE user_id = %s"
        cmd.execute(query, (user_id,))
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

    

@app.route('/readings', methods=['GET'])
def get_readings():
    global soil_status
    global temperature
    global humidity
    sensor_data = {
    "temperature": temperature,
    "humidity": humidity,
    "moisture": soil_status
}
    return jsonify(sensor_data)

@app.route('/pump/on', methods=['POST'])
def turn_pump_on():
    pump_status["state"] = "ON"
    GPIO.output(pump, True)
    return jsonify({"message": "Pump turned ON", "status": pump_status["state"]})

@app.route('/pump/off', methods=['POST'])
def turn_pump_off():
    pump_status["state"] = "OFF"
    GPIO.output(pump, False)
    return jsonify({"message": "Pump turned OFF", "status": pump_status["state"]})


def capture_image():
    global user_login_id,frame
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
    global frame
    global result
    global res
    global soil_status
    global temperature
    global humidity

    while True:
        humidity, temperature = Adafruit_DHT.read_retry(sensor, dht_pin)

        if humidity is not None and temperature is not None:
            print(f"Temperature: {temperature:.1f}°C | Humidity: {humidity}%")
        else:
            print("Failed to retrieve data from sensor!")
        time.sleep(2)
        
        soil_reading = GPIO.input(soil)
        pir_reading = GPIO.input(pir)
        print(f"Soil reading: {soil_reading}, PIR reading: {pir_reading}")
        if pir_reading == 1:
            print("Motion detected, capturing image...")
            image_file = capture_image()
            if image_file:
                obj = detect(image_file)
                print(f"Detected object: {obj}")
                if obj != "NONE":
                    GPIO.output(buzzer, True)
                    time.sleep(2)
                    GPIO.output(buzzer, False)
            else:
                print("Failed to capture image, skipping detection.")
        else:
            GPIO.output(buzzer, False)
        soil_status = "HIGH" if soil_reading == 0 else "LOW"


def detect(image_file):
    global user_login_id,frame
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
                    query = "INSERT INTO notifications (user_id, animal_name, timestamp) VALUES (%s, %s, CURRENT_TIMESTAMP)"
                    cmd.execute(query, (user_login_id,res))
                    querys = "INSERT INTO animals (user_id, animal_name,animal_image,timestamp) VALUES (%s, %s, %s, CURRENT_TIMESTAMP)"
                    cmd.execute(querys, (user_login_id,res,new_image_filename))
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
