import cv2
import mediapipe as mp
import requests
import time

BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"
CHAT_ID = "591291545"

def send_alert(message):
    url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage"
    data = {"chat_id": CHAT_ID, "text": message}
    requests.post(url, data=data)

mp_pose = mp.solutions.pose
pose = mp_pose.Pose()
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

alert_sent = False
cooldown = 10
last_alert_time = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break

    img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = pose.process(img_rgb)

    if results.pose_landmarks:
        mp_draw.draw_landmarks(frame, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

        # Example: measure distance between shoulders
        left_shoulder = results.pose_landmarks.landmark[mp_pose.PoseLandmark.LEFT_SHOULDER]
        right_shoulder = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_SHOULDER]

        # Calculate approximate shoulder width in pixels
        h, w, c = frame.shape
        shoulder_dist = abs(left_shoulder.x - right_shoulder.x) * w

        current_time = time.time()
        # Trigger alert if too close
        if shoulder_dist > 200:  # you can adjust this threshold
            if not alert_sent or (current_time - last_alert_time) > cooldown:
                send_alert("⚠️ Suspicious person approaching!")
                alert_sent = True
                last_alert_time = current_time
        else:
            alert_sent = False

    else:
        alert_sent = False

    cv2.imshow("Women Safety System", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
