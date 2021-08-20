import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: contactsView

    width : 400
    height: 400

    ListView {
        id: loadedItems

        anchors.fill: parent

        model: contactModel;

        delegate: SwipeDelegate {
            id: delegate

            width: parent.width

            text      : senderRole
            font.bold : selectRole
            background: Rectangle {
                color : Material.color( (index % 2 === 0)
                                       ? Material.LightGreen :
                                         Material.LightBlue,
                                       Material.Shade100)
            }

            swipe.onClosed: {
                contactModel.select(index)
                undoTimer.stop()
            }

            //! [delegate]
            swipe.right: Rectangle {
                width : parent.width
                height: parent.height
                clip  : true
                color : SwipeDelegate.pressed ? "#555" : "#666"

                Label {
                    anchors.fill: parent
                    padding     : 10

                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment  : Qt.AlignVCenter

                    font.family : "Fontello"
                    text        : delegate.swipe.complete ? "\ue805" // icon-cw-circled
                                                          : "\ue801" // icon-cancel-circled-1
                    color       : Material.color(delegate.swipe.complete
                                                 ? Material.Green
                                                 : Material.Red,
                                                 Material.Shade200)
                    opacity     : 2 * -delegate.swipe.position

                    Behavior on color { ColorAnimation {} }
                }

                Label {
                    anchors.fill: parent
                    padding     : 20

                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment  : Qt.AlignVCenter

                    text   : qsTr("Removed")
                    color  : Material.color(Material.Red, Material.Shade200)
                    opacity: delegate.swipe.complete ? 1 : 0


                    Behavior on opacity { NumberAnimation {} }
                }

                SwipeDelegate.onClicked:  delegate.swipe.close()
                // SwipeDelegate.onPressedChanged: undoTimer.stop()
            }
            //! [delegate]

            //! [removal]
            Timer {
                id: undoTimer

                interval   : 2000
                onTriggered: contactModel.remove(index)
            }

            swipe.onCompleted: undoTimer.start()
            //! [removal]
        }

        //! [transitions]
        remove: Transition {
            SequentialAnimation {
                PauseAnimation  { duration: 125 }
                NumberAnimation { property: "height"; to: 0; easing.type: Easing.InOutQuad }
            }
        }

        displaced: Transition {
            SequentialAnimation {
                PauseAnimation  { duration: 125 }
                NumberAnimation { property: "y"; easing.type: Easing.InOutQuad }
            }
        }
        //! [transitions]

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    Label {
        id: placeholder
        text: qsTr("Browse a xml file")

        anchors.fill   : parent
        anchors.margins: 10

        opacity : 0.5
        visible : loadedItems.count === 0
        wrapMode: Label.WordWrap

        font.pixelSize: 22

        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment  : Qt.AlignVCenter
    }
}
