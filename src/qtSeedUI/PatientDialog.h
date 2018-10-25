#include <QObject>
#include <QQuickWindow>
#include <memory>
#include "IBusiness.h"
#include "PatientHelper.h"

class PatientDialog : public QObject {
  Q_OBJECT
  Q_PROPERTY(PatientHelper* patient READ getQPatient NOTIFY patientChanged)

 public:
  PatientDialog(QObject *parent, std::shared_ptr<IBusiness> &business_logic);
  PatientHelper* getQPatient();

 public slots:
  void savePatientInfo(PatientHelper* patient);
  void clearPatientDialog();
  void GetPatientInfoFromList(Patient patient);

 signals:
   void patientChanged();

 private:
  std::shared_ptr<IBusiness> business_logic_;
  std::unique_ptr<PatientHelper> patient_helper_;
  bool new_patient_;
};
