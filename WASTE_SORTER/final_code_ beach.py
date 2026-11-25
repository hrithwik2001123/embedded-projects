import os
from ultralytics import YOLO
import cv2
from picamera2 import Picamera2
import RPi.GPIO as GPIO
import time
from flask import Flask, render_template_string, Response
import threading


TRIG = 17
ECHO = 18
servo_pin = 22
servo_pin2 = 27
conver_pin1 = 21
conver_pin2 = 20
IN1 = 5
IN2 = 6
IN3 = 13
IN4 = 19



app = Flask(__name__)

picam = Picamera2()
picam.preview_configuration.main.size = (480, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

model_path = os.path.join('/home/pi/WASTE_SORTER', 'runs', 'detect', 'train', 'weights', 'best.pt')
model = YOLO(model_path)
threshold = 0.5

global organic_alert_sent
global inorganic_alert_sent

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)


GPIO.setup(servo_pin, GPIO.OUT)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)
GPIO.setup(servo_pin2, GPIO.OUT)
GPIO.setup(conver_pin1, GPIO.OUT)
GPIO.setup(conver_pin2, GPIO.OUT)


GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)

GPIO.output(IN1, GPIO.LOW)
GPIO.output(IN2, GPIO.LOW)
GPIO.output(IN3, GPIO.LOW)
GPIO.output(IN4, GPIO.LOW)

def backward():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.HIGH)
    GPIO.output(IN3, GPIO.LOW)
    GPIO.output(IN4, GPIO.HIGH)

def left():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.HIGH)
    GPIO.output(IN3, GPIO.HIGH)
    GPIO.output(IN4, GPIO.LOW)

def right():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.LOW)
    GPIO.output(IN4, GPIO.HIGH)


def stop():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.LOW)
    GPIO.output(IN4, GPIO.LOW)

def forward():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.HIGH)
    GPIO.output(IN4, GPIO.LOW)

def conver_control_on():
    GPIO.output(conver_pin1, GPIO.HIGH)
    GPIO.output(conver_pin2, GPIO.LOW)

def conver_control_off():
    GPIO.output(conver_pin1, GPIO.LOW)
    GPIO.output(conver_pin2, GPIO.LOW)

def detect():
    pwm = GPIO.PWM(servo_pin, 50)
    pwm.start(0)

    pwm2 = GPIO.PWM(servo_pin2, 50)
    pwm2.start(0)

    start_time = time.time()
    frame = None

    while time.time() - start_time < 5:
        frame = picam.capture_array()
        time.sleep(0.1)

    cv2.imwrite("captured_image.jpg", frame)

    frame = cv2.imread("captured_image.jpg")
    results = model(frame)[0]

    detected_objects = 0
    res = ""

    for result in results.boxes.data.tolist():
        x1, y1, x2, y2, score, class_id = result

        if score > threshold:
            detected_objects += 1

            cv2.rectangle(
                frame,
                (int(x1), int(y1)),
                (int(x2), int(y2)),
                (0, 255, 0),
                4
            )

            cv2.putText(
                frame,
                results.names[int(class_id)].upper(),
                (int(x1), int(y1 - 10)),
                cv2.FONT_HERSHEY_SIMPLEX,
                1.3,
                (0, 255, 0),
                3,
                cv2.LINE_AA
            )

            res = results.names[int(class_id)]

    if detected_objects > 0:
        print(f"{res} detected.")

        if res == "paper" or res == "apple" or res == "orange" or res == "watermelon" or res == "banana":
            print("Organic")

            pwm.ChangeDutyCycle(12.5)
            time.sleep(1)

            pwm.ChangeDutyCycle(2.5)
            time.sleep(1)

            pwm.stop()

        elif res == "bottle" or res == "pen" or res == "coin" or res == "spoon":
            print("In-Organic")

            pwm2.ChangeDutyCycle(12.5)
            time.sleep(1)

            pwm2.ChangeDutyCycle(2.5)
            time.sleep(1)

            pwm2.stop()
            time.sleep(1)

    cv2.imwrite("annotated_image.jpg", frame)
def generate_frames():
    while True:
        frame = picam.capture_array()

        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
# =========================
# WEB PAGE
# =========================

HTML = """
<!DOCTYPE html>
<html>
<head>
    <title>Robot Control</title>
    <style>
        body {
            text-align: center;
            font-family: Arial;
            background: #f2f2f2;
        }

        h1 {
            margin-top: 20px;
        }

        button {
            width: 150px;
            height: 60px;
            font-size: 18px;
            margin: 10px;
            border-radius: 10px;
            border: none;
            cursor: pointer;
        }

        img {
            margin-top: 20px;
            width: 700px;
            border-radius: 10px;
        }
    </style>
</head>
<body>

    <h1>Web Controlled Robot</h1>

    <div>
        <button onclick="location.href='/forward'">Forward</button><br>
        <button onclick="location.href='/left'">Left</button>
        <button onclick="location.href='/stop'">Stop</button>
        <button onclick="location.href='/right'">Right</button><br>
        <button onclick="location.href='/backward'">Backward</button>
    </div>

    <h2>Live Camera View</h2>
    <img src="/video_feed">

</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(HTML)

@app.route('/forward')
def move_forward():
    forward()
    return render_template_string(HTML)

@app.route('/backward')
def move_backward():
    backward()
    return render_template_string(HTML)

@app.route('/left')
def move_left():
    left()
    return render_template_string(HTML)

@app.route('/right')
def move_right():
    right()
    return render_template_string(HTML)

@app.route('/stop')
def move_stop():
    stop()
    return render_template_string(HTML)

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


def main():

    while True:
        GPIO.output(TRIG, False)
        time.sleep(0.00001)
        GPIO.output(TRIG, True)
        time.sleep(0.00001)
        GPIO.output(TRIG, False)
        
        pulse_start = time.time()
        pulse_end = time.time()
        
        while GPIO.input(ECHO) == 0:
            pulse_start = time.time()
        while GPIO.input(ECHO) == 1:
            pulse_end = time.time()
        
        pulse_duration = pulse_end - pulse_start
        distance = pulse_duration * 17150
        distance = round(distance, 2)
        print(distance)
        time.sleep(0.2)
        if distance <= 9:
            detect()
            time.sleep(5)

if __name__ == '__main__':
    sensor_thread = threading.Thread(target=main)
    sensor_thread.daemon = True
    sensor_thread.start()

    app.run(host='0.0.0.0', port=5000, debug=False)