import QtQuick 2.0
import QtQuick.Controls 2.2

Button {
    property alias icon: icon.source

    width: 50
    height: 40

    contentItem: Item {
        Image {
            id: icon
            anchors.centerIn: parent
        }
    }
}
