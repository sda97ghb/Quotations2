import QtQuick 2.4

LongPeriodStatisticsForm {
    updateButton.onClicked: {
        loadingRectangle.visible = true
        longPeriodDealsStatisticsModel.updateData()
        todayDealsStatisticsModel.updateData()
    }
    longPeriodDealsStatisticsModel.onModelReset: {
        loadingRectangle.visible = false
    }
}
