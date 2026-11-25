from flask import Flask, request
import threading
from telegram import Update
from telegram.ext import Application, CommandHandler, ContextTypes

# ================== Global Variables ==================
humidity = None
temperature = None

# ================== Flask App ==================
flask_app = Flask(__name__)

@flask_app.route('/test', methods=['POST'])
def receive_data():   # <-- renamed to avoid pytest conflict
    global humidity, temperature
    val = request.get_data().decode()
    res = val.split(',')
    if len(res) >= 2:
        humidity = res[0]
        temperature = res[1]
        print(f"Received → Humidity: {humidity}, Temperature: {temperature}")
    return "ok"

def run_flask():
    flask_app.run(port=5000, debug=False, host='0.0.0.0')

# ================== Telegram Bot ==================
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"
ALLOWED_CHAT_IDS = [591291545]  # your Telegram ID

# /start command
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    if update.effective_chat.id in ALLOWED_CHAT_IDS:
        await update.message.reply_text("Hello! 👋 Send /reading to get latest sensor data.")
    else:
        await update.message.reply_text("⛔ Access Denied")

# /status command
async def status(update: Update, context: ContextTypes.DEFAULT_TYPE):
    if update.effective_chat.id in ALLOWED_CHAT_IDS:
        if humidity is not None and temperature is not None:
            await update.message.reply_text(f"🌡 Temperature: {temperature}°C\n💧 Humidity: {humidity}%")
        else:
            await update.message.reply_text("⚠ No data received from ESP32 yet.")
    else:
        await update.message.reply_text("⛔ Access Denied")

def main():
    # Start Flask in background thread
    flask_thread = threading.Thread(target=run_flask, daemon=True)
    flask_thread.start()

    # Start Telegram Bot
    app = Application.builder().token(BOT_TOKEN).build()
    app.add_handler(CommandHandler("start", start))
    app.add_handler(CommandHandler("reading"
                                   "", status))

    print("Bot + Flask server running... ✅")
    app.run_polling()

if __name__ == "__main__":
    main()
