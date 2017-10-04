import Qt.labs.calendar 1.0
import QtGraphicalEffects 1.0
import QtQuick 2.0
import QtQuick.Controls 2.2

import "dateTimeAuxiliary.js" as DateTimeAux

Item {
    id: datePicker

    property date date: new Date()

    clip: true
    width: 255
//    height: 260 // TODO: remove this line
    state: "spoilered"

    QtObject {
        id: internal
    }

    DateView {
        id: dateView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        date: datePicker.date
        onExpandButtonClicked: datePicker.state = "expanded"
    }

    StackView {
        id: picking
        anchors.fill: parent
        initialItem: dayPicker
        Component {
            id: dayPicker
            DayPicker {
                date: datePicker.date
                onHideButtonClicked: datePicker.state = "spoilered"
                onDateSelected: {
                    datePicker.date = date
                    datePicker.state = "spoilered"
                }
                onMonthClicked: picking.push(monthPicker)
                onYearClicked: console.log("year clicked")
            }
        }
        Component {
            id: monthPicker
            MonthPicker {
                onSelected: {
                    datePicker.date = new Date(datePicker.date.getFullYear(), month, datePicker.date.getDate())
                    picking.pop()
                }
                onBackClicked: picking.pop()
            }
        }
    }

    states: [
        State {
            name: "spoilered"
            PropertyChanges {target: datePicker; height: 40}
            PropertyChanges {target: dateView; visible: true}
            PropertyChanges {target: picking; visible: false}
        },
        State {
            name: "expanded"
            PropertyChanges {target: datePicker; height: 260}
            PropertyChanges {target: dateView; visible: false}
            PropertyChanges {target: picking; visible: true}
        }
    ]

    transitions: [
        Transition {
            from: "spoilered"
            to: "expanded"
            PropertyAnimation {target: datePicker; properties: "height"; duration: 100; easing.type: "OutBack"}
            PropertyAnimation {target: dateView; properties: "visible"; duration: 100}
            PropertyAnimation {target: picking; properties: "visible"; duration: 100}
        },
        Transition {
            from: "expanded"
            to: "spoilered"
            PropertyAnimation {target: datePicker; properties: "height"; duration: 100; easing.type: "InBack"}
            PropertyAnimation {target: dateView; properties: "visible"; duration: 100}
            PropertyAnimation {target: picking; properties: "visible"; duration: 100}
        }
    ]
}
