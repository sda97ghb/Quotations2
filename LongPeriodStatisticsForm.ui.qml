import MyTypes 1.0
import QtQuick 2.4
import QtQuick.Controls 2.2

Item {
    property alias longPeriodDealsStatisticsModel: longPeriodDealsStatisticsModel
    property alias todayDealsStatisticsModel: todayDealsStatisticsModel

    width: 1280
    height: 720
    property alias loadingRectangle: loadingRectangle
    property alias dateToPicker: dateToPicker
    property alias dateFromPicker: dateFromPicker
    property alias tickerSelector: tickerSelector
    property alias updateButton: updateButton

    Rectangle {
        id: rightPanelSplitter
        x: 868
        width: 1
        color: "#000000"
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.right: scrollView.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Row {
        id: row
        x: 10
        y: 10
        anchors.rightMargin: 10
        anchors.right: rightPanelSplitter.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.leftMargin: 10

        Statistics {
            id: todayStatistics

            title: todayDealsStatisticsModel.statistics.title

            numberOfDeals: todayDealsStatisticsModel.statistics.numberOfDeals
            averageVolume: todayDealsStatisticsModel.statistics.averageVolume
            minVolume: todayDealsStatisticsModel.statistics.minVolume
            maxVolume: todayDealsStatisticsModel.statistics.maxVolume

            numberOfBuyDeals: todayDealsStatisticsModel.statistics.numberOfBuyDeals
            averageBuyVolume: todayDealsStatisticsModel.statistics.averageBuyVolume
            minBuyVolume: todayDealsStatisticsModel.statistics.minBuyVolume
            maxBuyVolume: todayDealsStatisticsModel.statistics.maxBuyVolume

            numberOfSellDeals: todayDealsStatisticsModel.statistics.numberOfSellDeals
            averageSellVolume: todayDealsStatisticsModel.statistics.averageSellVolume
            minSellVolume: todayDealsStatisticsModel.statistics.minSellVolume
            maxSellVolume: todayDealsStatisticsModel.statistics.maxSellVolume

            TodayDealsStatisticsModel {
                id: todayDealsStatisticsModel

                ticker: tickerSelector.currentText
                date: todayDatePicker.date
            }
        }

        Item {
            width: 20
            height: parent.height

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 1
                height: parent.height
                color: "#000000"
            }
        }

        ListView {
            id: dayOfWeekStatisticsListView
            x: 0
            y: 0
            width: 750
            height: 470
            orientation: ListView.Horizontal
            delegate: Statistics {
                title: statistics.title

                numberOfDeals: statistics.numberOfDeals
                averageVolume: statistics.averageVolume
                minVolume: statistics.minVolume
                maxVolume: statistics.maxVolume

                numberOfBuyDeals: statistics.numberOfBuyDeals
                averageBuyVolume: statistics.averageBuyVolume
                minBuyVolume: statistics.minBuyVolume
                maxBuyVolume: statistics.maxBuyVolume

                numberOfSellDeals: statistics.numberOfSellDeals
                averageSellVolume: statistics.averageSellVolume
                minSellVolume: statistics.minSellVolume
                maxSellVolume: statistics.maxSellVolume
            }
            model: LongPeriodDealsStatisticsModel {
                id: longPeriodDealsStatisticsModel

                ticker: tickerSelector.currentText
                dateFrom: dateFromPicker.date
                dateTo: dateToPicker.date
            }
        }
    }

    ScrollView {
        id: scrollView
        width: 300
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Column {
            id: column
            width: 260
            anchors.left: parent.left
            anchors.leftMargin: 20

            SpacingRow {
                id: spacingRow3
            }

            Label {
                id: label
                text: qsTr("Ticker")
            }

            ComboBox {
                id: tickerSelector
                model: ["GAZP", "SBER"]
                currentIndex: 0
            }

            SpacingRow {
                id: spacingRow4
            }

            Label {
                id: label1
                text: qsTr("Today")
            }

            DatePicker {
                id: todayDatePicker
            }

            SpacingRow {
            }

            Label {
                text: qsTr("Date from")
                font.pointSize: 10
            }
            DatePicker {
                id: dateFromPicker
                date: new Date(2017, 8, 4)
            }
            SpacingRow {
            }

            Label {
                id: dateToLabel
                text: qsTr("Date to")
            }
            DatePicker {
                id: dateToPicker
                date: new Date(2017, 8, 10)
            }

            SpacingRow {
            }

            Button {
                id: updateButton
                text: qsTr("Update")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            SpacingRow {
                id: spacingRow
            }
        }
    }

    Rectangle {
        id: loadingRectangle
        color: "#80808080"
        visible: false
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator
            x: 70
            y: 64
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
