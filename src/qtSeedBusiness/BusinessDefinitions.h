#ifndef BUSINESSDEFINITIONS_H
#define BUSINESSDEFINITIONS_H

#include <QString>

static const int max_patients_message = 20;

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

#endif  // BUSINESSDEFINITIONS_H
