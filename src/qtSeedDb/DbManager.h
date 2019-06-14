#pragma once
#include "IDb.h"
#include <QSqlDatabase>

class DbManager : public IDb {
public:
  DbManager();
  ~DbManager() = default;

  bool StartUp() override;
  bool GetCommConfiguration(seed::CommsConfiguration &conf) override;
  bool UpdateCommConfiguration(const seed::CommsConfiguration &conf) override;

private:
  bool CreateConfigTable();

private:
  QSqlDatabase data_base_;
};
