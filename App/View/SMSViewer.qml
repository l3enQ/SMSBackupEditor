import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1

ListView {
    id: listView
    model: viewerModel
    clip: true

    delegate: Item {
        id: item1
        height: text1.height + 14;
        width: parent.width;
        Item {
            id: name
            height: text1.height + 12
            anchors.fill: parent
            Layout.fillHeight: true
            RowLayout {
                anchors.fill: parent
                Layout.fillWidth: true;
                spacing: 2;
                anchors.margins: 2
                Layout.fillHeight: true
                CheckBox {
                    id: checkBox1
                    checked: selectRole
                    Layout.alignment: Qt.AlignTop
                    onCheckedChanged: {
                        viewerModel.check(index, checked)
                    }
                }
                Rectangle {
                    color : "#00fdfdfd"
                    height: 2
                    width : 10
                    Layout.fillWidth: (typeRole === "1")
                }
                Rectangle {
                    color: (typeRole === "2") ? "#44880000" : "#44000088"
                    border.color: "#191919"
                    border.width: 1
                    radius: 10
                    height: text1.height + 10;
                    width : 15
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    Text {
                        id:text1
                        anchors.fill: parent
                        anchors.margins: 5
                        text: qsTr(textRole)
                        font.family: "fontello"
                        clip: true
                        height: contentHeight + 10;
                        wrapMode: Text.WordWrap
                        font.pixelSize: /*checkBox1.pressed ? 14:*/10
                    }
                }
                Rectangle {
                    color : "#00fdfdfd"
                    height: 2
                    width : 10
                    Layout.fillWidth: (typeRole === "2")
                }
            }
        }
    }
}
