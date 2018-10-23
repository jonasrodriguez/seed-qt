#include <QAbstractListModel>
#include <memory>
#include "IBusiness.h"

class PatientList : public QAbstractListModel {
  Q_OBJECT
 public:
  enum PatientRoles {
    idRole = Qt::UserRole + 1,
    nameRole,
    surnameRole,
    emailRole,
    dobRole
  };
  PatientList(QObject *parent, std::shared_ptr<IBusiness> &business_logic);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

 public slots:
  void InsertPatients(QVector<Patient> patients);
  void deletePatient(int patientId);
  void refreshPatientList();

 private:
  int patient_count_;
  QVector<Patient> patient_list_;
  std::shared_ptr<IBusiness> business_logic_;
};
