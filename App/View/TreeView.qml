import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: window
    width: 400
    height: 400
    visible: true

    ListView {
        id: listView
        anchors.fill: parent

        delegate: SwipeDelegate {
            id: delegate

            text: senderRole
            width: parent.width
            font.bold: selectRole

            swipe.onClosed: {
                contactModel.select(index)
                undoTimer.stop()
            }

            //! [delegate]
            swipe.right: Rectangle {
                width: parent.width
                height: parent.height
                clip: true
                color: SwipeDelegate.pressed ? "#555" : "#666"

                Label {
                    font.family: "Fontello"
                    text: delegate.swipe.complete ? "\ue805" // icon-cw-circled
                                                  : "\ue801" // icon-cancel-circled-1

                    padding: 20
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment: Qt.AlignVCenter

                    opacity: 2 * -delegate.swipe.position

                    color: Material.color(delegate.swipe.complete ? Material.Green : Material.Red, Material.Shade200)
                    Behavior on color { ColorAnimation { } }
                }

                Label {
                    text: qsTr("Removed")
                    color: "white"

                    padding: 20
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter

                    opacity: delegate.swipe.complete ? 1 : 0
                    Behavior on opacity { NumberAnimation { } }
                }

                SwipeDelegate.onClicked:  delegate.swipe.close()
                //                SwipeDelegate.onPressedChanged: undoTimer.stop()
            }
            //! [delegate]

            //! [removal]
            Timer {
                id: undoTimer
                interval: 1000
                onTriggered: contactModel.remove(index)
            }

            swipe.onCompleted: undoTimer.start()
            //! [removal]
        }

        model: contactModel;

        //! [transitions]
        remove: Transition {
            SequentialAnimation {
                PauseAnimation { duration: 125 }
                NumberAnimation { property: "height"; to: 0; easing.type: Easing.InOutQuad }
            }
        }

        displaced: Transition {
            SequentialAnimation {
                PauseAnimation { duration: 125 }
                NumberAnimation { property: "y"; easing.type: Easing.InOutQuad }
            }
        }
        //! [transitions]

        ScrollIndicator.vertical: ScrollIndicator { }
    }

    Label {
        id: placeholder
        text: qsTr("Nothing loaded!")

        anchors.margins: 60
        anchors.fill: parent

        opacity: 0.5
        visible: listView.count === 0

        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Label.WordWrap
        font.pixelSize: 18
    }
}
