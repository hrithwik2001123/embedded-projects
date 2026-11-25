import RPi.GPIO as GPIO
import time

FLAME_PIN = 27   # Change GPIO pin if needed

GPIO.setmode(GPIO.BCM)
GPIO.setup(FLAME_PIN, GPIO.IN)

try:
    while True:
        if GPIO.input(FLAME_PIN) == 0:   # Most flame sensors output LOW when flame is detected
            print("? Flame Detected!")
        else:
            print("No Flame")
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()
