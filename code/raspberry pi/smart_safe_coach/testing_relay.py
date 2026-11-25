import RPi.GPIO as GPIO
import time

RELAY_PIN = 22

GPIO.setmode(GPIO.BCM)
GPIO.setup(RELAY_PIN, GPIO.OUT)

try:
    while True:
        GPIO.output(RELAY_PIN, GPIO.HIGH)  # Relay ON
        print("Relay ON")
        time.sleep(2)

        GPIO.output(RELAY_PIN, GPIO.LOW)   # Relay OFF
        print("Relay OFF")
        time.sleep(2)

except KeyboardInterrupt:
    GPIO.cleanup()
