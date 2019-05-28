#include "Dashboard.h"
#include "Logic/BusinessLogic.h"

Dashboard::Dashboard(QObject *parent,
                     std::shared_ptr<BusinessLogic> &business_logic)
    : QObject(parent), business_logic_(business_logic), login_error_(""),
      navigation_("") {

  QObject::connect(business_logic_.get(), &BusinessLogic::SendLoginStatus, this,
                   &Dashboard::ProcessLoginStatus);

  UpdateNavigation(navMap::login);
  GetConfigurationFromBusiness();
}

void Dashboard::buttonLogin(QString user, QString pass) {
  business_logic_->LoginUser(user, pass);
}

void Dashboard::ProcessLoginStatus(bool loginStatus) {
  if (!loginStatus) {
    login_error_ = QString("User/Password rejected by the server.");

    UpdateNavigation(navMap::login);
    emit loginErrorChanged();
  } else {
    UpdateNavigation(navMap::patient_list);
  }
}

void Dashboard::buttonSaveConf(QString ip, QString port) {
  seed::CommsConfiguration conf;
  conf.ip = ip;
  conf.port = port.toInt();

  business_logic_->UpdateConfiguration(conf);
}

void Dashboard::GetConfigurationFromBusiness() {
  seed::CommsConfiguration conf;
  business_logic_->GetConfiguration(conf);
  ip_ = conf.ip;
  port_ = QString::number(conf.port);

  emit confChanged();
}

void Dashboard::UpdateNavigation(int nav) {
  switch (nav) {
  case navMap::home:
    navigation_ = nav_home;
    break;
  case navMap::patient_list:
    navigation_ = nav_patient_list;
    break;
  case navMap::conf:
    GetConfigurationFromBusiness();
    navigation_ = nav_conf;
    break;
  case navMap::login:
  default:
    navigation_ = nav_login;
    break;
  }

  emit navigationChanged();
}

void Dashboard::buttonNavHome() {
  if (business_logic_->IsUserLogger())
    UpdateNavigation(navMap::patient_list);
  else
    UpdateNavigation(navMap::login);
}

void Dashboard::buttonNavLogout() { UpdateNavigation(navMap::login); }

void Dashboard::buttonNavConfiguration() { UpdateNavigation(navMap::conf); }
