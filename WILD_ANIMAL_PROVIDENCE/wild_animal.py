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
            
   
        
def detect():
    print("a")
    global result
    global res
    cap = cv2.VideoCapture(0)
    o_c = 0
    obj_flag = 0
    while obj_flag == 0:
        res, img = cap.read()
        print(o_c)
        blob = cv2.dnn.blobFromImage(img, 1/255, (320, 320), [0, 0, 0], 1, crop=False)
        net.setInput(blob)
        layerNames = net.getLayerNames()
        a = net.getUnconnectedOutLayers()
        outputNames = [layerNames[i - 1] for i in net.getUnconnectedOutLayers()]
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
                    o_c += 1
                    
        indices = cv2.dnn.NMSBoxes(bbox, conf, 0.5, 0.3)
        if o_c > 10:
            obj_flag = 1
        for i in indices:
            i = i
            box = bbox[i]
            x, y, w, h = box[0], box[1], box[2], box[3]
            res=(classNames[classids[i]])
        
    #return classNames[classids[i]]
        if res in ["cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe"]:
            print(res)
            result = res
            res=""
        else:
            result = "NONE"
    return result
    
     
def buffering():
    while(1):
        GPIO.output(stat_led,True)
        time.sleep(0.2)
        GPIO.output(stat_led,False)
        time.sleep(0.2)   
if __name__=="__main__":
    main()
