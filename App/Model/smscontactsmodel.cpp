#include "smscontactsmodel.h"

SMSContactsModel::SMSContactsModel(QObject *parent) : QStandardItemModel(parent)
{
}

QVariant SMSContactsModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role >= selectRole) {
        switch (role) {
        case selectRole:
            return QVariant(selectedRow == index.row());
        default:
            break;
        }
    }
    return QStandardItemModel::data(index, role);
}

QHash<int, QByteArray> SMSContactsModel::roleNames() const
{
    QHash<int, QByteArray> result = QStandardItemModel::roleNames();
    result.insert(senderRole, QByteArrayLiteral("senderRole"));
    result.insert(selectRole, QByteArrayLiteral("selectRole"));
    result.insert(dataRole,   QByteArrayLiteral("dataRole"));
    return result;
}

void SMSContactsModel::remove(int row)
{
    removeRow(row);
    if (row < selectedRow)
        selectedRow--;
    else if (row == selectedRow)
        select(selectedRow);
}

void SMSContactsModel::select(int row)
{
    selectedRow = row;
    emit selectionChanged(selectedRow);
}

void SMSContactsModel::selectSMS(int row, int selected)
{
    qDebug() << selectedRow << selected;
    auto list = data(index(selectedRow, 0), dataRole).value<QList<QMap<QString, QString>>>();
    list[row].insert("select", QString::number(selected));
    setData(index(selectedRow, 0), QVariant::fromValue(list), dataRole);
}

void SMSContactsModel::onDataReady(smsMap data)
{
    clear();
    setColumnCount(1);
    setRowCount(data.uniqueKeys().count());
    for (int var = 0; var < rowCount(); ++var) {
        setData(index(var, 0), data.uniqueKeys().at(var),
                senderRole);
        setData(index(var, 0), QVariant::fromValue(data.values(data.uniqueKeys().at(var))),
                dataRole);
    }
}
