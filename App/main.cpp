#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QtQml>
#include "Model/backupxmlparser.h"
#include "Model/xmlreader.h"
#include <QDebug>
#include <QQuickStyle>
#include "Model/smscontactsmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QFontDatabase::addApplicationFont(":/fontello.ttf");

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    XMLReader *fsm = new XMLReader(&engine);
    engine.rootContext()->setContextProperty("xmlReader", fsm);

    BackupXMLParser *a = new BackupXMLParser("C:\\Users\\benyamin\\Downloads\\sms-20210506000715.xml");
    fsm->connect(fsm, &XMLReader::filepathChanged, a, &BackupXMLParser::ParseFile);

    SMSContactsModel *model = new SMSContactsModel();
    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(model));

    const QUrl url(QStringLiteral("qrc:/View/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
