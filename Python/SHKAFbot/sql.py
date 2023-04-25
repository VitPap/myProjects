import sqlite3

def add(item):
    connect = sqlite3.connect('db.db')
    cursor =    connect.cursor()

    itemDB = []
    itemDB.append(item)
    cursor.execute('INSERT OR IGNORE INTO users VALUES(?)', itemDB)
    connect.commit()
    cursor.close()

def getUserID():
    connect = sqlite3.connect('db.db')
    cursor = connect.cursor()

    query = 'SELECT * FROM users'
    cursor.execute(query)
    data = cursor.fetchall()

    resultStr = []

    for i in data:
        resultStr.append(i)

    result = []

    for i in resultStr:
        result.append(parseStr(str(i)))

    return result

def parseStr(str):
    i = 0
    while i < len(str) and str[i] != ',':
        i+=1
    return (int)(str[1:i])