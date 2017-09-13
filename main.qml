import MyTypes 1.0
import Qt.labs.calendar 1.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.2

ApplicationWindow {
    id: main

    visible: true
    width: 1000
    height: 660
    title: "Quotations"

    Component.onCompleted: loadDataFromServer.execute()

    //---------------- Non-visual components ----------------//
    LoadDataFromServer {
        id: loadDataFromServer
    }

    Timer {
        interval: 60000
        running: true
        repeat: true
        onTriggered: loadDataFromServer.execute()
    }

    ChartDataSource {
        id: chartDataSource
        hourFrom: hourFrom.value
        minuteFrom: minuteFrom.value
        intervalLength: intervalLength.value
        onUpdated: chartDataSource.updateSeries(chartView.series(0))
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: chartDataSource.update()
    }

//    Timer {
//        interval: 1000
//        running: true
//        repeat: true
//        onTriggered: candlestickChartModel.updateData()
//    }

    //---------------- Visual components ----------------//
    ScrollView {
        id: controlPanel
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 260

        Column {
            anchors.fill: parent
            spacing: 10

            SpacingRow {
                height: 20
            }

            Text {
                text: "Date"
            }

            Row {
                spacing: 22

                Text {
                    text: "07.09.2017"
                    font.pointSize: 14
                }
                Button {
                   text: "Change"
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.verticalCenterOffset: -10
//                   width: 30
                   height: 30
                }
            }

            SpacingRow {
                height: 10
            }

            Text {
                text: "Hour"
            }

            SpinBox {
                id: hourFrom
                width: parent.width - 30
                from: 10
                to: 18
                value: 10
                editable: true
                onValueChanged: chartDataSource.update()
            }

            Text {
                verticalAlignment: Text.AlignBottom
                text: "Minute"
            }

            SpinBox {
                id: minuteFrom
                width: parent.width - 30
                from: 0
                to: hourFrom.value == 18 ? 49 : 59
                value: 0
                editable: true
                onValueChanged: chartDataSource.update()
            }

            Text {
                text: "Interval length"
            }

            SpinBox {
                id: intervalLength
                width: parent.width - 30
                from: 1
                to: 60
                value: 10
                editable: true
                onValueChanged: chartDataSource.update()
            }

            SpacingRow {
                height: 20
            }

            Row {
                spacing: 20

                Column {
                    spacing: 10
                    width: (parent.parent.width - 30) / 2
                    Text {
                        text: "Minimum"
                    }

                    Text {
                        font.pointSize: 14
                        text: chartDataSource.minValue
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
                        text: chartDataSource.maxValue
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
                width: parent.width - 30
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
                width: parent.width - 30
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
//            HCandlestickModelMapper {
//                model: CandlestickChartModel {
//                    id: candlestickChartModel
//                }
//                timestampColumn: 0
//                openColumn: 1
//                highColumn: 2
//                lowColumn: 3
//                closeColumn: 4
//                firstSetRow: 0
//                lastSetRow: candlestickChartModel.seriesSize + 1
//            }

//            name: candlestickChartModel.seriesName
            name: "TODO: add series name"
            increasingColor: "green"
            decreasingColor: "red"

            axisX: DateTimeAxis {
                min: chartDataSource.from
                max: chartDataSource.to
                format: "yyyy.MM.dd hh.mm"
//                min: candlestickChartModel.from
//                max: candlestickChartModel.to
//                format: "hh:mm"
            }

            axisY: ValueAxis {
                min: customMinMax.checked ? customMin.value : chartDataSource.minValue
                max: customMinMax.checked ? customMax.value : chartDataSource.maxValue
//                min: 0
//                max: 40
            }

//            CandlestickSet { timestamp: 1435708800000; open: 183.47; high: 184.35; low: 183.47; close: 184.21 }
//            CandlestickSet { timestamp: 1435795200000; open: 184.16; high: 184.4;  low: 184.08; close: 184.29 }
//            CandlestickSet { timestamp: 1436140800000; open: 184.29; high: 184.29; low: 183.74; close: 184.03 }
//            CandlestickSet { timestamp: 1436227200000; open: 184.05; high: 184.05; low: 183.91; close: 184 }
//            CandlestickSet { timestamp: 1436313600000; open: 184;    high: 184;    low: 183.74; close: 183.9 }
        }
    }
}
