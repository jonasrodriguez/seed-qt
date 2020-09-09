#include "DbManager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DbManager::DbManager() { data_base_ = QSqlDatabase::addDatabase("QSQLITE"); }

bool DbManager::StartUp() {
  data_base_.setDatabaseName("seedDb.sqlite");
  data_base_.open();
  if (data_base_.tables().isEmpty()) {
    return CreateConfigTable();
  }
  return true;
}

bool DbManager::CreateConfigTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE Configuration "
                "(id integer primary key, "
                "ip varchar(20), "
                "port integer)");
  if (!query.exec()) {
    qDebug() << "DB Error!! Create Users table: " << query.lastError();
    return false;
  }

  query.exec(
      "INSERT INTO Configuration (ip, port) VALUES (\"127.0.0.1\", 8080)");
  return true;
}

bool DbManager::GetCommConfiguration(seed::CommsConfiguration &conf) {
  bool success = false;

  QSqlQuery query;
  query.prepare("SELECT * FROM Configuration");
  if (query.exec()) {
    while (query.next()) {
      conf.ip = query.value(1).toString();
      conf.port = query.value(2).toInt();
      success = true;
    }
  } else {
    qDebug() << "DB Error!! GetCommConfiguration: " << query.lastError();
  }
  return success;
}

bool DbManager::UpdateCommConfiguration(const seed::CommsConfiguration &conf) {
  bool success = false;

  QSqlQuery query;
  query.prepare("UPDATE Configuration SET ip = :ip, port = :port WHERE id = 1");
  query.bindValue(":ip", conf.ip);
  query.bindValue(":port", conf.port);

  if (query.exec())
    success = true;
  else
    qDebug() << "DB Error!! Update Configuration table: " << query.lastError();

  return success;
}
