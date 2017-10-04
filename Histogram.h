#ifndef HISTOGRAMDATACALCULATOR_H
#define HISTOGRAMDATACALCULATOR_H

#include <QList>

namespace histogram
{
    /// @arg interval Interval in percents.
    QList<quint64> calculate(QList<quint64> data, int numberOfSteps);
}

#endif // HISTOGRAMDATACALCULATOR_H
