import cv2
from ultralytics import YOLO

# Load your YOLO model
model = YOLO(r"D:\nexus\p\runs\detect\train\weights\best.pt")
threshold = 0.5

# Open webcam
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Cannot open webcam")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # YOLO prediction
    results = model(frame)[0]

    # Draw bounding boxes
    for result in results.boxes.data.tolist():
        x1, y1, x2, y2, score, class_id = result
        if score > threshold:
            label = results.names[int(class_id)]
            cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
            cv2.putText(frame, f"{label} {score:.2f}", (int(x1), int(y1-10)),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0,255,0), 2)

    cv2.imshow("Leaf Disease Detection", frame)

    # Press 'q' to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
