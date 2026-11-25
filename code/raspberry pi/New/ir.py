import RPi.GPIO as GPIO
import time
ir=22
led=21
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(ir,GPIO.IN)
GPIO.setup(led,GPIO.OUT)
while(1):
    if GPIO.input(ir)==0:
        GPIO.output(led,True)
    else:
        GPIO.output(led,False)
