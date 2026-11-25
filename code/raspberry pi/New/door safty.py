import time
import board
import busio
from PIL import Image, ImageDraw, ImageFont
import adafruit_ssd1306

# Create I2C interface
i2c = busio.I2C(board.SCL, board.SDA)

# Create the SSD1306 OLED class (128x64 display, I2C address 0x3C is most common)
oled = adafruit_ssd1306.SSD1306_I2C(128, 64, i2c, addr=0x3C)

# Clear display
oled.fill(0)
oled.show()

# Create blank image for drawing
image = Image.new("1", (oled.width, oled.height))
draw = ImageDraw.Draw(image)

# Load default font
font = ImageFont.load_default()

# Draw some text
draw.text((10, 20), "Door Safety", font=font, fill=255)

# Display it
oled.image(image)
oled.show()

time.sleep(5)

# Clear again
oled.fill(0)
oled.show()
