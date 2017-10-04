import Qt.labs.calendar 1.0
import QtGraphicalEffects 1.0
import QtQuick 2.0
import QtQuick.Controls 2.2

import "dateTimeAuxiliary.js" as DateTimeAux

Item {
    id: dayPicker
    property date date: new Date()

    property int headerPadding: 0

    signal hideButtonClicked()
    signal dateSelected(date date)
    signal monthClicked()
    signal yearClicked()

    onDateChanged: {
        var today = dayPicker.date
        listview.currentIndex = (today.getFullYear() - 2015) * 12 + today.getMonth()

    }

    Rectangle {
        id: topLine

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 40
        color: "white"

        Row {
            anchors.fill: parent
            anchors.leftMargin: headerPadding
            spacing: 8

            Button {
                width: contentItem.implicitWidth + 10
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                background: Rectangle {
                    color: parent.down ? "black" : (parent.hovered ? "#e0e0e0" : "transparent")
                }
                hoverEnabled: true
                contentItem: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: parent.down ? "white" : "black"
                    font.bold: true
                    font.pointSize: 14
                    text: DateTimeAux.monthNumberToName(listview.model.monthAt(listview.currentIndex) + 1)
                }
                onClicked: monthClicked()
            }

            Button {
                width: contentItem.implicitWidth + 10
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                background: Rectangle {
                    color: parent.down ? "black" : (parent.hovered ? "#e0e0e0" : "transparent")
                }
                hoverEnabled: true
                contentItem: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: parent.down ? "white" : "black"
                    font.bold: true
                    font.pointSize: 14
                    text: listview.model.yearAt(listview.currentIndex)
                }
                onClicked: yearClicked()
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
                        color: "black"
                    }
                }
            }
            background: Rectangle {
                color: "transparent"
            }
            onClicked: hideButtonClicked()
        }
    }

    DayOfWeekRow {
        id: dayOfWeekRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topLine.bottom
        background: Rectangle {
            color: "white"
        }
        delegate: Text {
            text: model.narrowName
            color: "#bdbebf"
            horizontalAlignment: Text.AlignHCenter
        }
        Rectangle {
            color: "#C7CDD2"
            height: 1
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }

    ListView {
        id: listview

        clip: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: dayOfWeekRow.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        currentIndex: {
            var today = dayPicker.date
            return (today.getFullYear() - 2015) * 12 + today.getMonth()
        }

        model: CalendarModel {
            from: new Date(2015, 0, 1)
            to: new Date(2020, 11, 30)
        }

        delegate: MonthGrid {
            id: monthGrid

            width: listview.width
            height: listview.height

            month: model.month
            year: model.year

            spacing: 0

            delegate: Item {
                function cellStr() {
                    return "%1.%2.%3".arg(model.day).arg(model.month).arg(model.year)
                }

                function selectedStr() {
                    var now = dayPicker.date
                    return "%1.%2.%3".arg(now.getDate()).arg(now.getMonth()).arg(now.getFullYear())
                }

                function todayStr() {
                    var now = new Date()
                    return "%1.%2.%3".arg(now.getDate()).arg(now.getMonth()).arg(now.getFullYear())
                }

                Rectangle {
                    anchors.fill: parent
                    color: "#e0e0e0"
                    visible: model.month !== monthGrid.month
                }

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "black"
                    border.width: 1
                    radius: height * 0.1
                    visible: cellStr() === selectedStr()
                }

                Rectangle {
                    color: "#bdbebf"
                    width: parent.width * 0.5
                    height: width * 0.2
                    radius: height / 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.1
                    visible: {
                        return cellStr() === todayStr()
                    }
                }

                Text {
                    text: model.day
                    color: {
                        if (model.month !== monthGrid.month)
                            return "#bdbebf"
                        return "black"
                    }
                    anchors.centerIn: parent
                    font.pointSize: model.date === datePicker.date ? 14 : 11
                }
            }

            onClicked: dateSelected(date)
        }

        highlightMoveDuration: 300
        highlightFollowsCurrentItem: true
        ScrollIndicator.horizontal: ScrollIndicator { }
    }
}
