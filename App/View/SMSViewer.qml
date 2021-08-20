import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.12

ListView {
    id  : listView
    clip: true

    model: viewerModel

    delegate: Item {
        id: item1

        width : parent.width;
        height: text1.height + 14;

        Item {
            id: name

            anchors.fill     : parent
            Layout.fillHeight: true

            height: text1.height + 12

            RowLayout {
                anchors.fill     : parent
                Layout.fillWidth : true;
                Layout.fillHeight: true
                anchors.margins  : 2
                spacing          : 2;

                CheckBox {
                    id: checkBox1

                    Layout.alignment: Qt.AlignTop

                    checked: selectRole

                    onCheckedChanged: {
                        viewerModel.check(index, checked)
                    }
                }

                Rectangle {
                    Layout.fillWidth: (typeRole === "1")

                    color : "#00fdfdfd"
                    height: 2
                    width : 10
                }

                Rectangle {
                    Layout.fillWidth : true
                    Layout.fillHeight: true

                    clip  : true
                    height: text1.height + 10;
                    width : 15

                    border.color: Material.color(Material.Grey, Material.Shade100)
                    border.width: 1
                    radius      : 10
                    color       : Material.color( (typeRole === "2")
                                                 ? Material.LightGreen
                                                 : Material.LightBlue,
                                                   Material.Shade100)
                    Text {
                        id: text1

                        anchors.fill   : parent
                        anchors.margins: 5
                        clip           : true
                        height         : contentHeight + 10;
                        text           : qsTr(textRole)
                        font.family    : "fontello"
                        wrapMode       : Text.WordWrap
                        font.pixelSize : 10
                    }
                }

                Rectangle {
                    Layout.fillWidth: (typeRole === "2")

                    color : "#00fdfdfd"
                    height: 2
                    width : 10
                }
            }
        }
    }
}
