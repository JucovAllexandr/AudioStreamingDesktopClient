#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <auth.h>
#include <appmanager.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    AppManager app_manager(engine);
    //app_manager.setEngine(&engine);

    engine.rootContext()->setContextProperty("Auth", app_manager.auth());
    engine.rootContext()->setContextProperty("AppManager", &app_manager);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);



    return app.exec();
}
