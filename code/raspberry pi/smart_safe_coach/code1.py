import RPi.GPIO as GPIO
import time

# ===== Pin Definitions =====
PIR_PIN = 17
FLAME_PIN = 27
RELAY_PIN = 22
BUZZER_PIN = 23
IN1 = 24
IN2 = 25
# ENA tied HIGH in hardware

# ===== Setup =====
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(PIR_PIN, GPIO.IN)
GPIO.setup(FLAME_PIN, GPIO.IN)
GPIO.setup(RELAY_PIN, GPIO.OUT)
GPIO.setup(BUZZER_PIN, GPIO.OUT)
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)

print("System Started... Press CTRL+C to exit.")

try:
    while True:
        # ===== PIR ? Relay Control =====
        if GPIO.input(PIR_PIN):   # Motion detected
            GPIO.output(RELAY_PIN, GPIO.LOW)
            print("Motion Detected -> Relay ON")
        else:                     # No motion
            GPIO.output(RELAY_PIN, GPIO.HIGH)
            print("No Motion -> Relay OFF")

        # ===== Flame Sensor =====
        if GPIO.input(FLAME_PIN) == 0:   # Flame detected (active LOW)
            GPIO.output(BUZZER_PIN, GPIO.HIGH)
            time.sleep(1)
            GPIO.output(BUZZER_PIN, GPIO.LOW)
            GPIO.output(IN1, GPIO.LOW)   # Stop motor
            GPIO.output(IN2, GPIO.LOW)
            print("? Flame Detected -> Buzzer ON, Motor OFF")
            #time.sleep(5000)
        else:
            GPIO.output(BUZZER_PIN, GPIO.LOW)
            GPIO.output(IN1, GPIO.HIGH)  # Motor forward
            GPIO.output(IN2, GPIO.LOW)
            print("No Flame -> Motor Running")

        time.sleep(0.5)

except KeyboardInterrupt:
    print("Exiting...")
    GPIO.cleanup()
