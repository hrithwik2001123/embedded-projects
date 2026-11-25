import time
import board
import adafruit_dht
import psutil
import RPi.GPIO as GPIO

soil=27
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(soil,GPIO.IN)
for proc in psutil.process_iter():
    if "libgpiod" in proc.name():
        proc.kill()
sensor=adafruit_dht.DHT11(board.D21)

while True:
    try:
        temp=sensor.temperature
        humidity=sensor.humidity
        print("temperature:{}*c humidity:{}%".format(temp,humidity))
        soil_value=GPIO.input(soil)
        if soil_value==0:
            print("soil is wet")
        else:
            print("soil is dry")
    except RuntimeError as error:
        print(error.args[0])
        time.sleep(2.0)
        continue
    except Exception as error:
        sensor=None
        raise error
    time.sleep(1.0)
