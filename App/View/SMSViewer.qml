import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1

ListView {
    model: viewerModel
    clip: true

    delegate: Item {
        id: item1
        height: 50;
        width: parent.width;
        RowLayout {
            spacing: 10;
            CheckBox {
                checked: selectRole
                onCheckedChanged: {
                    viewerModel.check(index, checked)
                }
            }
            Label {
                id:text1
                text: textRole
            }

        }
    }

}

