#include <QObject>
#include <memory>
#include "IBusiness.h"

static const QString nav_home           = "home.qml";
static const QString nav_patient_list   = "PatientArea.qml";
static const QString nav_login          = "Login.qml";

enum navMap {
    home,
    patient_list,
    login
};

class Dashboard : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString loginError READ getLoginError NOTIFY loginErrorChanged)
  Q_PROPERTY(QString navigation READ getNavigation NOTIFY navigationChanged)

 public:
  Dashboard(QObject *parent, std::shared_ptr<IBusiness> &business_logic);

  QString getLoginError() const { return login_error_; }
  QString getNavigation() const { return navigation_; }

 signals:
  void loginErrorChanged();
  void navigationChanged();

 public slots:
  void ProcessLoginStatus(bool loginStatus);
  void buttonLogin(QString user, QString pass);

 private:
  void updateNavigation(int nav);

 private:
  std::shared_ptr<IBusiness> business_logic_;
  QString login_error_;
  QString navigation_;
};
