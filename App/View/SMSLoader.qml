import QtQuick 2.0
import QtQuick.Controls 1.4

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {
    onWidthChanged: {
        console.log(width)
    }

    width: width > 150 ? width : 0

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 2
        spacing: 2

        RowLayout {
            Button {
                id: browseBtn
                text: "Browse.."
                onClicked: {
                    console.log("clicked")
                }
            }
            TextField {
                id: pathField
                Layout.alignment: Qt.AlignBaseline
                Layout.fillWidth: true
                text: ""
                readOnly: true;
            }
        }

        TreeView {
            clip: true
            Layout.fillWidth: true
            TableViewColumn {
                title: "Name"
                role: "fileName"
                width: 50
            }
            TableViewColumn {
                title: "Permissions"
                role: "filePermissions"
                width: 80
            }
            Layout.fillHeight: true
        }

    }
    //        model: fileSystemModel
}
