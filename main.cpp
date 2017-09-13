#include "CandlestickChartModel.h"
#include "ChartDataSource.h"
#include "LoadDataFromServer.h"

#include <QtWidgets/QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing,
    // therefore QApplication must be used.
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterType<CandlestickChartModel>("MyTypes", 1, 0, "CandlestickChartModel");
    qmlRegisterType<ChartDataSource>("MyTypes", 1, 0, "ChartDataSource");
    qmlRegisterType<LoadDataFromServer>("MyTypes", 1, 0, "LoadDataFromServer");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
