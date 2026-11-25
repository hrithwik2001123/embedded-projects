import serial, pynmea2

gps = serial.Serial("/dev/serial0", baudrate=115200, timeout=1)

while True:
    line = gps.readline().decode('ascii', errors='replace')
    if line.startswith('$GPGGA'):
        msg = pynmea2.parse(line)
        print(f"Latitude: {msg.latitude}, Longitude: {msg.longitude}")
