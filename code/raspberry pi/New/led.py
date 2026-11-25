import RPi.GPIO as GPIO
import time
led=21
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(led,GPIO.OUT)
while(1):
    GPIO.output(led,True)
    time.sleep(1)
    GPIO.output(led,False)
    time.sleep(1)
