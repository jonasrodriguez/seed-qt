#ifndef IDB_H
#define IDB_H

#include "Definitions.h"
#include <QString>

class IDb {
public:
  IDb() = default;
  virtual ~IDb() = default;

  virtual void StartUp() = 0;

  virtual bool AddUser(QString user, QString pass) = 0;
  virtual bool CheckUser(QString user, QString pass) = 0;

  virtual bool GetCommConfiguration(seed::CommsConfiguration &conf) = 0;
  virtual bool
  UpdateCommConfiguration(const seed::CommsConfiguration &conf) = 0;
};

#endif // IDB_H
