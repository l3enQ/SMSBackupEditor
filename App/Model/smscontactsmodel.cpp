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

void SMSContactsModel::loadFile(QString path)
{
    clear();
    setColumnCount(1);
    emit loadFileRequested(path);
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
    emit dataChanged(index(0, 0), index(rowCount() - 1, 0), {selectRole});
    emit contactSelected(selectedRow);
}

void SMSContactsModel::selectSMS(int row, int selected)
{
    auto list = data(index(selectedRow, 0), dataRole).value<QList<QMap<QString, QString>>>();
    list[row].insert("select", QString::number(selected));
    setData(index(selectedRow, 0), QVariant::fromValue(list), dataRole);
}

void SMSContactsModel::onExportReq(QString path)
{
    smsMap exportData;
    for (int var = 0; var < rowCount(); ++var) {
        QString sender = data(index(var, 0), senderRole).toString();

        QList<QMap<QString, QString>> senderData = data(index(var, 0), dataRole)
                .value<QList<QMap<QString, QString>>>();
        for (int sms = 0; sms < senderData.count(); ++sms) {
            QMap<QString, QString> smsData = senderData.at(sms);
            int selected = smsData.value("select").toInt();
            if (selected == 1) {
                smsData.remove("select");
                exportData.insertMulti(sender, smsData);
            }
        }
    }

    emit exportReady(exportData, path);
}

void SMSContactsModel::onDataReady(smsMap data)
{
    setRowCount(data.uniqueKeys().count());
    for (int var = 0; var < rowCount(); ++var) {
        setData(index(var, 0), data.uniqueKeys().at(var),
                senderRole);
        setData(index(var, 0), QVariant::fromValue(data.values(data.uniqueKeys().at(var))),
                dataRole);
    }
}
