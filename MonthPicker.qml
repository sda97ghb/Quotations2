import QtGraphicalEffects 1.0
import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    signal selected(int month)
    signal backClicked()

    color: "transparent"

    ListView {
        clip: true
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        model: ["January", "February", "March", "April", "May", "June",
            "Jule", "August", "September", "October", "November", "December"]
        delegate: Button {
            anchors.horizontalCenter: parent.horizontalCenter
            height: 30
            background: Rectangle {
                color: "transparent"
            }
            contentItem: Text {
                font.pointSize: 14
                text: modelData
            }
            onClicked: selected(index)
        }
        ScrollIndicator.vertical: ScrollIndicator {
        }
    }

    Button {
        anchors.left: parent.left
        anchors.top: parent.top
        width: 30
        height: 30
        hoverEnabled: true
        contentItem: Item {
            Image {
                anchors.centerIn: parent
                source: "icons/ic_arrow_back_black_24px.svg"
                ColorOverlay {
                    source: parent
                    anchors.fill: parent
                    color: parent.parent.parent.down ? "white" : "black"
                }
            }
        }
        background: Rectangle {
            color: parent.down ? "black" : (parent.hovered ? "#e0e0e0" : "transparent")
        }
        onClicked: backClicked()
    }
}
