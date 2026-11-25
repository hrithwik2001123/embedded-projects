import pymysql
con=pymysql.connect(host='localhost',user='root',passwd='root',db='sensordata',port=3306,charset='utf8')
cmd=con.cursor()
from flask import Flask, request

app = Flask(__name__)

@app.route('/test', methods=['POST'])
def test():
    val = request.get_data().decode()
    res=val.split(',')
    humidity=res[0]
    temperature=res[1]
    gas=res[2]
    gas_value = int(gas)  # convert to integer

    if gas_value == 1:
        gas = "high"
        print("high")
    else:
        gas = "low"
        print("low")

    print(humidity,temperature,gas)
    cmd.execute("insert into dh11_gas values(null,'" + humidity + "','" + temperature + "','" + gas + "')")
    con.commit()
    print("success")
    return "ok"

app.run(port=5000, debug=True, host='0.0.0.0')
