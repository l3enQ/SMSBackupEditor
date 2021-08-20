#ifndef BACKUPXMLPARSER_H
#define BACKUPXMLPARSER_H

#include <QThread>
#include <QMultiMap>

typedef QMultiMap<QString, QMap<QString, QString>> smsMap;

class BackupXMLParser : public QObject
{
    Q_OBJECT

public:
    BackupXMLParser(QObject *parent = nullptr);
    ~BackupXMLParser();

public slots:
    bool ParseFile(QString filePath);
    void ExportToFile(smsMap smsesData, QString filePath);

signals:
    dataReady(smsMap smses);

private:
    void write(QList<QMap<QString, QString>> smses, QString filePath);

    QThread _thread;
    const QStringList attributes = {
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
};
Q_DECLARE_METATYPE(smsMap);

#endif // BACKUPXMLPARSER_H
