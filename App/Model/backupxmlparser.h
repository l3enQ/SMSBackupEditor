#ifndef BACKUPXMLPARSER_H
#define BACKUPXMLPARSER_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include <QMultiMap>
#include <QThread>

typedef QMultiMap<QString, QMap<QString, QString>> smsMap;


class BackupXMLParser : public QObject
{
    Q_OBJECT

public:
    BackupXMLParser(const QString &filePath);
    ~BackupXMLParser();
    bool Parse();

public slots:
    bool ParseFile(QString filePath);

signals:
    dataReady(smsMap smses);

private:
    QString _filePath;
    QDomDocument domDocument;
    QThread _thread;

    void write(QList<QMap<QString, QString>> smses);

};
Q_DECLARE_METATYPE(smsMap);

#endif // BACKUPXMLPARSER_H
