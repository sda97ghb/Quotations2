import MyTypes 1.0
import QtQuick 2.8
import QtQuick.Controls 2.2
import QtCharts 2.2

Item {
    width: 1280
    height: 720

//    Component.onCompleted: candlestickChartModel.loadData()

    //---------------- Non-visual components ----------------//
//    Timer {
//        interval: 60000
//        running: true
//        repeat: true
//        onTriggered: loadDataFromFinam.execute(tickerEdit.currentText, datePicker.date)
//    }

    //---------------- Visual components ----------------//
    ScrollView {
        id: controlPanel
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 30
        width: 255

        Column {
            anchors.fill: parent
            spacing: 10

            SpacingRow {
                height: 20
            }

            ComboBox {
                id: tickerEdit
                model: ["SBER", "GAZP"]
                currentIndex: 0
            }

            DatePicker {
                id: datePicker
                width: 245
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Update"
                onClicked: candlestickChartModel.loadData()
            }

            SpacingRow {
                height: 20
            }

            Text {
                text: "Hour"
            }

            SpinBox {
                id: hourFrom
                width: parent.width
                from: 10
                to: 18
                value: 10
                editable: true
            }

            Text {
                verticalAlignment: Text.AlignBottom
                text: "Minute"
            }

            SpinBox {
                id: minuteFrom
                width: parent.width
                from: 0
                to: hourFrom.value == 18 ? 49 : 59
                value: 0
                editable: true
            }

            Text {
                text: "Interval length"
            }

            SpinBox {
                id: intervalLength
                width: parent.width
                from: 1
                to: 60
                value: 10
                editable: true
            }

            SpacingRow {
                height: 20
            }

            Row {
                spacing: 20

                Column {
                    spacing: 10
                    width: (parent.parent.width - 10) / 2
                    Text {
                        text: "Minimum"
                    }

                    Text {
                        font.pointSize: 14
                        text: candlestickChartModel.minValue
                    }
                }

                Column {
                    spacing: 10
                    width: (parent.parent.width - 30) / 2
                    Text {
                        text: "Maximum"
                    }

                    Text {
                        font.pointSize: 14
                        text: candlestickChartModel.maxValue
                    }
                }
            }

            SpacingRow {
                height: 10
            }

            CheckBox {
                id: customMinMax
                text: "Fixed chart min and max"
            }

            Text {
                text: "Chart maximum"
            }

            SpinBox {
                id: customMax
                width: parent.width
                from: 1
                to: 200
                value: 190
                editable: true
            }

            Text {
                text: "Chart minimum"
            }

            SpinBox {
                id: customMin
                width: parent.width
                from: 0
                to: 199
                value: 180
                editable: true
            }

            SpacingRow {
                height: 20
            }
        }
    }

    ChartView {
        id: chartView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: controlPanel.left
        anchors.left: parent.left
        antialiasing: true
        theme: ChartView.ChartThemeLight

        CandlestickSeries {
            HCandlestickModelMapper {
                model: CandlestickChartModel {
                    id: candlestickChartModel
                    ticker: tickerEdit.currentText
                    date: datePicker.date
                    hourFrom: hourFrom.value
                    minuteFrom: minuteFrom.value
                    intervalLength: intervalLength.value
                }
                timestampColumn: 0
                openColumn: 1
                highColumn: 2
                lowColumn: 3
                closeColumn: 4
                firstSetRow: 0
                lastSetRow: candlestickChartModel.seriesSize + 1
            }

            name: candlestickChartModel.seriesName

            increasingColor: "green"
            decreasingColor: "red"

            axisX: DateTimeAxis {
                min: candlestickChartModel.seriesFrom
                max: candlestickChartModel.seriesTo
                format: "hh:mm:ss"
                tickCount: 2 * candlestickChartModel.seriesSize + 1
                labelsAngle: -90
            }

            axisY: ValueAxis {
                min: customMinMax.checked ? customMin.value : candlestickChartModel.minValue
                max: customMinMax.checked ? customMax.value : candlestickChartModel.maxValue
            }
        }
    }
}
