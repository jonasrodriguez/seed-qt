#pragma once
#include "IDb.h"
#include <QSqlDatabase>

class DbManager : public IDb {
public:
  DbManager();
  ~DbManager() = default;

  void StartUp() override;
  bool AddUser(QString user, QString pass) override;
  bool CheckUser(QString user, QString pass) override;
  bool GetCommConfiguration(seed::CommsConfiguration &conf) override;
  bool UpdateCommConfiguration(const seed::CommsConfiguration &conf) override;

private:
  void CreateUsersTable();
  void CreateConfTable();
  bool ExistUser(QString user);
  QString EncryptPass(QString pass);

private:
  QSqlDatabase data_base_;
};
