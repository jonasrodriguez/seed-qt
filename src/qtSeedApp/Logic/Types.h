#pragma once

#include <QObject>
#include <QString>

namespace seed {
struct CommsConfiguration {
  QString ip;
  int port;
};

struct Patient {
  QString id;
  QString name;
  QString surname;
  QString email;
  QString dateOfBirth;
  QString coordinates;
  QString street;
  QString city;
  QString zip;

  Patient() {}
  Patient(const Patient &p)
      : id(p.id), name(p.name), surname(p.surname), email(p.email),
        dateOfBirth(p.dateOfBirth), coordinates(p.coordinates),
        street(p.street), city(p.city), zip(p.zip) {}
  ~Patient() {}
};

} // namespace seed

Q_DECLARE_METATYPE(seed::Patient)
