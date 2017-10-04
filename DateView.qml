import QtGraphicalEffects 1.0
import QtQuick 2.0
import QtQuick.Controls 2.2

import "dateTimeAuxiliary.js" as DateTimeAux

Rectangle {
    property date date: new Date()
    property color foregroundColor: "black"

    signal expandButtonClicked()

    height: 40
    color: "transparent"

    Row {
        anchors.fill: parent
//        anchors.leftMargin: 12
        spacing: 8

        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: foregroundColor
            font.bold: true
            font.pointSize: 14
            text: date.getDate()
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: foregroundColor
            font.bold: true
            font.pointSize: 14
            text: DateTimeAux.monthNumberToName(date.getMonth() + 1)
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: foregroundColor
            font.bold: true
            font.pointSize: 14
            text: date.getFullYear()
        }
    }

    Button {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: height
        height: parent.height
        contentItem: Item {
            Image {
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 10
                source: "icons/ic_event_black_24px.svg"
                ColorOverlay {
                    source: parent
                    anchors.fill: parent
                    color: foregroundColor
                }
            }
        }
        background: Rectangle {
            color: "transparent"
        }
        onClicked: expandButtonClicked()
    }
}
