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
stat_led = 21
data_led = 20
buzzer = 16
light = 17
pump = 27
dht_pin = 4
soil = 6
pir = 13
sensor = Adafruit_DHT.DHT11
command = 0
temperature = 0
soil_status = None
pir_status = None



def main():
    global result
    global res
    global soil_status
    global temperature
    global humidity

    # GPIO setup
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(stat_led, GPIO.OUT)
    GPIO.setup(data_led, GPIO.OUT)
    GPIO.setup(buzzer, GPIO.OUT)
    GPIO.setup(light, GPIO.OUT)
    GPIO.setup(pump, GPIO.OUT)
    GPIO.setup(soil, GPIO.IN)
    GPIO.setup(pir, GPIO.IN)
    GPIO.output(buzzer, False)
    GPIO.output(pump, False)
    GPIO.output(light, False)
    while True:
        pir_reading = GPIO.input(pir)
        print(pir_reading)



if __name__ == "__main__":
    main()
