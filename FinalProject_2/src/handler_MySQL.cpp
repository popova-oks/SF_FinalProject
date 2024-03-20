#include "../headers/handler_MySQL.h"

Handler_MySQL::Handler_MySQL() {
    if (!createConnection()) {
        qDebug() << "Failed to create database";
    }
    if (!createTables()) {
        qDebug() << "Failed to create tables";
    }
}

bool Handler_MySQL::createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName("oxana");
    db.setHostName("localhost");
    db.setPassword("OxanA");

    // Устанавливаем базу данных "test2" как активную
    db.setDatabaseName("SFProject");

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
                               "password TEXT NOT NULL, "
                               "attach BOOLEAN DEFAULT(FALSE) NOT NULL, "
                               "block BOOLEAN DEFAULT(FALSE) NOT NULL"
                               ");";
    if (!query.exec(createUsersTableQuery)) {
        qDebug() << "Unable to create a table1: " << query.lastError().text();
        return false;
    }

    QString createMessagesTableQuery = "CREATE TABLE IF NOT EXISTS messages ("
                                "id INTEGER PRIMARY KEY AUTO_INCREMENT, "
                                "id_receiver INT, "
                                "id_sender INT NOT NULL, "
                                "message TEXT, "
                                "CONSTRAINT fk_messages_receiver FOREIGN KEY (id_sender) REFERENCES users(id)"
                               ");";
    if (!query.exec(createMessagesTableQuery)) {
        qDebug() << "Unable to create a table2: " << query.lastError().text();
        return false;
    }
    return true;
}

QStringList Handler_MySQL::createListUsers()
{
    QSqlQuery query;
    QString queryStr = "SELECT login FROM users WHERE attach=:attach AND block=:block";
    query.prepare(queryStr);
    query.bindValue(":attach", true);
    query.bindValue(":block", false);

    QStringList users;
    if (query.exec()) {
        while (query.next()) {
           users.append(query.value(0).toString());
        }
     }
    return users;
}

QStringList Handler_MySQL::createListBlockUsers()
{
    QSqlQuery query;
    QString queryStr = "SELECT login FROM users WHERE block=:block";
    query.prepare(queryStr);
    query.bindValue(":block", true);

    QStringList users;
    if (query.exec()) {
        while (query.next()) {
           users.append(query.value(0).toString());
        }
     }
    return users;
}

QStringList Handler_MySQL::createListUnblockUsers()
{
    QSqlQuery query;
    QString queryStr = "SELECT login FROM users WHERE block=:block";
    query.prepare(queryStr);
    query.bindValue(":block", false);

    QStringList users;
    if (query.exec()) {
        while (query.next()) {
           users.append(query.value(0).toString());
        }
     }
    return users;
}

QStringList Handler_MySQL::createListPrivateMessages(const QString &receiver)
{
    QSqlQuery query;
    QString queryStr = "SELECT u.login, m.message "
                       "FROM users u JOIN messages m ON u.id = m.id_sender "
                       "WHERE m.id_receiver = (SELECT id FROM users WHERE login=:receiver)";
    query.prepare(queryStr);
    query.bindValue(":receiver", receiver);

    QStringList messages;
    if (query.exec()) {
        while (query.next()) {
           QString message = query.value(0).toString() + ": " + query.value(1).toString();
           messages.append(message);
        }
    }
    return messages;
}

QStringList Handler_MySQL::createListMessagesForAll()
{
    QSqlQuery query;
    QString queryStr = "SELECT u.login, m.message "
                       "FROM users u JOIN messages m ON u.id = m.id_sender "
                       "WHERE m.id_receiver = 0 ;";
    query.prepare(queryStr);

    QStringList messages;
    if (query.exec()) {
        while (query.next()) {
           QString message = query.value(0).toString() + ": " + query.value(1).toString();
           messages.append(message);
        }
    }
    return messages;
}

