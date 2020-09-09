#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include "Logic/Types.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QVector>

static const QString json_id = "id";
static const QString json_name = "name";
static const QString json_surname = "surname";
static const QString json_email = "email";
static const QString json_dob = "dob";
static const QString json_address = "address";
static const QString json_coordinates = "coordinates";
static const QString json_street = "street";
static const QString json_city = "city";
static const QString json_zip = "zip";

static const QString json_content = "content";
static const QString json_totalElements = "totalElements";
static const QString json_first = "first";
static const QString json_last = "last";
static const QString json_number = "number";
static const QString json_numberElements = "numberOfElements";
static const QString json_zie = "size";
static const QString json_totalPages = "totalPages";

using namespace seed;

class MessageHelper {
public:
  static void ReadPatientContent(const QJsonDocument &doc,
                                 QVector<Patient> &patients, int &page_number);
  static int NumberOfPatients(const QJsonDocument &doc);
  static QByteArray CreateJsonPatient(const Patient &patient);

private:
  MessageHelper() {}
  static Patient ReadJsonPatient(const QJsonObject &obj);
};

#endif // MESSAGEHELPER_H
