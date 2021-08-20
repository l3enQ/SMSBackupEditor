import QtQuick 2.0
//import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Item {
    clip: true
    onWidthChanged: {
        width = width > 150 ? width : 0;
    }

    //! [filedialog]
    FileDialog {
        id: fileDialog
        modality: Qt.WindowModal;
        title: "Choose some files";
        selectExisting: true;
        selectMultiple: false;
        selectFolder: false;
        nameFilters: [ "XML files (*.xml)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: true
        onAccepted: {
            var path = fileDialog.fileUrl.toString();
            path = path.replace(/^(file:\/{3})/,"");
            // unescape html codes like '%23' for '#'
            var cleanPath = decodeURIComponent(path);
            console.log("Accepted: " + cleanPath)

            pathField.text = cleanPath;
            xmlReader.setFilepath(cleanPath);
        }
        onRejected: { console.log("Rejected") }
    }

    FileDialog {
        id: saveDialog
        modality: Qt.WindowModal;
        title: "Export to ...";
        selectExisting: false;
        selectMultiple: false;
        selectFolder: false;
        nameFilters: [ "XML files (*.xml)" ]
        selectedNameFilter: "XML files (*.xml)"
        sidebarVisible: true
        onAccepted: {
            var path = saveDialog.fileUrl.toString();
            path = path.replace(/^(file:\/{3})/,"");
            // unescape html codes like '%23' for '#'
            var cleanPath = decodeURIComponent(path);
            console.log("Accepted: " + cleanPath)

            xmlReader.exportToFile(cleanPath);
//            contactModel.onExportReq(cleanPath);
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
                    fileDialog.visible = true;
                }
            }
            TextField {
                id: pathField
                Layout.alignment: Qt.AlignBaseline
                Layout.fillWidth: true
                text: ""
                readOnly: true;
                ToolTip.text: text
                ToolTip.visible: text ? ma.containsMouse : false
                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }

        TreeView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: publishBtn
            text: "Publish selected objects"
            onClicked: {
                saveDialog.visible = true;
            }
        }
    }
}
