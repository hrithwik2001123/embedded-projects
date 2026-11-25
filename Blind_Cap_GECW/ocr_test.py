import cv2
import pytesseract
import time
from picamera2 import Picamera2

# Initialize camera
picam = Picamera2()
picam.preview_configuration.main.size = (640, 480)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

# Give camera time to adjust
time.sleep(2)

def extract_all_text_from_image(image_path):
    """Extract all text from an image"""
    image = cv2.imread(image_path)
    if image is None:
        return "No image found"
    
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
    
    text = pytesseract.image_to_string(gray)
    return text

# Capture continuously with delay
photo_count = 1
capture_interval = 5  # seconds between captures
last_capture_time = time.time()

print("📸 Camera is ON - Press 'q' to quit")
print(f"Will capture photo every {capture_interval} seconds")
print("-" * 50)

try:
    while True:
        # Capture frame from camera
        frame = picam.capture_array()
        
        # Display live camera feed
        cv2.imshow('Live Camera - Press q to quit', frame)
        
        # Check if it's time to capture a photo
        current_time = time.time()
        if current_time - last_capture_time >= capture_interval:
            # Save the captured photo
            photo_path = f"photo_{photo_count}.jpg"
            cv2.imwrite(photo_path, frame)
            
            print(f"\n📸 Photo {photo_count} captured and saved: {photo_path}")
            
            # Extract and print all text from the photo
            extracted_text = extract_all_text_from_image(photo_path)
            
            print("=" * 50)
            print(f"📝 TEXT FROM PHOTO {photo_count}:")
            print("=" * 50)
            
            if extracted_text.strip():
                print(extracted_text)
                print("\nWords found:")
                # Print individual words
                words = extracted_text.split()
                for i, word in enumerate(words, 1):
                    print(f"  {i}. {word}")
                print(f"\nTotal words: {len(words)}")
            else:
                print("No text detected in this photo")
            
            print("=" * 50)
            
            photo_count += 1
            last_capture_time = current_time
        
        # Check for quit command
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            print("\n👋 Stopping camera...")
            break
            
except KeyboardInterrupt:
    print("\n\n👋 Interrupted by user")

finally:
    # Cleanup
    cv2.destroyAllWindows()
    print("Camera stopped")
