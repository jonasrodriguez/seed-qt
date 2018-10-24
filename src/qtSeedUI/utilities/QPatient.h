#pragma once
#include <QObject>
#include "BusinessDefinitions.h"

class QPatient : public QObject {
  Q_OBJECT

  public:
    QPatient(QObject *parent = nullptr) : QObject(parent) {};
    Patient getPatient() { return patient_; };
    void setPatient(Patient patient) { patient_ = patient; };

  private:
    Patient patient_;
};
