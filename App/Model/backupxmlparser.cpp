#include "backupxmlparser.h"
#include <QDomDocument>
#include <QtDebug>
#include <QFile>

BackupXMLParser::BackupXMLParser(QObject *parent):
    QObject(parent)
{
    _thread.start();
    moveToThread(&_thread);
}

BackupXMLParser::~BackupXMLParser()
{
    _thread.quit();
    _thread.wait();
}

bool BackupXMLParser::ParseFile(QString filePath)
{
    QFile xmlFile(filePath);
    if (!xmlFile.exists() || !xmlFile.open(QFile::ReadOnly)) {
        qDebug() << "Check your *.xml file";
        return false;
    }

    QDomDocument domDocument;

    int errorLine;
    int errorColumn;
    QString errorStr;

    if (!domDocument.setContent(&xmlFile, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qDebug() << QString("Parse error at line %1, column %2:\n%3")
                    .arg(errorLine)
                    .arg(errorColumn)
                    .arg(errorStr);
        return false;
    }

    QDomElement root = domDocument.documentElement();

    smsMap smsesMap;
    for (int var = 0; var < root.childNodes().size(); ++var) {
        QMap<QString, QString> attribVals;
        QDomElement nodeElement = root.childNodes().at(var).toElement();
        foreach (auto attrib, attributes) {
            attribVals.insert(attrib, nodeElement.attribute(attrib));
        }
        attribVals.insert("select", "1");

        smsesMap.insertMulti(attribVals.value("address"), attribVals);
    }

    emit dataReady(smsesMap);

    return true;
}

void BackupXMLParser::ExportToFile(smsMap smsesData, QString filePath)
{
    write(smsesData.values(), filePath);
}

void BackupXMLParser::write(QList<QMap<QString, QString>> smses, QString filePath)
{
    QDomDocument doc;
    QDomElement rootElement = doc.createElement("smses");

    foreach (auto sms, smses) {
        QDomElement element = doc.createElement("sms");
        foreach (auto key, sms.keys()) {
            element.setAttribute(key, sms.value(key));
        }
        rootElement.appendChild(element);
    }

    doc.appendChild(rootElement);

    QFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        qDebug()<< "Can not open Xml file. Check yor file.";
        return ;
    }

    QTextStream outXml(&file);
    outXml.setCodec("UTF-8");
    outXml.setAutoDetectUnicode(true);
    outXml << QString::fromUtf8(doc.toString().toUtf8());
    file.close();
}
