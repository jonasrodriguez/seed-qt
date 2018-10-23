#include "Dashboard.h"
#include <QDebug>

Dashboard::Dashboard(QObject *parent,
                     std::shared_ptr<IBusiness> &business_logic)
    : QObject(parent), business_logic_(business_logic), login_error_(""), navigation_("")  {
  QObject::connect(business_logic_.get(), &IBusiness::SendLoginStatus, this,
                   &Dashboard::ProcessLoginStatus);
  updateNavigation(navMap::login);
}

void Dashboard::buttonLogin(QString user, QString pass) {
  business_logic_->LoginUser(user, pass);
}

void Dashboard::ProcessLoginStatus(bool loginStatus) {
  if (!loginStatus) {
    login_error_ = QString("User/Password rejected by the server.");

    updateNavigation(navMap::login);
    emit loginErrorChanged();    
  }
  else {
    updateNavigation(navMap::patient_list);
  }
}

void Dashboard::updateNavigation(int nav) {
  switch(nav) {
    case navMap::home:
      navigation_ = nav_home;
  break;
    case navMap::patient_list:
      navigation_ = nav_patient_list;
  break;
    case navMap::login:
    default:
      navigation_ = nav_login;
  break;
  }

  emit navigationChanged();
}
