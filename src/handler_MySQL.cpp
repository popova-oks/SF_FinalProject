#include "../headers/handler_MySQL.h"

bool Handler_MySQL::createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName("oxana");
    db.setHostName("localhost");
    db.setPassword("OxanA");

    // Устанавливаем базу данных "test2" как активную
    db.setDatabaseName("DB_Project");

    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }

    qDebug() << "Database created successfully";
    return true;
}

bool Handler_MySQL::createTables()
{
    // Создание таблицы users
    QSqlQuery query;
    QString createUsersTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
                               "login  VARCHAR(25) UNIQUE NOT NULL, "
                               "password  VARCHAR(25) NOT NULL, "
                               "attach BOOLEAN DEFAULT(FALSE) NOT NULL, "
                               "unblock BOOLEAN DEFAULT(TRUE) NOT NULL"
                               ");";
    if (!query.exec(createUsersTableQuery)) {
        qDebug() << "Unable to create a table1: " << query.lastError().text();
        return false;
    }

    QString createMessagesTableQuery = "CREATE TABLE IF NOT EXISTS messages ("
                                "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
                                "id_reciver INT NOT NULL, "
                                "id_sender INT NOT NULL, "
                                "CONSTRAINT fk_messages_reciver FOREIGN KEY (id_reciver) REFERENCES users(id)"
                               ");";
    if (!query.exec(createMessagesTableQuery)) {
        qDebug() << "Unable to create a table2: " << query.lastError().text();
        return false;
    }
    return true;
}
