import cv2
import time
import requests
from ultralytics import YOLO

# =====================================================
# CONFIGURATION
# =====================================================

# YOLO model path
MODEL_PATH = r"E:\nuxs\drone\runs\detect\train\weights\best.pt"

# Detection confidence
CONFIDENCE_THRESHOLD = 0.5

# ESP32-CAM stream URL
ESP32_STREAM_URL = "http://192.168.1.105:81/stream"   # 🔁 CHANGE IP

# ESP8266 relay pulse URL
ESP8266_IP = "192.168.199.114"                          # 🔁 CHANGE IP
RELAY_PULSE_URL = f"http://{ESP8266_IP}/relay/pulse"

# Relay control timing
RELAY_ON_TIME = 2        # seconds (handled by ESP, kept for logic)
COOLDOWN_TIME = 15       # seconds between triggers (IMPORTANT)

# =====================================================
# LOAD YOLO MODEL
# =====================================================
print("🔄 Loading YOLO model...")
model = YOLO(MODEL_PATH)
print("✅ Model loaded")

# =====================================================
# OPEN ESP32-CAM STREAM
# =====================================================
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

if not cap.isOpened():
    print("❌ Cannot connect to ESP32-CAM stream")
    exit()

print("📡 ESP32-CAM stream connected")

# =====================================================
# VARIABLES
# =====================================================
last_trigger_time = 0
relay_ready = True

print("🚀 System running (Press Q to quit)")

# =====================================================
# MAIN LOOP
# =====================================================
while True:
    ret, frame = cap.read()
    if not ret:
        print("❌ Frame read failed")
        break

    # Resize for speed
    frame = cv2.resize(frame, (640, 480))

    # Run YOLO
    results = model(frame, conf=CONFIDENCE_THRESHOLD, verbose=False)

    disease_detected = False

    # =================================================
    # DRAW DETECTIONS
    # =================================================
    for r in results:
        if r.boxes is not None and len(r.boxes) > 0:
            disease_detected = True

            for box in r.boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                class_id = int(box.cls[0])
                score = float(box.conf[0])
                label = model.names[class_id]

                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv2.putText(
                    frame,
                    f"{label} {score:.2f}",
                    (x1, y1 - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.7,
                    (0, 255, 0),
                    2
                )

    # =================================================
    # RELAY TRIGGER LOGIC (AUTO 2s)
    # =================================================
    current_time = time.time()

    if disease_detected and relay_ready:
        try:
            print("⚠️ Leaf disease detected → Relay pulse sent")
            requests.get(RELAY_PULSE_URL, timeout=1)

            relay_ready = False
            last_trigger_time = current_time

        except Exception as e:
            print("❌ ESP8266 not reachable:", e)

    # Cooldown reset
    if not relay_ready and (current_time - last_trigger_time >= COOLDOWN_TIME):
        relay_ready = True
        print("⏳ Cooldown finished → System ready again")

    # =================================================
    # DISPLAY
    # =================================================
    cv2.imshow("Leaf Disease Detection | ESP32 + ESP8266", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# =====================================================
# CLEANUP
# =====================================================
cap.release()
cv2.destroyAllWindows()
print("👋 Program stopped")
