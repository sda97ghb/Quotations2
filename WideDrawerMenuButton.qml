import QtQuick 2.0
import QtQuick.Controls 2.2

Button {
    id: button

    property alias icon: icon.source

    height: 40
    width: parent.width

    contentItem: Row {
        anchors.fill: parent
        spacing: 20
        Item {
            anchors.verticalCenter: parent.verticalCenter
            height: button.height
            width: 50
            Image {
                id: icon
                anchors.centerIn: parent
            }
        }
        Label {
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Label.AlignVCenter
            horizontalAlignment: Label.AlignLeft
            text: button.text
        }
    }
}
