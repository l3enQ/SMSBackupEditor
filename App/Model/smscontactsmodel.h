#ifndef SMSCONTACTSMODEL_H
#define SMSCONTACTSMODEL_H

#include <QStandardItemModel>
#include "backupxmlparser.h"

class SMSContactsModel: public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SMSContactsModel(QObject *parent = nullptr);

    enum Roles  {
        selectRole = Qt::UserRole + 1,
        senderRole = Qt::UserRole + 2,
        dataRole   = Qt::UserRole + 3
    };
    Q_ENUM(Roles)

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

public slots:
    Q_INVOKABLE void loadFile(QString path);
    Q_INVOKABLE void onExportReq(QString path);
    Q_INVOKABLE void select(int row);
    Q_INVOKABLE void remove(int row);

    void onDataReady(smsMap data);
    void selectSMS(int row, int selected);

signals:
    void loadFileRequested(QString path);
    void contactSelected(int row);
    void exportReady(smsMap data, QString path);

private:
    int selectedRow = -1;
};

#endif // SMSCONTACTSMODEL_H
