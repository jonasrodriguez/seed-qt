#include "DbManager.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DbManager::DbManager() { data_base_ = QSqlDatabase::addDatabase("QSQLITE"); }

void DbManager::StartUp() {
  data_base_.setDatabaseName("seedDb.sqlite");
  data_base_.open();
  if (data_base_.tables().isEmpty()) CreateConfTable();
}
void DbManager::CreateUsersTable() {
  QSqlQuery query;
  query.prepare(
      "CREATE TABLE users "
      "(user_id integer primary key, "
      "user varchar(20), "
      "password varchar(50))");
  if (!query.exec())
    qDebug() << "DB Error!! Create Users table: " << query.lastError();

  AddUser("Systelab", "Systelab");
}
void DbManager::CreateConfTable() {
  QSqlQuery query;
  query.prepare(
      "CREATE TABLE commsConf "
      "(id integer primary key, "
      "ip varchar(20), "
      "port integer)");
  if (!query.exec())
    qDebug() << "DB Error!! Create Users table: " << query.lastError();

  SetCommConfiguration("127.0.0.1", 8080);
}
bool DbManager::GetCommConfiguration(QString &ip, int &port) {
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM commsConf");
    if (query.exec()) {
      if (query.next()) {
          success = true;
      }
    } else {
      qDebug() << "DB Error!! GetCommConfiguration: " << query.lastError();
    }
    return success;
}
bool DbManager::SetCommConfiguration(QString ip, int port) {
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO commsConf (ip, port) VALUES (:ip, :port)");
    query.bindValue(":ip", ip);
    query.bindValue(":port", port);

    if (query.exec())
      success = true;
    else
      qDebug() << "DB Error!! Add user: " << query.lastError();

    return success;
}
bool DbManager::AddUser(QString user, QString pass) {
  if (ExistUser(user)) return false;

  bool success = false;

  QSqlQuery query;
  query.prepare(
      "INSERT INTO users (user, password) "
      "VALUES (:user, :pass)");
  query.bindValue(":user", user);
  query.bindValue(":pass", EncryptPass(pass));

  if (query.exec())
    success = true;
  else
    qDebug() << "DB Error!! Add user: " << query.lastError();

  return success;
}
bool DbManager::CheckUser(QString user, QString pass) {
  bool success = false;
  QSqlQuery query;
  query.prepare(
      "SELECT * FROM users WHERE user = (:user) AND password = (:pass)");
  query.bindValue(":user", user);
  query.bindValue(":pass", EncryptPass(pass));
  if (query.exec()) {
    if (query.next()) success = true;
  } else
    qDebug() << "DB Error!! Select User: " << query.lastError();
  return success;
}
QString DbManager::EncryptPass(QString pass) {
  // Need salty salt :D
  return QString(
      QCryptographicHash::hash((pass.toUtf8()), QCryptographicHash::Md5)
          .toHex());
}
bool DbManager::ExistUser(QString user) {
  bool success = false;
  QSqlQuery query;
  query.prepare("SELECT * FROM users WHERE user = (:user)");
  query.bindValue(":user", user);
  if (query.exec()) {
    if (query.next()) success = true;
  } else
    qDebug() << "DB Error!! Select User: " << query.lastError();
  return success;
}
