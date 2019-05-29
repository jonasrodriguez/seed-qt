#pragma once

#include <QString>

namespace seed {
struct CommsConfiguration {
  QString ip;
  int port;
};

struct PatientAddress {
  QString coordinates;
  QString street;
  QString city;
  QString zip;
};

struct Patient {
  QString id;
  QString name;
  QString surname;
  QString email;
  QString dateOfBirth;
  PatientAddress address;
};

} // namespace seed
