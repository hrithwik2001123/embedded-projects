import RPi.GPIO as GPIO
import time
import threading
import os
import numpy as np
from picamera2 import Picamera2
import cv2
import serial
import random
import datetime
import Adafruit_DHT
import pymysql 
try:
    con=pymysql.connect(host='192.168.0.159',port=3306,user='root',passwd='root',charset='utf8',db='wildanimalprovi')
    cmd=con.cursor()
    print("db connected successfuly")
except Exception as e:
    print("not connected to db",e)
    
os.system("sudo service motion stop")


stat_led = 21
data_led = 20
buzzer = 16
light = 17
pump=27
dht_pin = 4 
soil = 6
pir = 13
sensor = Adafruit_DHT.DHT11
command = 0
temperature=0
soil_status=None
pir_status=None

classesFile = '//home//pi//WILD_ANIMAL_PROVIDENCE//coco.names'
classNames = []
with open(classesFile, 'rt') as f:
    classNames = f.read().rstrip('\n').split('\n')

result = "NONE"
modelconfig = '//home//pi//WILD_ANIMAL_PROVIDENCE//yolov3tiny.cfg'
modelweight = '//home//pi//WILD_ANIMAL_PROVIDENCE//yolov3tiny.weights'
net = cv2.dnn.readNetFromDarknet(modelconfig, modelweight)



        
def main():
    global result
    global res
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(stat_led,GPIO.OUT)
    GPIO.setup(data_led,GPIO.OUT)
    GPIO.setup(buzzer,GPIO.OUT)
    GPIO.setup(light,GPIO.OUT)
    GPIO.setup(pump,GPIO.OUT)
    GPIO.setup(soil,GPIO.IN)
    GPIO.setup(pir,GPIO.IN)
    GPIO.output(buzzer,False)
    GPIO.output(pump,False)
    GPIO.output(light,False)
    threading.Thread(target=buffering).start()
    threading.Thread(target=controll).start()



def capture():
    cv2.imwrite('/home/pi/WILD_ANIMAL_PROVIDENCE/images/sj.png')
   
def controll():
    global result
    global res
    global soil_status
    global temperature
    global humidity
    count=0
    cnt=0
    while(1):
        humidity, temperature = Adafruit_DHT.read_retry(sensor, dht_pin)

        if humidity is not None and temperature is not None:
            print("Temperature: {:.1f}°C | Humidity: {}%".format(temperature, humidity))
        else:
            print("Failed to retrieve data from sensor!")
        time.sleep(2)
        soil_reading=GPIO.input(soil)
        print(soil_reading)
        pir_reading=GPIO.input(pir)
        if pir_reading==0:
            GPIO.output(data_led,True)
            print("ok")
            obj = detect()
            print(obj)
            if obj != "NONE":
                GPIO.output(light,True)
                GPIO.output(buzzer,True)
                time.sleep(2)
                GPIO.output(light,False)
                GPIO.output(buzzer,False)
        else:
            GPIO.output(light,False)
            GPIO.output(buzzer,False)
            GPIO.output(data_led,False)
        soil_status=""
        if soil_reading==0:
            soil_status="HIGH"
        else:
            soil_status="LOW"
        try:
            cmd.execute("insert into datas values(null,'"+str(temperature)+"','"+str(humidity)+"','"+soil_status+"',curdate(),curtime())")
            con.commit()
        except Exception as e:
            print(e)
            
   




import cv2
import numpy as np
import time

def detect():
    print("Opening camera for 5 seconds...")

    # Open the camera (1 is the default camera index, use 0 or 2 if needed)
    cap = cv2.VideoCapture(1)

    # Check if the camera was successfully opened
    if not cap.isOpened():
        print("Error: Camera not found!")
        return "NONE"

    # Let the camera warm up for a second
    time.sleep(1)

    # Wait for 5 seconds before capturing the image
    start_time = time.time()
    while time.time() - start_time < 5:
        # Capture frame-by-frame
        ret, img = cap.read()

        if not ret:
            print("Error: Failed to capture image.")
            continue

        # Display the frame (optional, for debugging)
        cv2.imshow("Capturing Image", img)

        # Wait for 'q' key to be pressed to exit early (optional)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Capture and save the image after 5 seconds
    timestamp = time.strftime("%Y%m%d_%H%M%S")  # To make the filename unique
    image_filename = f"captured_image_{timestamp}.jpg"
    cv2.imwrite(image_filename, img)
    print(f"Image captured and saved as {image_filename}")

    # Release the camera and close all windows
    cap.release()
    cv2.destroyAllWindows()

    return image_filename

# Call the function to capture and store the image
captured_image = detect()


    
     
def buffering():
    while(1):
        GPIO.output(stat_led,True)
        time.sleep(0.2)
        GPIO.output(stat_led,False)
        time.sleep(0.2)   
if __name__=="__main__":
    main()
