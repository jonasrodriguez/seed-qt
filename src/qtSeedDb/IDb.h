#ifndef IDB_H
#define IDB_H

#include "Logic/Types.h"
#include <QString>

class IDb {
public:
  IDb() = default;
  virtual ~IDb() = default;

  virtual bool StartUp() = 0;

  virtual bool GetCommConfiguration(seed::CommsConfiguration &conf) = 0;
  virtual bool
  UpdateCommConfiguration(const seed::CommsConfiguration &conf) = 0;
};

#endif // IDB_H
