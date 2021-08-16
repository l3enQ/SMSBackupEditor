import QtQuick 2.0
//import QtQuick 2.3

import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Item {
    onWidthChanged: {
        console.log(width)
    }

    width: width > 150 ? width : 0

    //! [filedialog]
    FileDialog {
        id: fileDialog
//        visible: browseBtn.pressed
        modality: Qt.WindowModal;
        title: "Choose some files";
        selectExisting: true;
        selectMultiple: false;
        selectFolder: false;
        nameFilters: [ "XML files (*.xml)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls[0])
            pathField.text = fileUrls[0];
        }
        onRejected: { console.log("Rejected") }
    }
    //! [filedialog]

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
                    fileDialog.visible = true;
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
