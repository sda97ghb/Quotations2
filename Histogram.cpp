#include "Histogram.h"

QList<quint64> histogram::calculate(QList<quint64> data, int numberOfSteps)
{
    if (numberOfSteps < 1)
        return QList<quint64>();

    if (numberOfSteps == 1)
        return QList<quint64>() << data.size();

    QList<quint64> result;
    for (int i = 0; i < numberOfSteps; ++ i)
        result.append(1);

    if (data.isEmpty())
        return result;

    quint64 minValue = *(std::min_element(data.begin(), data.end()));
    quint64 maxValue = *(std::max_element(data.begin(), data.end()));

    for (quint64 value : data)
    {
        int index = (value - minValue) * numberOfSteps / (maxValue - minValue);
        if (index == numberOfSteps)
            -- index;
        ++ result[index];
    }

    return result;
}
