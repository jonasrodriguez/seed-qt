#include <QObject>
#include <QQuickWindow>
#include <memory>
#include "IBusiness.h"

class NewPatientDlg : public QObject {
  Q_OBJECT
//  Q_PROPERTY(QString patName READ getPatientName NOTIFY patientChanged)

 public:
  NewPatientDlg(QObject *parent, std::shared_ptr<IBusiness> &business_logic);

  QString getPatientName() const { return patient_.name; }
//  QString getPatientSurname() const { return patient_.surname; }
//  QString getPatientDob() const { return patient_.dateOfBirth; }
//  QString getPatientEmail() const { return patient_.email; }
//  QString getPatientCoord() const { return patient_.address.coordinates; }
//  QString getPatientStreet() const { return patient_.address.street; }
//  QString getPatientCity() const { return patient_.address.city; }
//  QString getPatientZip() const { return patient_.address.zip; }

 public slots:
  void saveNewPatient(QString name, QString surname, QString dob, QString email, QString coordinates, QString street, QString city, QString zipCode);

 private:
  std::shared_ptr<IBusiness> business_logic_;
  Patient patient_;
};
