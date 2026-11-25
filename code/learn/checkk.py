import os
from ultralytics import YOLO
import cv2 

# Load the YOLO model
model = YOLO("D:\\nexus\\learn\\best.pt")  # load a custom model

# Detection threshold
threshold = 0.5

cap = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret,frame=cap.read()

    # Perform detection
    results = model(frame)[0]

    for result in results.boxes.data.tolist():
        x1, y1, x2, y2, score, class_id = result

        if score > threshold:
            # Draw bounding box and label
            cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 4)
            cv2.putText(frame, results.names[int(class_id)].upper(), (int(x1), int(y1 - 10)),
                        cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 255, 0), 3, cv2.LINE_AA)
            res=results.names[int(class_id)]
            print(res)

    # Display the resulting frame
    cv2.imshow('Live Detection', frame)


    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# Close all windows
cv2.destroyAllWindows()