bool Handler_MySQL::add_user(const QString &login, const QString &password)
{
    if (is_block(login)) {
        qDebug() << "The user was blocked";
        return false;
    }
    if (is_user(login)) {
        qDebug() << "The user already exist";
        return false;
    }
    QSqlQuery insertQuery;
    QString insertQueryStr = "INSERT INTO users (login, password, attach, block) "
                             "VALUES (:login, :password, :attach, :block);";

    insertQuery.prepare(insertQueryStr);
    insertQuery.bindValue(":login", login);
    insertQuery.bindValue(":password", password);
    insertQuery.bindValue(":attach", true);
    insertQuery.bindValue(":block", false);

    if (!insertQuery.exec()) {
        qDebug() << "Unable to make insert operation:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool Handler_MySQL::attach_user(const QString &login, const QString &password)
{
    if (is_block(login)) {
        qDebug() << "The user was blocked";
        return false;
    }
    if (!check_user(login, password)) {
        qDebug() << "The user don't find";
        return false;
    }

    QSqlQuery insertQuery;
    QString insertQueryStr = "UPDATE users SET attach=:attach WHERE login=:login";
    insertQuery.prepare(insertQueryStr);
    insertQuery.bindValue(":attach", true);
    insertQuery.bindValue(":login", login);

    if (!insertQuery.exec()) {
        qDebug() << "Unable to update user attach status:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool Handler_MySQL::detach_user(const QString &login)
{
    if (is_block(login)) {
        qDebug() << "The user was blocked";
        return false;
    }
    QSqlQuery insertQuery;
    QString insertQueryStr = "UPDATE users SET attach=:attach WHERE login=:login";
    insertQuery.prepare(insertQueryStr);
    insertQuery.bindValue(":attach", false);
    insertQuery.bindValue(":login", login);

    if (!insertQuery.exec()) {
        qDebug() << "Unable to update user attach status:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool Handler_MySQL::add_message(const QString &sender, const QString &receiver, const QString &message)
{
     if (is_block(receiver)) {
         qDebug() << "The receiver was blocked";
         return false;
     }
     if (is_block(sender)) {
         qDebug() << "The sender was blocked";
         return false;
     }
     if (receiver != "all") {
         if (!is_user(receiver)) {
             qDebug() << "The receiver was not found";
             return false;
         }
     }
     if (!is_user(sender)) {
         qDebug() << "The sender was not found";
         return false;
     }
     QSqlQuery insertQuery;
     if (receiver == "all") {
         QString insertQueryStr = "INSERT INTO messages (id_sender, id_receiver, message) "
                                  "VALUES ((SELECT id FROM users WHERE login=:sender), "
                                  "0, :message);";
         insertQuery.prepare(insertQueryStr);
         insertQuery.bindValue(":sender", sender);
         insertQuery.bindValue(":message", message);
     } else {
         QString insertQueryStr = "INSERT INTO messages (id_sender, id_receiver, message) "
                                  "VALUES ((SELECT id FROM users WHERE login=:sender), "
                                  "(SELECT id FROM users WHERE login=:receiver), "
                                  ":message);";

         insertQuery.prepare(insertQueryStr);
         insertQuery.bindValue(":sender", sender);
         insertQuery.bindValue(":receiver", receiver);
         insertQuery.bindValue(":message", message);
     }
     if (!insertQuery.exec()) {
         qDebug() << "Unable to perform insert operation:" << insertQuery.lastError().text();
         return false;
     }
     return true;
}

bool Handler_MySQL::block_user(const QString &adm_login, const QString &adm_password, const QString &user)
{
    if (user == "admin") {
        qDebug() << "The admin can't block or unblock";
        return false;
    }
    if (!check_user(adm_login, adm_password)) {
        qDebug() << "The admin don't find";
        return false;
    }
    QSqlQuery insertQuery;
    QString insertQueryStr = "UPDATE users SET block=:block WHERE login=:login";
    insertQuery.prepare(insertQueryStr);
    insertQuery.bindValue(":block", true);
    insertQuery.bindValue(":login", user);

    if (!insertQuery.exec()) {
        qDebug() << "Unable to update user block status:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool Handler_MySQL::unblock_user(const QString &adm_login, const QString &adm_password, const QString &user)
{
    if (user == "admin") {
        qDebug() << "The admin can't block or unblock";
        return false;
    }
    if (!check_user(adm_login, adm_password)) {
        qDebug() << "The admin don't find";
        return false;
    }
    QSqlQuery insertQuery;
    QString insertQueryStr = "UPDATE users SET block=:block WHERE login=:login";
    insertQuery.prepare(insertQueryStr);
    insertQuery.bindValue(":block", false);
    insertQuery.bindValue(":login", user);

    if (!insertQuery.exec()) {
        qDebug() << "Unable to update user block status:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool Handler_MySQL::check_user(const QString &login, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT attach FROM users WHERE login = :login AND password = :password;");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        return true;
    } else {
        qDebug() << "User not found";
        return false;
    }
}

bool Handler_MySQL::is_block(const QString &login)
{
    QSqlQuery query;
    query.prepare("SELECT block FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        bool isBlocked = query.value(0).toBool();
        return isBlocked;
    } else {
        qDebug() << "User not found";
        return false;
    }
}

bool Handler_MySQL::is_user(const QString &login)
{
    QSqlQuery query;
    query.prepare("SELECT attach FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        bool isAttached = query.value(0).toBool();
        return isAttached;
    } else {
        qDebug() << "User not found";
        return false;
    }
}


