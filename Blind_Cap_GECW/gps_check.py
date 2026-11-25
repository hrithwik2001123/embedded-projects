import serial
import time

ser = serial.Serial("/dev/serial0", baudrate=115200, timeout=1)

location = ""

try:
    while True:
        print("GPS fetching....")
        received_data = ser.readline().decode('utf-8',errors='ignore')
        if received_data.startswith('$GPGGA'):
            data_elements = received_data.split(',')
            latitude = data_elements[2]
            longitude = data_elements[4]

                # Convert latitude and longitude to decimal degrees
            latitude_degrees = float(latitude[:2]) + float(latitude[2:]) / 60.0
            longitude_degrees = float(longitude[:3]) + float(longitude[3:]) / 60.0
            print(f"Latitude: {latitude_degrees}, Longitude: {longitude_degrees}")
            location = f"http://maps.google.com/maps?q={latitude_degrees},{longitude_degrees}"
        else:
            print(".....")
            #latitude_degrees = 10.8240
            #longitude_degrees = 76.6426
            #print(f"Latitude: {latitude_degrees}, Longitude: {longitude_degrees}")
            #location = f"http://maps.google.com/maps?q={latitude_degrees},{longitude_degrees}"
        time.sleep(0.2)
except Exception as e:
    print(e)
