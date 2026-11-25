from flask import Flask, request
import threading
import telebot

# ===== Telegram Bot Setup =====
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"   # replace with your token
bot = telebot.TeleBot(BOT_TOKEN)

# ===== Flask Setup =====
app = Flask(__name__)

# store latest data
latest_data = {"humidity": None, "temperature": None}


@app.route('/test', methods=['POST'])
def test():
    """ESP32 will POST humidity,temperature here"""
    try:
        val = request.get_data().decode()
        res = val.split(',')
        humidity = res[0]
        temperature = res[1]

        # save latest values
        latest_data["humidity"] = humidity
        latest_data["temperature"] = temperature

        print(f"📡 Received -> Humidity: {humidity}, Temp: {temperature}")
        return "OK"
    except Exception as e:
        print("Error:", e)
        return "ERROR", 400


# ===== Telegram Bot Handlers =====
@bot.message_handler(commands=['start'])
def send_welcome(message):
    bot.reply_to(message, "🌡 Welcome! You can ask:\n/humidity\n/temperature\n/status")


@bot.message_handler(commands=['humidity'])
def send_humidity(message):
    h = latest_data["humidity"]
    if h:
        bot.reply_to(message, f"💧 Humidity: {h}%")
    else:
        bot.reply_to(message, "⚠️ No data yet from ESP32.")


@bot.message_handler(commands=['temperature'])
def send_temperature(message):
    t = latest_data["temperature"]
    if t:
        bot.reply_to(message, f"🌡 Temperature: {t}°C")
    else:
        bot.reply_to(message, "⚠️ No data yet from ESP32.")


@bot.message_handler(commands=['status'])
def send_status(message):
    h = latest_data["humidity"]
    t = latest_data["temperature"]
    if h and t:
        bot.reply_to(message, f"✅ Latest Reading:\nHumidity: {h}%\nTemperature: {t}°C")
    else:
        bot.reply_to(message, "⚠️ No sensor data received yet.")


# ===== Run Flask + Bot together =====
def run_flask():
    app.run(host="0.0.0.0", port=5000, debug=False)


if __name__ == "__main__":
    # run flask in background
    threading.Thread(target=run_flask, daemon=True).start()
    print("🚀 Flask running on port 5000")
    print("🤖 Telegram Bot running...")
    bot.polling()
