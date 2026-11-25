import RPi.GPIO as GPIO
import time

# Pin definitions
servo = 22
button = 16  # First button
button1 = 20  # Second button (was incorrectly reassigned)

# Flags for button press detection
flag = 0
flag1 = 0

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(servo, GPIO.OUT)
GPIO.setup(button, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Added pull-up resistor
GPIO.setup(button1, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Added pull-up resistor

# PWM initialization (corrected capitalization)
pwm = GPIO.PWM(servo, 50)  # 50 Hz frequency
pwm.start(0)  # Start with 0 duty cycle

try:
    while True:
        # Read button values
        btn_val = GPIO.input(button)
        btn_val1 = GPIO.input(button1)  # Corrected variable name
        
        # Button 1 logic (for 0 degree position)
        if btn_val == 0:  # Button pressed (active low with pull-up)
            flag = 1
        if btn_val == 1 and flag == 1:  # Button released after press
            pwm.ChangeDutyCycle(2.5)  # Corrected capitalization
            time.sleep(0.3)  # Allow time for servo movement
            pwm.ChangeDutyCycle(0)  # Stop sending signal to prevent jitter
            flag = 0
            
        # Button 2 logic (for 180 degree position)
        if btn_val1 == 0:  # Button pressed (active low with pull-up)
            flag1 = 1
        if btn_val1 == 1 and flag1 == 1:  # Button released after press
            pwm.ChangeDutyCycle(12.5)  # Corrected capitalization
            time.sleep(0.3)  # Allow time for servo movement
            pwm.ChangeDutyCycle(0)  # Stop sending signal to prevent jitter
            flag1 = 0
            
        # Small delay to debounce buttons
        time.sleep(0.05)
        
except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()
