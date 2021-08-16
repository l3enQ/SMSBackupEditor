#include <QApplication>
#include <QQmlApplicationEngine>
#include "Model/backupxmlparser.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);


    BackupXMLParser a("C:\\Users\\l3enQ\\Downloads\\sms-20210506000715.xml");
    qDebug() << a.Parse();


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/View/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
