#ifndef BUSINESSDEFINITIONS_H
#define BUSINESSDEFINITIONS_H

#include <QString>

static const QString json_id            = "id";
static const QString json_name          = "name";
static const QString json_surname       = "surname";
static const QString json_email         = "email";
static const QString json_dob           = "dob";
static const QString json_address       = "address";
static const QString json_coordinates   = "coordinates";
static const QString json_street        = "street";
static const QString json_city          = "city";
static const QString json_zip           = "zip";

struct PatientAddress {
  QString coordinates;
  QString street;
  QString city;
  QString zip;
};

struct Patient {
  int id;
  QString name;
  QString surname;
  QString email;
  QString dateOfBirth;
  PatientAddress address;
};

#endif  // BUSINESSDEFINITIONS_H
