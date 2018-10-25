#include <QObject>
#include <QQuickWindow>
#include <memory>
#include "IBusiness.h"
#include "PatientHelper.h"

class PatientDialog : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool newPatient MEMBER new_patient_)
  Q_PROPERTY(PatientHelper* patient READ getQPatient NOTIFY patientChanged)

 public:
  PatientDialog(QObject *parent, std::shared_ptr<IBusiness> &business_logic);
  PatientHelper* getQPatient();

 public slots:
  void saveNewPatient(QString name, QString surname, QString dob, QString email, QString coordinates, QString street, QString city, QString zipCode);
  void savePatientInfo(PatientHelper* patient);

 signals:
   void patientChanged();

 private:
  std::shared_ptr<IBusiness> business_logic_;
  std::unique_ptr<PatientHelper> qpatient_;
  bool new_patient_;
};
