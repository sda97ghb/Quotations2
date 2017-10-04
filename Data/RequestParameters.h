#ifndef REQUESTPARAMETERS_H
#define REQUESTPARAMETERS_H

#include <QString>

class RequestParameters
{
public:
    virtual QString toGetRequestParameters() const = 0;
};

#endif // REQUESTPARAMETERS_H
