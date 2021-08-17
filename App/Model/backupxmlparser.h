#ifndef BACKUPXMLPARSER_H
#define BACKUPXMLPARSER_H

#include <QObject>
#include <QDomDocument>
#include <QMap>

class BackupXMLParser : public QObject
{
    Q_OBJECT

public:
    BackupXMLParser(const QString &filePath);
    bool Parse();

public slots:
    bool ParseFile(QString filePath);

private:
    QString _filePath;
    QDomDocument domDocument;

    void write(QList<QMap<QString, QString>> smses);
};

#endif // BACKUPXMLPARSER_H
