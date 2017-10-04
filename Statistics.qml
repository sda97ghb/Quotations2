import QtQuick 2.0

import QtQuick.Controls 2.2

Item {
    property alias title: titleLabel.text

    property alias numberOfDeals: numberOfDealsLabel.text
    property alias averageVolume: averageVolumeLabel.text
    property alias minVolume: minVolumeLabel.text
    property alias maxVolume: maxVolumeLabel.text

    property alias numberOfBuyDeals: numberOfBuyDealsLabel.text
    property alias averageBuyVolume: buyAverageVolumeLabel.text
    property alias minBuyVolume: buyMinVolumeLabel.text
    property alias maxBuyVolume: buyMaxVolumeLabel.text

    property alias numberOfSellDeals: numberOfSellDealsLabel.text
    property alias averageSellVolume: sellAverageVolumeLabel.text
    property alias minSellVolume: sellMinVolumeLabel.text
    property alias maxSellVolume: sellMaxVolumeLabel.text

    width: 150
    height: 470

    Column {
        id: column
        anchors.fill: parent

        Label {
            id: titleLabel
            text: qsTr("Title")
            font.bold: true
            font.pointSize: 16
        }

        SpacingRow {
            id: spacingRow1
        }

        Label {
            text: qsTr("Number of deals")
        }

        Label {
            id: numberOfDealsLabel
            text: "0"
            font.pointSize: 12
        }

        SpacingRow {
            id: spacingRow4
        }

        Label {
            text: qsTr("Average volume")
        }

        Label {
            id: averageVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Min volume")
        }

        Label {
            id: minVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Max volume")
        }

        Label {
            id: maxVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        SpacingRow {
            id: spacingRow2
        }

        Label {
            text: qsTr("Buy")
            font.pointSize: 14
        }

        SpacingRow {
            height: 6
        }

        Label {
            text: qsTr("Number of deals")
        }

        Label {
            id: numberOfBuyDealsLabel
            text: "0"
            font.pointSize: 12
        }

        SpacingRow {
        }

        Label {
            text: qsTr("Average volume")
        }

        Label {
            id: buyAverageVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Min volume")
        }

        Label {
            id: buyMinVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Max volume")
        }

        Label {
            id: buyMaxVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        SpacingRow {
            id: spacingRow3
        }

        Label {
            text: qsTr("Sell")
            font.pointSize: 14
        }

        SpacingRow {
            height: 6
        }

        Label {
            text: qsTr("Number of deals")
        }

        Label {
            id: numberOfSellDealsLabel
            text: "0"
            font.pointSize: 12
        }

        SpacingRow {
        }

        Label {
            text: qsTr("Average volume")
        }

        Label {
            id: sellAverageVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Min volume")
        }

        Label {
            id: sellMinVolumeLabel
            text: "0"
            font.pointSize: 12
        }

        Label {
            text: qsTr("Max volume")
        }

        Label {
            id: sellMaxVolumeLabel
            text: "0"
            font.pointSize: 12
        }
    }

}
