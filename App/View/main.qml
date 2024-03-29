import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.14

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("SMS Backup Editor")
    minimumWidth:  320;
    minimumHeight: 320;
    Material.theme : Material.Light
    Material.accent: Material.Green

    SplitView {
        id : splitView
        anchors.fill: parent

        SMSLoader {
            SplitView.preferredWidth: 200;
            SplitView.minimumWidth  : 100;
            SplitView.maximumWidth  : window.width < 600
                                      ? 200
                                      : 400;
        }

        SMSViewer {
            SplitView.preferredWidth: 500;
            SplitView.minimumWidth  : 100;
            SplitView.fillWidth     : true;
        }

        handle: Rectangle {
            implicitWidth: 2
            radius       : 2
            color: SplitHandle.pressed ? "#ff009900"
                                       : (SplitHandle.hovered
                                          ? "#99009900"
                                          : "#55009900")
        }
    }
}
