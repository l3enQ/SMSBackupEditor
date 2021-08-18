#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QtQml>
#include <QDebug>
#include <QQuickStyle>
#include "Model/backupxmlparser.h"
#include "Model/xmlreader.h"
#include "Model/smscontactsmodel.h"
#include "Model/selectablesmsviewer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Benyamin");
    app.setOrganizationDomain("Benyamin");
    qRegisterMetaType<smsMap>();
    QFontDatabase::addApplicationFont(":/fontello.ttf");
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    BackupXMLParser *a = new BackupXMLParser("");
    XMLReader *fsm = new XMLReader(&engine);
    engine.rootContext()->setContextProperty("xmlReader", fsm);
    SMSContactsModel *model = new SMSContactsModel(&engine);
    engine.rootContext()->setContextProperty("contactModel", QVariant::fromValue(model));
    SelectableSMSViewer *viewerModel = new SelectableSMSViewer(&engine);
    engine.rootContext()->setContextProperty("viewerModel", QVariant::fromValue(viewerModel));

    fsm->connect(fsm, &XMLReader::filepathChanged, model, &SMSContactsModel::clear);
    fsm->connect(fsm, &XMLReader::filepathChanged, a, &BackupXMLParser::ParseFile);

    model->connect(a, &BackupXMLParser::dataReady, model, &SMSContactsModel::onDataReady);
    model->connect(model, &SMSContactsModel::selectionChanged, [=](int row){
        QList<QMap<QString, QString>> data = model->data(model->index(row, 0),
                                                         SMSContactsModel::dataRole)
                .value<QList<QMap<QString, QString>>>();
        viewerModel->onDataReady(data);
    });
    model->connect(viewerModel, &SelectableSMSViewer::dataChanged,
                   [=](const QModelIndex &topLeft, const QModelIndex &bottomRight,
                   const QVector<int> &roles = QVector<int>()){
        if (roles.contains(SelectableSMSViewer::selectRole)) {
            if (topLeft.isValid() && bottomRight.isValid() && topLeft.row() == bottomRight.row()) {
                int select = topLeft.data(SelectableSMSViewer::selectRole).toInt();
                qDebug() << topLeft << select;
                model->selectSMS(topLeft.row(), select);
            }
        }
    });

    const QUrl url(QStringLiteral("qrc:/View/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
