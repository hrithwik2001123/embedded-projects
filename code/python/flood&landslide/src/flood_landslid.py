import pymysql
import json
from flask import Flask, request

con = pymysql.connect(
    host='localhost',
    user='root',
    passwd='root',
    db='flood_landslide',
    port=3306,
    charset='utf8'
)
cmd = con.cursor()

app = Flask(__name__)

@app.route('/test', methods=['POST'])
def test():
    data = request.get_json(force=True)

    soil = data["soil"]
    Tem = data["temperature"]
    Humid = data["humidity"]
    Rain = data["rain"]
    Motion = data["motion"]
    Water_level = data["water_level"]
    Emergency = data["emergency"]

    rain_status = "dry" if Rain == 1 else "rainfall"
    motion_status = "motion detected" if Motion == 1 else "no motion"
    water_status = "high water level" if Water_level == 1 else "normal water level"
    emergency_status = "emergency" if Emergency == 1 else "normal"

    print(f"soil: {soil}, Humidity: {Humid}, Temperature: {Tem}, "
          f"Rain: {rain_status}, Motion: {motion_status}, "
          f"Water Level: {water_status}, Emergency: {emergency_status}")

    try:
        with con.cursor() as cursor:
            cursor.execute(
                "INSERT INTO floods_landslid VALUES (NULL, %s, %s, %s, %s, %s, %s, %s)",
                (soil, Tem, Humid, rain_status, motion_status, water_status, emergency_status)
            )
            con.commit()
    except Exception as e:
        print("❌ DB error:", e)
        return "db error", 500

    print("✅ success")
    return "ok"

app.run(port=5000, debug=True, host='0.0.0.0')
