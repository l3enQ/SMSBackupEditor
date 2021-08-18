#include "selectablesmsviewer.h"

SelectableSMSViewer::SelectableSMSViewer(QObject *parent) : QStandardItemModel(parent)
{

}

QHash<int, QByteArray> SelectableSMSViewer::roleNames() const
{
    QHash<int, QByteArray> result = QStandardItemModel::roleNames();
    result.insert(dataRole,   QByteArrayLiteral("dataRole"));
    result.insert(dateRole,   QByteArrayLiteral("dateRole"));
    result.insert(textRole,   QByteArrayLiteral("textRole"));
    result.insert(servRole,   QByteArrayLiteral("servRole"));
    result.insert(selectRole, QByteArrayLiteral("selectRole"));
    return result;
}

void SelectableSMSViewer::check(int row, bool checked)
{
    setData(index(row, 0), checked ? 1 : 0, selectRole);
}

void SelectableSMSViewer::onDataReady(QList<QMap<QString, QString>> data)
{
    clear();

    setColumnCount(1);
    setRowCount(data.count());

    for (int row = 0; row < rowCount(); ++row) {
        qDebug() << row << data.at(row).value("select", "0").toInt();
        setData(index(row, 0), QVariant::fromValue(data.at(row)),         dataRole);
        setData(index(row, 0), data.at(row).value("readable_date"),       dateRole);
        setData(index(row, 0), data.at(row).value("select", "0").toInt(), selectRole);
        setData(index(row, 0), data.at(row).value("body"),                textRole);
        setData(index(row, 0), data.at(row).value("service_center"),      servRole);
    }
}
