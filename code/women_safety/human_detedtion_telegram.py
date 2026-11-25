import cv2
import mediapipe as mp
import requests
import time

# Telegram details
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"
CHAT_ID = "591291545"

def send_alert(message):
    url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage"
    data = {"chat_id": CHAT_ID, "text": message}
    requests.post(url, data=data)

# Mediapipe setup
mp_pose = mp.solutions.pose
pose = mp_pose.Pose()
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

alert_sent = False     # Track if alert was already sent
cooldown = 10          # Seconds to wait before sending next alert
last_alert_time = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break

    img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = pose.process(img_rgb)

    if results.pose_landmarks:
        mp_draw.draw_landmarks(frame, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

        # Send alert only if cooldown has passed
        current_time = time.time()
        if not alert_sent or (current_time - last_alert_time) > cooldown:
            send_alert("⚠️ Human detected nearby!")
            alert_sent = True
            last_alert_time = current_time

    else:
        alert_sent = False  # Reset when no human is detected

    cv2.imshow("Women Safety Alert", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
