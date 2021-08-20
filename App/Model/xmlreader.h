#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>

class XMLReader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString filepath READ filePath WRITE setFilepath NOTIFY filepathChanged)

public:
    explicit XMLReader(QObject *parent = nullptr);

    Q_INVOKABLE QString filePath();
    Q_INVOKABLE void setFilepath(QString path);
    Q_INVOKABLE void exportToFile(QString path);

signals:
    void filepathChanged(QString);
    void exportToFileRequested(QString);

private:
    QString _filePath;
};

#endif // XMLREADER_H
