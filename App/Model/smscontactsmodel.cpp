#include "smscontactsmodel.h"

SMSContactsModel::SMSContactsModel(QObject *parent) : QStandardItemModel(parent)
{
    // testData
    {
        setColumnCount(1);
        setRowCount(5);
        setData(index(0, 0), "1", SMSContactsModel::textRole);
        setData(index(1, 0), "asdssd2", SMSContactsModel::textRole);
        setData(index(2, 0), "4dsd", SMSContactsModel::textRole);
        setData(index(3, 0), "5", SMSContactsModel::textRole);
        setData(index(4, 0), "5ssssssssssssss", SMSContactsModel::textRole);
    }

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
    result.insert(textRole, QByteArrayLiteral("textRole"));
    result.insert(selectRole, QByteArrayLiteral("selectRole"));
    return result;
}

void SMSContactsModel::remove(int row) {
    removeRow(row);
}

void SMSContactsModel::select(int row) {
    selectedRow = row;
    emit dataChanged(index(0, 0), index(rowCount() - 1, 0));
}

void SMSContactsModel::check(int row) {
    setData(index(rowCount() - 1, 0), data(index(row, 0), SMSContactsModel::textRole),
            SMSContactsModel::textRole);
}

void SMSContactsModel::onDataReady(smsMap data)
{
    clear();
    setColumnCount(1);
    setRowCount(data.uniqueKeys().count());
    for (int var = 0; var < rowCount(); ++var) {
        setData(index(var, 0), data.uniqueKeys().at(var), SMSContactsModel::textRole);
    }
}
