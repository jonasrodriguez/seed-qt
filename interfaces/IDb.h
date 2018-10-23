#ifndef IDB_H
#define IDB_H

#include <QString>

class IDb {
 public:
  IDb() = default;
  virtual ~IDb() = default;

  virtual void StartUp() = 0;

  virtual bool AddUser(QString user, QString pass) = 0;
  virtual bool CheckUser(QString user, QString pass) = 0;

  virtual bool GetCommConfiguration(QString &ip, int &port) = 0;
  virtual bool SetCommConfiguration(QString ip, int port) = 0;
};

#endif  // IDB_H
