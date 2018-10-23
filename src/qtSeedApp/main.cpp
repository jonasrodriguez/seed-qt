#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <memory>
#include "BusinessLogic.h"
#include "Dashboard.h"
#include "IBusiness.h"
#include "PatientList.h"
#include "NewPatientDlg.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  std::shared_ptr<IBusiness> business_logic(new BusinessLogic);
  business_logic->StartUp();

  Dashboard dashboard(nullptr, business_logic);
  engine.rootContext()->setContextProperty("dashboardLogic", &dashboard);

  PatientList patientList(nullptr, business_logic);
  engine.rootContext()->setContextProperty("patientList", &patientList);

  NewPatientDlg newPatientDlg(nullptr, business_logic);
  engine.rootContext()->setContextProperty("newPatientDlg", &newPatientDlg);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty()) return -1;

  QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() { business_logic->ShutDown(); });

  return app.exec();
}
