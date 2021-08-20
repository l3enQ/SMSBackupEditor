#ifndef SELECTABLESMSVIEWER_H
#define SELECTABLESMSVIEWER_H

#include <QStandardItemModel>

class SelectableSMSViewer : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SelectableSMSViewer(QObject *parent = nullptr);

    enum Roles  {
        selectRole = Qt::UserRole + 1,
        dateRole   = Qt::UserRole + 2,
        servRole   = Qt::UserRole + 3,
        textRole   = Qt::UserRole + 4,
        typeRole   = Qt::UserRole + 5,
        dataRole   = Qt::UserRole + 6
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
