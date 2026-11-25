import RPi.GPIO as GPIO
from flask import Flask
import telebot

# === Telegram Bot Token ===
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"
bot = telebot.TeleBot(BOT_TOKEN)

# === Raspberry Pi LED Pin ===
LED_PIN = 18   # GPIO18 (change if needed)

# === Flask App ===
app = Flask(__name__)

# === GPIO Setup ===
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)


# ==================== FLASK ROUTES ====================
@app.route("/led/on")
def led_on():
    GPIO.output(LED_PIN, GPIO.HIGH)
    return "LED is ON"

@app.route("/led/off")
def led_off():
    GPIO.output(LED_PIN, GPIO.LOW)
    return "LED is OFF"


# ==================== TELEGRAM HANDLERS ====================
@bot.message_handler(commands=['start'])
def start(message):
    bot.reply_to(message, "Raspberry Pi LED Bot Ready! Send 'on' or 'off'.")


@bot.message_handler(func=lambda message: True)
def handle_message(message):
    text = message.text.lower()

    if "on" in text:
        response = led_on()
        bot.reply_to(message, f"? {response}")
    elif "off" in text:
        response = led_off()
        bot.reply_to(message, f"? {response}")
    else:
        bot.reply_to(message, "Send 'on' or 'off' to control LED.")


# ==================== MAIN ====================
if __name__ == "__main__":
    from threading import Thread

    # Run Flask in background thread
    flask_thread = Thread(target=lambda: app.run(host="0.0.0.0", port=5000))
    flask_thread.start()

    # Run Telegram bot
    print("Bot is running...")
    bot.polling()
