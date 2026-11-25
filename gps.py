import serial

s = serial.Serial('/dev/ttyS0', 9600)

while True:
    gps = s.readline().decode().strip()
    if gps.startswith('$GPGGA'):
        g = gps.split(',')
        if g[6] == '1':
            lat = float(g[2][:2]) + float(g[2][2:])/60
            lon = float(g[4][:3]) + float(g[4][3:])/60
            if g[3] == 'S': lat = -lat
            if g[5] == 'W': lon = -lon
            print(lat, lon)
