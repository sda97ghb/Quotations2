#include "Histogram.h"
#include "LongPeriodDealsLoader.h"

#include "Data/DataLoader.h"
#include "Data/LoadableDeals.h"
#include "Data/LoadableQuotations.h"

#include "Presenters/CandlestickChartModel.h"
#include "Presenters/DealsHistogramModel.h"
#include "Presenters/LongPeriodDealsStatisticsModel.h"
#include "Presenters/TodayDealsStatisticsModel.h"

#include <QtWidgets/QApplication>

//#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing,
    // therefore QApplication must be used.
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

//    // For single day
//    DataLoader dataLoader;
//    LoadableDeals loadableDeals;
//    loadableDeals.setTicker("GAZP");
//    loadableDeals.setDate(QDate(2017, 8, 1));
//    QObject::connect(&loadableDeals, &LoadableDeals::updated, [&loadableDeals]()
//    {
//        Deals deals = loadableDeals.toDeals();
//        qDebug() << "loaded deals";
//        qDebug() << "There are " << deals.size() << " deals available.";
//        qDebug() << "Min volume" << deals.minVolume();
//        qDebug() << "Max volume" << deals.maxVolume();
//        qDebug() << "Average volume" << deals.averageVolume();
//        qDebug() << "Average buy volume" << deals.filterBuy().averageVolume();
//        qDebug() << "Average sell volume" << deals.filterSell().averageVolume();
//        qDebug() << "Total buy volume" << deals.filterBuy().totalVolume();
//        qDebug() << "Total sell volume" << deals.filterSell().totalVolume();
//        qDebug() << histogram::calculate(deals.filterBuy().toListOfVolumes(), 100);
//        qDebug() << histogram::calculate(deals.filterSell().toListOfVolumes(), 100);
////        for (Deal deal : deals.toList())
////            qDebug() << deal;
//    });
//    dataLoader.load(loadableDeals);

//    // For long period
//    LongPeriodDealsLoader longPeriodDealsLoader("SBER", QDate(2017, 8, 1),
//                                                QDate(2017, 8, 2));
//    QObject::connect(&longPeriodDealsLoader, &LongPeriodDealsLoader::allDaysLoaded, [&]()
//    {
//        Deals allDealsInInterval = longPeriodDealsLoader.allDeals();
//        QHash<int, Deals> splittedByDayOfWeek = allDealsInInterval.splitByDayOfWeek();
//        for (QHash<int, Deals>::iterator iter = splittedByDayOfWeek.begin();
//             iter != splittedByDayOfWeek.end(); ++ iter)
//        {
//            int dayOfWeek = iter.key();
//            Deals deals = iter.value();
//
//            qInfo() << "Day of week" << dayOfWeek;
//
//            qInfo() << "Average volume" << deals.averageVolume();
//            qInfo() << "Average buy volume" << deals.filterBuy().averageVolume();
//            qInfo() << "Average sell volume" << deals.filterSell().averageVolume();
//
//            qInfo() << "Min volume" << deals.minVolume();
//            qInfo() << "Min buy volume" << deals.filterBuy().minVolume();
//            qInfo() << "Min sell volume" << deals.filterSell().minVolume();
//
//            qInfo() << "Max volume" << deals.maxVolume();
//            qInfo() << "Max buy volume" << deals.filterBuy().maxVolume();
//            qInfo() << "Max sell volume" << deals.filterSell().maxVolume();
//
//            QHash<QDate, Deals> splittedByDate = deals.splitByDate();
//
//            int totalNumberOfDeals = 0;
//            for (Deals dealsInSomeDay : splittedByDate)
//                totalNumberOfDeals += dealsInSomeDay.size();
//
//            int averageNumberOfDeals = 0;
//            unless (splittedByDate.isEmpty())
//                averageNumberOfDeals = totalNumberOfDeals / splittedByDate.size();
//
//            qInfo() << "Average number of deals" << averageNumberOfDeals;
//        }
//    });

    qmlRegisterType<CandlestickChartModel>("MyTypes", 1, 0, "CandlestickChartModel");
    qmlRegisterType<DealsHistogramModel>("MyTypes", 1, 0, "DealsHistogramModel");
    qmlRegisterType<LongPeriodDealsStatisticsModel>("MyTypes", 1, 0, "LongPeriodDealsStatisticsModel");
    qmlRegisterType<TodayDealsStatisticsModel>("MyTypes", 1, 0, "TodayDealsStatisticsModel");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
