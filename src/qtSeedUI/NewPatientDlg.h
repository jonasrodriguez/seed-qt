#include <QObject>
#include <QQuickWindow>
#include <memory>
#include "IBusiness.h"

class NewPatientDlg : public QObject {
  Q_OBJECT
 public:
  NewPatientDlg(QObject *parent, std::shared_ptr<IBusiness> &business_logic);

 public slots:
  void saveNewPatient(QString name, QString surname, QString dob, QString email, QString coordinates, QString street, QString city, QString zipCode);

 private:
  std::shared_ptr<IBusiness> business_logic_;
};
