import config
import telebot
from telebot import types
from telebot.apihelper import ApiTelegramException
import sql

bot = telebot.TeleBot(config.TOKEN)

ALERT_IS_EXPECT = False
ALERT_IS_SAVED = False
ALERT_MESSAGE = telebot.types.Message

@bot.message_handler(commands=['start'])
def start(message):
        add_into_db(message)
        hi_message(message)
        clear_alert()
        checkerSub(message)

@bot.message_handler(content_types=['text'])
def check_text(message):
        global ALERT_MESSAGE
        global ALERT_IS_EXPECT
        global ALERT_IS_SAVED
        isAdmin = is_admin(message.from_user.id)

        if ALERT_IS_EXPECT and not ALERT_IS_SAVED and isAdmin: #сохранить сообщение для рассылки
                ALERT_MESSAGE = message
                ALERT_IS_SAVED = True
                alertAgreement(message)
        elif message.text == config.ALERT and isAdmin: #ждем сообщение для рассылки
                ALERT_IS_EXPECT = True
                bot.send_message(message.chat.id, config.SEND_ALERT_MESSAGE, reply_markup=types.ReplyKeyboardRemove())
        elif message.text == config.ALERT_AGREE and ALERT_IS_SAVED and isAdmin: #согласие рассылки
                makeAlert()
                clear_alert()
                originMenu(True, message)
        elif message.text == config.ALERT_DISAGREE and ALERT_IS_SAVED and isAdmin: #отклонение рассылки
                clear_alert()
                originMenu(True, message)
        elif message.text == config.SUB_ALREADY or message.text == config.UPDATE_INFO: #обновление статуса подписки
                checkerSub(message)
@bot.message_handler(content_types=['photo'])
def check_photo(message):
        global ALERT_MESSAGE
        global ALERT_IS_EXPECT
        global ALERT_IS_SAVED

        if ALERT_IS_EXPECT and not ALERT_IS_SAVED and is_admin(message.from_user.id):
                ALERT_IS_SAVED = True
                ALERT_MESSAGE = message
                alertAgreement(message)

def add_into_db(message):
        sql.add(message.chat.id)

def checkerSub(message):
        userID = message.from_user.id

        isFullSub = True

        markup = types.InlineKeyboardMarkup()

        text = config.SUB_MESSAGE

        for channel in config.CHANNELS:
                if not isSubscribed(channel[1], userID):
                        isFullSub = False
                        break

        if not isFullSub:
                text = config.NOT_SUB_MESSAGE
                for channel in config.CHANNELS:
                        markup.add(types.InlineKeyboardButton(channel[0], url=channel[2]))

        bot.send_message(message.chat.id, text, reply_markup=markup)
        originMenu(isFullSub, message)
def isSubscribed(chatID, userID):
        try:
                member = bot.get_chat_member(chat_id=chatID, user_id=userID)
                if (member.status == 'left'):
                        return False
                return True
        except ApiTelegramException as e:
                if e.result_json['description'] == 'Bad Request: user not found':
                        return False

def hi_message(message):
        bot.send_photo(message.chat.id, config.HI_PHOTO, caption=config.HI_TEXT)
def iAmSub(buttonMarkup):
        return addButton(config.SUB_ALREADY, buttonMarkup)
def updInfo(buttonMarkup):
        return addButton(config.UPDATE_INFO, buttonMarkup)

def addButton(text, buttonMarkup):
        button = types.KeyboardButton(text)
        buttonMarkup.add(button)
        return buttonMarkup


def addAdminTools(buttonMarkup):
        return addButton(config.ALERT, buttonMarkup)

def is_admin(userID):
        for cur in config.ADMINS:
            if cur == userID:
                return True
        return False
def alertAgreement(message):
        buttonMarkup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        buttonMarkup = addButton(config.ALERT_AGREE, buttonMarkup)
        buttonMarkup = addButton(config.ALERT_DISAGREE, buttonMarkup)
        bot.send_message(message.chat.id, config.ALERT_IS_RIGHT, reply_markup=buttonMarkup)

def makeAlert():
        global ALERT_TEXT
        usersID = sql.getUserID()

        for user in usersID:
                try:
                        if ALERT_MESSAGE.content_type == 'photo':
                            bot.send_photo(user, ALERT_MESSAGE.photo[0].file_id, caption=ALERT_MESSAGE.caption)
                        else:
                            bot.send_message(user, ALERT_MESSAGE.text, reply_markup=types.ReplyKeyboardRemove())
                except ApiTelegramException as e:
                        nothingDO = ""


        ALERT_TEXT = ""

def originMenu(isGood, message):
        buttonMarkup = types.ReplyKeyboardMarkup(resize_keyboard=True)

        if isGood:
                buttonMarkup = updInfo(buttonMarkup)
        else:
                buttonMarkup = iAmSub(buttonMarkup)

        if is_admin(message.from_user.id):
                buttonMarkup = addAdminTools(buttonMarkup)

        bot.send_message(message.chat.id, config.CHOOSE_METHOD, reply_markup=buttonMarkup)

def clear_alert():
        global ALERT_MESSAGE
        global ALERT_IS_SAVED
        global ALERT_IS_EXPECT
        ALERT_MESSAGE = telebot.types.Message
        ALERT_IS_EXPECT = False
        ALERT_IS_SAVED = False

bot.polling(none_stop=True)