import RPi.GPIO as GPIO
import time
import requests  # For sending data to server

# ===== Pin Definitions =====
PIR_PIN = 17       # GPIO17
FLAME_PIN = 27     # GPIO27
RELAY_PIN = 22     # GPIO22
BUZZER_PIN = 23    # GPIO23

# Motor driver pins (L293D)
IN1 = 24           # GPIO24
IN2 = 25           # GPIO25
# ENA is tied HIGH in hardware, so not controlled in code

# ===== Server URL =====
#SERVER_URL = "http://your-server-ip:5000/update"  # Change to your server endpoint

# ===== Setup GPIO =====
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(PIR_PIN, GPIO.IN)
GPIO.setup(FLAME_PIN, GPIO.IN)
GPIO.setup(RELAY_PIN, GPIO.OUT)
GPIO.setup(BUZZER_PIN, GPIO.OUT)
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)

# ===== Functions =====
def start_motor():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)
    print("Motor Started")
def stop_motor():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.LOW)
    print("Motor Stopped")

def handle_pir():
    if GPIO.input(PIR_PIN):
        GPIO.output(RELAY_PIN, GPIO.HIGH)
        print("Motion Detected -> Relay ON")
        start_motor()
        s#end_to_server("motion", "detected")
    else:
        GPIO.output(RELAY_PIN, GPIO.LOW)
        print("No Motion -> Relay OFF")
        stop_motor()
        #send_to_server("motion", "none")

def handle_flame():
    if GPIO.input(FLAME_PIN) == 0:  # 0 = Flame detected
        GPIO.output(BUZZER_PIN, GPIO.HIGH)
        print("Flame Detected -> Buzzer ON")
        send_to_server("flame", "detected")
    else:
        GPIO.output(BUZZER_PIN, GPIO.LOW)
        #send_to_server("flame", "none")

'''def send_to_server(sensor, status):
    try:
        data = {"sensor": sensor, "status": status}
        response = requests.post(SERVER_URL, json=data, timeout=2)
        print("Server Response:", response.text)
    except Exception as e:
        print("Server Error:", e)'''

# ===== Main Loop =====
try:
    while True:
        handle_pir()
        handle_flame()
        time.sleep(0.5)

except KeyboardInterrupt:
    print("Exiting...")
    GPIO.cleanup()
