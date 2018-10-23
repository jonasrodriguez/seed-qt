#pragma once
#include <QSqlDatabase>
#include "IDb.h"

class DbManager : public IDb {
 public:
  DbManager();
  ~DbManager() = default;

  void StartUp() override;
  bool AddUser(QString user, QString pass) override;
  bool CheckUser(QString user, QString pass) override;
  bool GetCommConfiguration(QString &ip, int &port) override;
  bool SetCommConfiguration(QString ip, int port) override;

 private:
  void CreateUsersTable();
  void CreateConfTable();
  bool ExistUser(QString user);
  QString EncryptPass(QString pass);

 private:
  QSqlDatabase data_base_;
};
