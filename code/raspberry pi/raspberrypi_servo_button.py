import RPi.GPIO as GPIO
import time
servo=22
button=16
button=20
flag=0
flag1=0
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(servo,GPIO.OUT)
GPIO.setup(button,GPIO.IN)
GPIO.setup(button1,GPIO.IN)
pwm=GPIO.pwm(SERVO,50)
PWM.START(0)
try:
    while True:
        btn_val=GPIO.input(button)
        bttn_val=GPIO.input(button1)
        if btn_val==0:
            flag=1
        if btn_val==1 and flag==1:
            pwm.changeDutyCycle(2.5)
            flag=0
        if bttn_val==0:
            flag1=1
        if bttn_val==1 and flag1==1:
            pwm.changeDutyCycle(12.5)
            flag1=0
except keyboardInterrupt:
        pwm.stop()
        GPIO.cleanup()
            
