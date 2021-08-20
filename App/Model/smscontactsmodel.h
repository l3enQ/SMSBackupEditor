#ifndef SMSCONTACTSMODEL_H
#define SMSCONTACTSMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>
#include "backupxmlparser.h"

class SMSContactsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SMSContactsModel(QObject *parent = nullptr);

    enum Roles  {
        dataRole   = Qt::UserRole + 4,
        senderRole = Qt::UserRole + 5,
        selectRole = Qt::UserRole + 6
    };
    Q_ENUM(Roles)

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    int selectedRow = -1;

public slots:
    Q_INVOKABLE void loadFile(QString path);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE void select(int row);
    Q_INVOKABLE void onExportReq(QString path);

    void onDataReady(smsMap data);
    void selectSMS(int row, int selected);

signals:
    void loadFileRequested(QString path);
    void contactSelected(int row);
    void exportReady(smsMap data, QString path);
};

#endif // SMSCONTACTSMODEL_H
