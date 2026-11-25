import pymysql
from flask import Flask, request

# MySQL connection
con = pymysql.connect(
    host='localhost',
    user='root',
    passwd='root',
    db='land',
    port=3306,
    charset='utf8'
)

app = Flask(__name__)

@app.route('/test', methods=['POST'])
def test():
    data = request.get_json(force=True)

    # Arduino sends raw values → we decode them here
    soil_val = int(data["soil"])          # 0 or 1
    vibration_val = int(data["vibration"]) # 0 or 1

    soil = "Wet" if soil_val == 0 else "Dry"
    vibration = "Detected" if vibration_val == 0 else "Not Detected"

    # Direct values (keep as string for VARCHAR)
    temperature = str(data["temperature"])
    humidity = str(data["humidity"])
    accX = str(data["accX"])
    accY = str(data["accY"])
    accZ = str(data["accZ"])
    gyroX = str(data["gyroX"])
    gyroY = str(data["gyroY"])
    gyroZ = str(data["gyroZ"])

    # Debug print
    print(f"📥 Received: Soil={soil}, Temp={temperature}, Humidity={humidity}, "
          f"Vibration={vibration}, acc=({accX},{accY},{accZ}), "
          f"gyro=({gyroX},{gyroY},{gyroZ})")

    # Save into DB
    try:
        with con.cursor() as cursor:
            cursor.execute(
                """INSERT INTO land_1 
                (soil, temperature, humidity, vibration, accX, accY, accZ, gyroX, gyroY, gyroZ)
                VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)""",
                (soil, temperature, humidity, vibration, accX, accY, accZ, gyroX, gyroY, gyroZ)
            )
            con.commit()
    except Exception as e:
        print("❌ DB error:", e)
        return "db error", 500

    print("✅ Data saved to DB")
    return "ok"

if __name__ == "__main__":
    app.run(port=5000, debug=True, host='0.0.0.0')
