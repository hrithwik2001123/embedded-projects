from telegram import Update
from telegram.ext import Application, CommandHandler, MessageHandler, filters, ContextTypes

# --- Replace with your Bot Token from BotFather ---
BOT_TOKEN = "6595861968:AAF2prVyX8nJTwgY15XVR07GDoGiU68FARk"

# Optional: Only allow specific chat IDs
ALLOWED_CHAT_IDS = [591291545]  # Your chat ID(s)


# --- Command: /start ---
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    if update.effective_chat.id in ALLOWED_CHAT_IDS:
        await update.message.reply_text("Hello! 👋 I am your test bot, ready to chat.")
    else:
        await update.message.reply_text("⛔ Access Denied")


# --- Reply to any message ---
async def echo(update: Update, context: ContextTypes.DEFAULT_TYPE):
    if update.effective_chat.id in ALLOWED_CHAT_IDS:
        user_text = update.message.text
        await update.message.reply_text(f"You said: {user_text}")
    else:
        await update.message.reply_text("⛔ Access Denied")


# --- Main Function ---
def main():
    app = Application.builder().token(BOT_TOKEN).build()

    # Commands
    app.add_handler(CommandHandler("start", start))

    # Normal Messages
    app.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, echo))

    print("Bot is running... ✅")
    app.run_polling()


if __name__ == "__main__":
    main()
