#ifndef BACKUPXMLPARSER_H
#define BACKUPXMLPARSER_H

#include <QObject>
#include <QDomDocument>

class BackupXMLParser
{
public:
    BackupXMLParser(const QString &filePath);

    bool Parse();

    void write(QList<QMap<QString, QString>> smses);

private:
    QString _filePath;
    QDomDocument domDocument;
};

#endif // BACKUPXMLPARSER_H
