import RPi.GPIO as GPIO
import time
import threading
from flask import *
app=Flask(__name__)
LED=21
def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(LED,GPIO.OUT)
    threading.Thread(target=flsk).start()
@app.route('/control',methods=['GET','POST'])
def control():
    cmd=request.form['data']
    print(cmd)
    if cmd =='A':
        GPIO.output(LED,True)
    elif cmd =='B':
        GPIO.output(LED,False)
    return jsonify({'result':'success'})
def flsk():
    app.run(host='0.0.0.0',port=5000)
    if __name__=="__main__":
        main() 
