#include <QObject>
#include <memory>
#include "IBusiness.h"

static const QString nav_home           = "home.qml";
static const QString nav_patient_list   = "PatientArea.qml";
static const QString nav_login          = "Login.qml";
static const QString nav_conf           = "Configuration.qml";

enum navMap {
    home,
    patient_list,
    login,
    conf
};

class Dashboard : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString loginError READ getLoginError NOTIFY loginErrorChanged)
  Q_PROPERTY(QString navigation READ getNavigation NOTIFY navigationChanged)
  Q_PROPERTY(QString ip     MEMBER ip_    NOTIFY confChanged)
  Q_PROPERTY(QString port   MEMBER port_  NOTIFY confChanged)

 public:
  Dashboard(QObject *parent, std::shared_ptr<IBusiness> &business_logic);

  QString getLoginError() const { return login_error_; }
  QString getNavigation() const { return navigation_; }

 signals:
  void loginErrorChanged();
  void navigationChanged();
  void confChanged();

 public slots:
  void ProcessLoginStatus(bool loginStatus);  

  void buttonLogin(QString user, QString pass);
  void buttonSaveConf(QString ip, QString port);

  void buttonNavHome();
  void buttonNavLogout();
  void buttonNavConfiguration();

 private:
  void UpdateNavigation(int nav);
  void GetConfigurationFromBusiness();

 private:
  std::shared_ptr<IBusiness> business_logic_;
  QString login_error_;
  QString navigation_;
  QString ip_;
  QString port_;
};
