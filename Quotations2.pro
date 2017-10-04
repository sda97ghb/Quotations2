QT += charts qml quick

CONFIG += c++14

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    BetterCpp.h \
    \
    Data/RequestParameters.h \
    Data/AlorRequestParameters.h \
    Data/FinamRequestParameters.h \
    Data/DataLoader.h \
    Data/LoadableData.h \
    Data/LoadableDeals.h \
    Data/LoadableQuotations.h \
    Data/LongPeriodDealsLoader.h \
    \
    Entities/Deal.h \
    Entities/Deals.h \
    Entities/Quotation.h \
    Entities/Quotations.h \
    \
    Presenters/CandlestickChartModel.h \
    Presenters/DealsHistogramModel.h \
    Presenters/LongPeriodDealsStatisticsModel.h \
    Presenters/StatisticsDTO.h \
    Presenters/TodayDealsStatisticsModel.h \
    \
    Global.h \
    Histogram.h \
    IntRange.h

SOURCES += \
    main.cpp \
    \
    Data/AlorRequestParameters.cpp \
    Data/FinamRequestParameters.cpp \
    Data/DataLoader.cpp \
    Data/LoadableData.cpp \
    Data/LoadableQuotations.cpp \
    Data/LoadableDeals.cpp \
    Data/LongPeriodDealsLoader.cpp \
    \
    Entities/Deal.cpp \
    Entities/Deals.cpp \
    Entities/Quotation.cpp \
    Entities/Quotations.cpp \
    \
    Presenters/CandlestickChartModel.cpp \
    Presenters/DealsHistogramModel.cpp \
    Presenters/LongPeriodDealsStatisticsModel.cpp \
    Presenters/StatisticsDTO.cpp \
    Presenters/TodayDealsStatisticsModel.cpp \
    \
    Global.cpp \
    Histogram.cpp \
    IntRange.cpp

RESOURCES += qml.qrc
