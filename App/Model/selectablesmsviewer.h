#ifndef SELECTABLESMSVIEWER_H
#define SELECTABLESMSVIEWER_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>
#include "backupxmlparser.h"

class SelectableSMSViewer : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SelectableSMSViewer(QObject *parent = nullptr);

    enum Roles  {
        selectRole = Qt::UserRole + 4,
        textRole   = Qt::UserRole + 5,
        dateRole   = Qt::UserRole + 6,
        dataRole   = Qt::UserRole + 1,
        servRole   = Qt::UserRole + 2
    };
    Q_ENUM(Roles)
    QHash<int,QByteArray> roleNames() const override;

private:
    int selectedRow = 2;

public slots:
    Q_INVOKABLE void check(int row, bool checked);

    void onDataReady(QList<QMap<QString, QString>> data);
};

#endif // SELECTABLESMSVIEWER_H
