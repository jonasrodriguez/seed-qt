#include "PatientList.h"
#include <QDebug>

QHash<int, QByteArray> PatientList::roleNames() const {
  QHash<int, QByteArray> roles;

  roles[idRole] = json_id.toUtf8();
  roles[nameRole] = json_name.toUtf8();
  roles[surnameRole] = json_surname.toUtf8();
  roles[emailRole] = json_email.toUtf8();
  roles[dobRole] = json_dob.toUtf8();

  return roles;
}

PatientList::PatientList(QObject *parent,
                         std::shared_ptr<IBusiness> &business_logic)
    : QAbstractListModel(parent),
      patient_count_(0),
      business_logic_(business_logic) {
  QObject::connect(business_logic_.get(),
                   SIGNAL(SendPatientList(QVector<Patient>)), this,
                   SLOT(InsertPatients(QVector<Patient>)));
}

int PatientList::rowCount(const QModelIndex & /* parent */) const {
  return patient_list_.size();
}

QVariant PatientList::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (index.row() >= patient_list_.size() || index.row() < 0) return QVariant();

  switch (role) {
    case PatientRoles::idRole:
      return patient_list_.at(index.row()).id;
      break;
    case PatientRoles::nameRole:
      return patient_list_.at(index.row()).name;
      break;
    case PatientRoles::surnameRole:
      return patient_list_.at(index.row()).surname;
      break;
    case PatientRoles::emailRole:
      return patient_list_.at(index.row()).email;
      break;
    case PatientRoles::dobRole: {
      QString dob(patient_list_.at(index.row()).dateOfBirth);
      return dob.left(4) + "/" + dob.mid(4, 2) + "/" + dob.mid(6, 2);
    } break;
    default:
      return QVariant();
      break;
  }

  return QVariant();
}

void PatientList::InsertPatients(QVector<Patient> patients) {
  // Clear list before inserting new patients
  if (!patient_list_.empty()) {
    beginRemoveRows(QModelIndex(), 0, patient_list_.size() - 1);
    patient_list_.clear();
    endRemoveRows();
  }

  beginInsertRows(QModelIndex(), patient_list_.size(),
                  patient_list_.size() + patients.size() - 1);
  for (auto i : patients) {
    patient_list_.push_back(i);
  }
  endInsertRows();
}

void PatientList::deletePatient(int patientId) {
  business_logic_->DeletePatient(patientId);
}

void PatientList::refreshPatientList() { business_logic_->GetPatientList(); }
