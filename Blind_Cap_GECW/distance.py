import RPi.GPIO as GPIO
import time

GPIO_TRIGGER = 17                  
GPIO_ECHO = 18

    


def main():

    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)

    # GPIO pin setup
    GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
    GPIO.setup(GPIO_ECHO, GPIO.IN)
    while True:
        GPIO.output(GPIO_TRIGGER, False)
        time.sleep(0.0001)
        GPIO.output(GPIO_TRIGGER, True)
        time.sleep(0.0001)
        GPIO.output(GPIO_TRIGGER, False)

        start_time = time.time()
        stop_time = time.time()

        while GPIO.input(GPIO_ECHO) == 0:
            start_time = time.time()

        while GPIO.input(GPIO_ECHO) == 1:
            stop_time = time.time()

        time_elapsed = stop_time - start_time
        distance = (time_elapsed * 34300) / 2
        print(distance)
 

if __name__ == "__main__":
    main()
