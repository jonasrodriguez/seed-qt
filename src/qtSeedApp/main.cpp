#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QThread>
#include <memory>

#include "Logic/BusinessLogic.h"
#include "Logic/Types.h"
#include "Views/Dashboard.h"
#include "Views/PatientDialog.h"
#include "Views/PatientList.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  std::shared_ptr<BusinessLogic> business_logic(new BusinessLogic);
  business_logic->StartUp();

  Dashboard dashboard(nullptr, business_logic);
  engine.rootContext()->setContextProperty("dashboardLogic", &dashboard);

  PatientList patientList(nullptr, business_logic);
  engine.rootContext()->setContextProperty("patientList", &patientList);

  PatientDialog patientDialog(nullptr, business_logic);
  engine.rootContext()->setContextProperty("patientDialog", &patientDialog);

  qRegisterMetaType<seed::Patient>();

  QThread businessThread;
  business_logic->moveToThread(&businessThread);
  businessThread.start();

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
    business_logic->ShutDown();
    businessThread.quit();
    businessThread.wait();
  });

  return app.exec();
}
