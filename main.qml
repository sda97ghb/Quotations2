import QtQuick 2.8
import QtQuick.Controls 2.2

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 1280
    height: 720
    title: "Quotations"

    SwipeView {
        id: swipeView

        anchors.left: drawerMenu.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        clip: true

        QuotationsCandlestickChart {
        }

        LongPeriodStatistics {
        }

        DealsHistogram {
        }
    }

    Item {
        id: drawerMenu

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        clip: false
        width: 50

        Rectangle {
            anchors.fill: parent
            color: "lightgray"
        }

        Column {
            anchors.fill: parent

            SmallDrawerMenuButton {
                icon: "icons/ic_menu.svg"
                onClicked: drawerMenu.state = "expanded"
            }

            SmallDrawerMenuButton {
                icon: "icons/ic_chart.svg"
                onClicked: swipeView.currentIndex = 0
            }
            SmallDrawerMenuButton {
                icon: "icons/ic_long_period_statistic.svg"
                onClicked: swipeView.currentIndex = 1
            }
            SmallDrawerMenuButton {
                icon: "icons/ic_histogram.svg"
                onClicked: swipeView.currentIndex = 2
            }
        }

        Item {
            id: expandedMenu
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 250

            MouseArea {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: mainWindow.width
                onClicked: drawerMenu.state = "small"
            }

            Rectangle {
                anchors.fill: parent
                color: "lightgray"
            }

            Column {
                anchors.fill: parent

                SmallDrawerMenuButton {
                    icon: "icons/ic_menu.svg"
                    onClicked: drawerMenu.state = "small"
                }

                WideDrawerMenuButton {
                    text: "Quotations"
                    icon: "icons/ic_chart.svg"
                    onClicked: swipeView.currentIndex = 0
                }

                WideDrawerMenuButton {
                    text: "Long period statistic"
                    icon: "icons/ic_long_period_statistic.svg"
                    onClicked: swipeView.currentIndex = 1
                }

                WideDrawerMenuButton {
                    text: "Deals volume histogram"
                    icon: "icons/ic_histogram.svg"
                    onClicked: swipeView.currentIndex = 2
                }
            }
        }

        state: "small"

        states: [
            State {
                name: "small"
                PropertyChanges { target: expandedMenu; visible: false }
                PropertyChanges { target: expandedMenu; width: 50 }
            },
            State {
                name: "expanded"
                PropertyChanges { target: expandedMenu; visible: true }
                PropertyChanges { target: expandedMenu; width: 250 }
            }
        ]

        transitions: [
            Transition {
                from: "small"
                to: "expanded"
                PropertyAnimation { target: expandedMenu; properties: "width"; duration: 100 }
            },
            Transition {
                from: "expanded"
                to: "small"
                PropertyAnimation { target: expandedMenu; properties: "width"; duration: 100 }
                PropertyAnimation { target: expandedMenu; properties: "visible"; duration: 100 }
            }
        ]
    }
}
