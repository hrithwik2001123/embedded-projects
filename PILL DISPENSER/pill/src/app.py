import time
from flask import *
import pymysql
import datetime
import threading
import requests
import telepot
TELEGRAM_API_TOKEN="8063823944:AAGtipyAYfuCD40rjQZIFd9c7zbUpvDvlC8"
CHAT_ID ="1559099472"
res = 'invalid'
knownEncodings = []
nameList = []
presentList = []
dat = ""
dat1 = ""
sub=""
cls=""
result1=""
flag1=0
flag2=0
flag3=0
flag=0
med_name1=[]
med_name2=[]
med_name3=[]
med_name4=[]
con=pymysql.connect(host="localhost",user="root",passwd="root",port=3307,db="medicine_trolly",charset='utf8')
cmd=con.cursor()
app=Flask(__name__)
replay=""
def send_telegram_message(message):
    url = f"https://api.telegram.org/bot{TELEGRAM_API_TOKEN}/sendMessage"
    payload = {
        "chat_id": CHAT_ID,
        "text": message
    }
    response = requests.post(url, data=payload)
    return response.json()
@app.route('/test',methods=['GET','POST'])
def test():
    global dat
    global med_name1
    global med_name3
    global med_name3
    val=request.get_data().decode()
    print(val)
    v=""
    data="ok"
    if med_name1:
        #print(med_name1)
        if(len(med_name1)>0):
            v = med_name1[0]
            print(v)
            del med_name1[0]
            #print(f"Removed element at index 0: {v}")
            data=v
    if med_name2:
        #print(med_name1)
        if(len(med_name2)>0):
            v = med_name2[0]
            print(v)
            del med_name2[0]
            #print(f"Removed element at index 0: {v}")
            data=v
    if med_name3:
        #print(med_name1)
        if(len(med_name3)>0):
            v = med_name3[0]
            print(v)
            del med_name3[0]
            #print(f"Removed element at index 0: {v}")
            data=v
    return data


@app.route('/check',methods=['GET','POST'])
def check():
    global dat1
    val1 = request.get_data().decode()
    message = "patient didn't take the medicine"
    send_telegram_message(message)
    return "sucess"

@app.route('/login',methods=['POST'])
def login():
        uname=request.form['username']
        password=request.form['password']
        cmd.execute("select * from login where username='"+uname+"' and password='"+password+"'")
        s = cmd.fetchone()
        print(s)
        if s:
            print(s[0])
            print(s[3])
            return jsonify({'status': 'ok','lid':s[0],'type':s[3]})
        else:
            return jsonify({'status': 'error'})

@app.route('/medicine_register',methods=['POST'])
def register():
    try:
        name=request.form['name']
        bid=request.form['bid']
        medname = request.form['medname']
        quantity=request.form['quantity']
        times=request.form['times']
        cmd.execute("insert into patient_details values(null,'"+name+"','"+bid+"','"+medname+"','"+quantity+"','"+times+"')")
        con.commit()
        return jsonify({'status':'ok'})
    except Exception as e:
        print(str(e))
        return jsonify({'status': 'error'})

@app.route('/view_medicine',methods=['GET'])
def view_faculty():
    cmd.execute("select * from patient_details order by id desc")
    row_headers = [x[0] for x in cmd.description]
    s = cmd.fetchall()
    print(s)
    json_data = []
    for result in s:
        json_data.append(dict(zip(row_headers, result)))
    con.commit()
    return jsonify(json_data)

def control():
    global flag1,flag2,flag3
    global replay
    global med_name4
    while True:
        cmd.execute("select * from patient_details")
        res=cmd.fetchall()
        tm=datetime.datetime.now().strftime("%H:%M:%S")
        #morning
        if(str(tm)=="12:15:03"):
            time.sleep(1)
            for i in range(0, len(res)):
                if str(res[i][5]) == "A":
                    med_name1.append(res[i][3])
                    med_name1.append(res[i][2])

                if str(res[i][5]) == "B":
                    med_name1.append(res[i][3])
                    med_name1.append(res[i][2])

                if str(res[i][5]) == "C":
                    med_name1.append(res[i][3])
                    med_name1.append(res[i][2])

            print(med_name1)
        # Afternoon
        if(str(tm)=="12:19:03"):
            time.sleep(1)
            for i in range(0, len(res)):
                if str(res[i][5]) == "A":
                    med_name2.append(res[i][3])
                    med_name2.append(res[i][2])

                if str(res[i][5]) == "E":
                    med_name2.append(res[i][3])
                    med_name2.append(res[i][2])

            print(med_name2)
        #Night
        if(str(tm)=="12:20:03"):
            time.sleep(1)
            for i in range(0, len(res)):
                if str(res[i][5]) == "A":
                    med_name3.append(res[i][3])
                    med_name3.append(res[i][2])

                if str(res[i][5]) == "B":
                    med_name3.append(res[i][3])
                    med_name3.append(res[i][2])

                if str(res[i][5]) == "D":
                    med_name3.append(res[i][3])
                    med_name3.append(res[i][2])

            print(med_name3)


def main():
    threading.Thread(target=control).start()
    threading.Thread(target=flsk).start()
def flsk():
    app.run(host="0.0.0.0", port=5000)

if __name__=="__main__":
    main()