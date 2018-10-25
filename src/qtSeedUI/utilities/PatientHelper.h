#ifndef PATIENTHELPER_H
#define PATIENTHELPER_H

#include <QObject>
#include "BusinessDefinitions.h"

class PatientHelper : public QObject {
  Q_OBJECT
  Q_PROPERTY(int id             MEMBER id_ CONSTANT)
  Q_PROPERTY(QString name       MEMBER name_ CONSTANT)
  Q_PROPERTY(QString surname    MEMBER surname_ CONSTANT)
  Q_PROPERTY(QString email      MEMBER email_ CONSTANT)
  Q_PROPERTY(QString dob        MEMBER dob_ CONSTANT)
  Q_PROPERTY(QString coor       MEMBER coor_ CONSTANT)
  Q_PROPERTY(QString street     MEMBER street_ CONSTANT)
  Q_PROPERTY(QString city       MEMBER city_ CONSTANT)
  Q_PROPERTY(QString zip        MEMBER zip_ CONSTANT)

  public:
    PatientHelper(QObject *parent = nullptr) : QObject (parent) {}

    Patient getPatient() {
        Patient p;
        p.id            = id_;
        p.name          = name_;
        p.surname       = surname_;
        p.email         = email_;
        p.dateOfBirth   = dob_;
        p.address.coordinates = coor_;
        p.address.street      = street_;
        p.address.city        = city_;
        p.address.zip         = zip_;
        return p;
    }

    void setPatient(Patient patient) {
        id_ = patient.id;
        name_ = patient.name;
        surname_ = patient.surname;
        email_ = patient.email;
        dob_ = patient.dateOfBirth;
        coor_ = patient.address.coordinates;
        street_ = patient.address.street;
        city_ = patient.address.city;
        zip_ = patient.address.zip;
    }

    void setDummyValues() {
        id_ = 333;
        name_ = "Nombre";
        surname_ = "Ieee";
        email_ = "WootWoot";
    }

  private:
    int id_;
    QString name_;
    QString surname_;
    QString email_;
    QString dob_;
    QString coor_;
    QString street_;
    QString zip_;
    QString city_;
};

#endif // PATIENTHELPER_H
