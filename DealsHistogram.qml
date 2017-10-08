import MyTypes 1.0
//import Qt.labs.calendar 1.0
import QtQuick 2.8
import QtQuick.Controls 2.2
import QtCharts 2.2

Item {
    width: 1280
    height: 720

    Column {
        id: rightPanel

        width: 260
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 20

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Update"
            onClicked: dealsHistogramModel.reload()
        }

        Row {
            width: parent.width
            Column {
                width: parent.width / 2
                spacing: 10

                Label {
                    text: "Buy min volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.buyMinVolume
                }

                Label {
                    text: "Buy max volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.buyMaxVolume
                }

                Label {
                    text: "Buy average volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.buyAverageVolume
                }
            }

            Column {
                width: parent.width / 2
                spacing: 10
                Label {
                    text: "Sell min volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.sellMinVolume
                }

                Label {
                    text: "Sell max volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.sellMaxVolume
                }

                Label {
                    text: "Sell average volume"
                }

                Label {
                    font.pointSize: 14
                    text: dealsHistogramModel.sellAverageVolume
                }
            }
        }

        Column {
            width: parent.width
            spacing: 10
            SpacingRow {
                height: 10
            }

            Label {
                text: "From"
            }

            SpinBox {
                id: volumeFrom
                width: parent.width
            }

            SpacingRow {
                height: 10
            }

            Label {
                text: "To"
            }

            SpinBox {
                id: volumeTo
                width: parent.width
            }

            SpacingRow {
                height: 10
            }

            Label {
                text: "Number of intervals"
            }

            SpinBox {
                id: numberOfIntervals
                width: parent.width
                from: 1
                to: 100
                value: 20
            }

            SpacingRow {
                height: 10
            }

            CheckBox {
                id: enableLogYAxis
                text: "Log y axis"
            }
        }
    }

    ChartView {
        id: chartView
        anchors.left: parent.left
        anchors.right: rightPanel.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        antialiasing: true
        theme: ChartView.ChartThemeLight

        BarSeries {
            labelsVisible: true
            labelsPosition: AbstractBarSeries.LabelsInsideBase
            HBarModelMapper {
                model: DealsHistogramModel {
                    id: dealsHistogramModel
                    numberOfIntervals: numberOfIntervals.value
                    volumeFrom: volumeFrom.value
                    volumeTo: volumeTo.value
//                    Component.onCompleted: reload()
                }
                firstBarSetRow: 0
                lastBarSetRow: 1
                firstColumn: 0
            }
            axisX: BarCategoryAxis {
                categories: {
                    var arr = new Array
                    for (var i = 0; i < numberOfIntervals.value; ++ i)
                    {
                        var range = dealsHistogramModel.maxVolume - dealsHistogramModel.minVolume
                        var value = range * (i + 0.5) / numberOfIntervals.value
                        value += dealsHistogramModel.minVolume
                        arr.push(Math.floor(value))
                    }
                    return arr
                }
            }
            axisY: enableLogYAxis.checked ? logValueYAxis : valueYAxis
            LogValueAxis {
                id: logValueYAxis
                base: 10
                min: 0
                max: Math.pow(10, Math.ceil(Math.log(dealsHistogramModel.maxValue) / Math.log(10)))
            }
            ValueAxis {
                id: valueYAxis
                min: 0
                max: dealsHistogramModel.maxValue
            }
        }
    }
}
