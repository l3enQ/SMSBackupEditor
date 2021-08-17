#include "backupxmlparser.h"
#include <QDomDocument>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>

BackupXMLParser::BackupXMLParser(const QString &filePath)
{
    _filePath = filePath;
}

bool BackupXMLParser::Parse()
{
    QString errorStr;
    int errorLine;
    int errorColumn;

    //load the file
    QFile xmlFile(_filePath);
    if (!xmlFile.exists() || !xmlFile.open(QFile::ReadOnly)) {
        qDebug() << "Check your *.xml file";
        return false;
    }


//    domDocument = QDomDocument(_filePath);

    if (!domDocument.setContent(&xmlFile, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(nullptr, "DOM",
                                 QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    qDebug() << root.tagName();// << root.attributes() << root.childNodes();
    qDebug() << root.attribute("count") << root.childNodes().size() << root.attributes().size();

    QStringList attributes = {
        "protocol",
        "address",
        "date",
        "type",
        "subject",
        "toa",
        "sc_toa",
        "service_center",
        "read",
        "status",
        "locked",
        "date_sent",
        "sub_id",
        "readable_date",
        "contact_name",
        "body"
    };

    QLocale us(QLocale::English);

    QList<QMap<QString, QString>> smses;
    QMultiMap<QString, QMap<QString, QString>> smsesMap;
    for (int var = 0; var < root.childNodes().size(); ++var) {
        QMap<QString, QString> attribVals;
        QDomElement nodeElement = root.childNodes().at(var).toElement();
        foreach (auto attrib, attributes) {
            attribVals.insert(attrib, nodeElement.attribute(attrib));
        }

        smses.append(attribVals);
        smsesMap.insertMulti(attribVals.value("address"), attribVals);

//        qDebug() << nodeElement.attribute("readable_date")
//                 << us.toString(QDateTime::fromMSecsSinceEpoch(nodeElement.attribute("date").toLongLong()), "MMM d, yyyy h:mm:ss A")
//                 << nodeElement.attribute("date_sent").toLongLong();
    }


    qDebug() << smses.size() << smsesMap.size() << smsesMap.uniqueKeys().size()
             << smsesMap.values(smsesMap.keys().at(110).size();
    qDebug() << smsesMap.uniqueKeys().at(110) << smsesMap.values(smsesMap.uniqueKeys().at(110));

//    clear();


//    QDomElement child = root.firstChildElement();
//    while (!child.isNull()) {
//        parseFolderElement(child);
//        child = child.nextSiblingElement(folderElement());
//    }
    write(smses);
    return true;
}

void BackupXMLParser::write(QList<QMap<QString, QString> > smses)
{
    QDomDocument doc = QDomDocument("smses2");
    QDomElement rootElement = doc.createElement("smses");

    foreach (auto sms, smses) {
        QDomElement element = doc.createElement("sms");
        foreach (auto key, sms.keys()) {
            element.setAttribute(key, sms.value(key));
        }
        rootElement.appendChild(element);
    }

    doc.appendChild(rootElement);

    QFile file("D:/xmlPath.xml");
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
