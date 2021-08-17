#ifndef SMSCONTACTSMODEL_H
#define SMSCONTACTSMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>

class SMSContactsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SMSContactsModel(QObject *parent = nullptr);

    enum Roles  {
        selectRole = Qt::UserRole + 4,
        textRole = Qt::UserRole + 5
    };
    Q_ENUM(Roles)

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    int selectedRow = 2;

public slots:
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE void select(int row);
    Q_INVOKABLE void check(int row);

signals:

};

#endif // SMSCONTACTSMODEL_H
