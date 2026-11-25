import RPi.GPIO as GPIO
import time
trigger=17
echo=27
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(trigger,GPIO.OUT)
GPIO.setup(echo,GPIO.IN)

def measure_distance():
    GPIO.output(trigger,True)
    time.sleep(0.00001)
    GPIO.output(trigger,False)
    start_time=time.time()
    stop_time=time.time()
    while GPIO.input(echo)==0:
        stop_time=time.time()
    while GPIO.input(echo)==1:
        stop_time=time.time()
        time_elapsed=stop_time-start_time
        distance=(time_elapsed*34300)/2
    return(distance)

try:
    while True:
        dist=measure_distance()
        print(f"distance: {dist:.2f}cm")
        time.sleep(0.5)
except Exception as e:
    print("error:",e)
    GPIO.cleanup()

