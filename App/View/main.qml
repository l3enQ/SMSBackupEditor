import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("SMS Backup Editor")

    SplitView{
        id : splitView
        anchors.fill: parent

        SMSLoader{
            SplitView.preferredWidth: 200;
            SplitView.minimumWidth: 0;
            SplitView.maximumWidth: 400
        }

        SMSViewer {
            SplitView.preferredWidth: 500;
            SplitView.minimumWidth: 300;
            SplitView.fillWidth: true;
        }

        handle: Rectangle {
            implicitWidth:  2
            color: SplitHandle.pressed ? "#ff0000"
                : (SplitHandle.hovered ? "#00ff00" : "#009900")
        }
    }
}
