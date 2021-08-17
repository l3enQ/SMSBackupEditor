import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("SMS Backup Editor")
    minimumWidth:  320;
    minimumHeight: 320;

    SplitView{
        id : splitView
        anchors.fill: parent

        SMSLoader{
            SplitView.preferredWidth: 200;
            SplitView.minimumWidth: 100;
            SplitView.maximumWidth: window.width < 600 ? 200 : 400;
        }

        SMSViewer {
            SplitView.preferredWidth: 500;
            SplitView.minimumWidth: 100;
            SplitView.fillWidth: true;
        }

        handle: Rectangle {
            implicitWidth:  2
            color: SplitHandle.pressed ? "#ff0000"
                : (SplitHandle.hovered ? "#00ff00" : "#009900")
        }
    }
}
