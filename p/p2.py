from flask import Flask, request, render_template_string, Response
import threading
import cv2
from ultralytics import YOLO

app = Flask(__name__)

# ================= CONFIG =================
MODEL_PATH = r"D:\nexus\p\runs\detect\train\weights\best.pt"
CAMERA_SOURCE = 0

# ================= GLOBAL =================
output_frame = None

# ✅ separate states (IMPORTANT FIX)
disease_state = "disease_off"
soil_state = "soil_off"

sensor = {
    "temp": 0,
    "hum": 0,
    "soil": 0
}

# ================= CAMERA =================
camera = cv2.VideoCapture(CAMERA_SOURCE)

# ================= YOLO LOOP =================
def yolo_loop():
    global output_frame, disease_state

    print("Loading YOLO...")
    model = YOLO(MODEL_PATH)

    threshold = 0.5
    detect_count = 0

    print("YOLO running...")

    while True:
        success, frame = camera.read()
        if not success:
            continue

        results = model(frame)[0]

        disease_detected = False

        if results.boxes is not None:
            for result in results.boxes.data.tolist():
                x1, y1, x2, y2, score, class_id = result

                if score > threshold:
                    disease_detected = True

                    label = results.names[int(class_id)]

                    # Draw box
                    cv2.rectangle(frame,
                                  (int(x1), int(y1)),
                                  (int(x2), int(y2)),
                                  (0, 255, 0), 2)

                    cv2.putText(frame,
                                f"{label} {score:.2f}",
                                (int(x1), int(y1-10)),
                                cv2.FONT_HERSHEY_SIMPLEX,
                                0.7,
                                (0, 255, 0),
                                2)

        # ===== STABILITY =====
        if disease_detected:
            detect_count += 1
        else:
            detect_count = 0

        if detect_count >= 3:
            disease_state = "disease_on"
        else:
            disease_state = "disease_off"

        output_frame = frame


# ================= VIDEO =================
def generate_frames():
    global output_frame

    while True:
        if output_frame is None:
            continue

        _, buffer = cv2.imencode('.jpg', output_frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


# ================= WEB =================
@app.route('/')
def home():
    return render_template_string("""
    <html>
    <body style="text-align:center; background:black; color:white;">

    <h1>ESP32 CONTROL</h1>

    <button onclick="send('forward')">Forward</button><br><br>
    <button onclick="send('left')">Left</button>
    <button onclick="send('stop')">Stop</button>
    <button onclick="send('right')">Right</button><br><br>
    <button onclick="send('backward')">Backward</button>

    <h2>SENSOR</h2>
    <p>Temp: <span id="t">--</span></p>
    <p>Hum: <span id="h">--</span></p>
    <p>Soil: <span id="s">--</span></p>

    <h3>Camera</h3>
    <img src="/video" width="500">

    <script>
    function send(cmd){
        fetch('/set/' + cmd);
    }

    setInterval(()=>{
        fetch('/data')
        .then(r=>r.json())
        .then(d=>{
            document.getElementById('t').innerText = d.temp;
            document.getElementById('h').innerText = d.hum;
            document.getElementById('s').innerText = d.soil;
        });
    },2000);
    </script>

    </body>
    </html>
    """)

# ================= MANUAL CONTROL =================
manual_cmd = "stop"

@app.route('/set/<cmd>')
def set_cmd(cmd):
    global manual_cmd
    manual_cmd = cmd
    print("👉 MANUAL:", cmd)
    return "OK"

# ================= FINAL COMMAND =================
@app.route('/get_command')
def get_command():
    global disease_state, soil_state, manual_cmd

    # Priority: manual > disease > soil
    if manual_cmd != "stop":
        cmd = manual_cmd
    elif disease_state == "disease_on":
        cmd = "disease_on"
    elif soil_state == "soil_on":
        cmd = "soil_on"
    else:
        cmd = "stop"

    print("📤 SEND:", cmd)
    return cmd


# ================= SENSOR =================
@app.route('/update', methods=['POST'])
def update():
    global sensor, soil_state

    data = request.get_json(force=True)

    sensor["temp"] = data["temp"]
    sensor["hum"] = data["hum"]
    sensor["soil"] = data["soil"]

    print("📥 SENSOR:", sensor)

    if sensor["soil"] >= 4000:
        soil_state = "soil_on"
    else:
        soil_state = "soil_off"

    return "OK"


@app.route('/data')
def data():
    return sensor


# ================= START =================
threading.Thread(target=yolo_loop, daemon=True).start()

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)