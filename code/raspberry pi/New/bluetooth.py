import serial
import time

bt = serial.Serial("/dev/serial1",baudrate=9600,timeout=1)

try:
    while True:
        bt.write(b"Hello from raspberry pi!\n")
        print("sent: Hello from raspberry pi ")
        data =bt.readline().decode().strip()
        if data:
            print("Received :",data)
            reply="you said : "+ data +"\n"
            bt.write(reply.encode())
            print("sent back:",reply.strip())
            time.sleep(2)
except keyboardInterrupt:
    print("program stopped")
    bt.close()
