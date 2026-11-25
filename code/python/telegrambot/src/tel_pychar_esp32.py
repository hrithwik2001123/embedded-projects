import requests
import time
import telebot

# === Telegram Bot Token ===
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"
bot = telebot.TeleBot(BOT_TOKEN)
# === ESP32 IP ===
ESP32_IP = "http://192.168.137.130"  # <-- include http://

@bot.message_handler(commands=['start'])
def start(message):
    bot.reply_to(message, "ESP32 Bot Ready! Send 'on' or 'off'.")

@bot.message_handler(func=lambda message: True)
def handle_message(message):
    text = message.text.lower()

    if "on" in text:
        r = requests.get(f"{ESP32_IP}/led/on")
        bot.reply_to(message, f"✅ {r.text}")
    elif "off" in text:
        r = requests.get(f"{ESP32_IP}/led/off")
        bot.reply_to(message, f"❌ {r.text}")
    else:
        bot.reply_to(message, "Send 'on' or 'off' to control LED.")

print("Bot is running...")
bot.polling()
