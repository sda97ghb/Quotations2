#ifndef REQUESTPARAMETERS_H
#define REQUESTPARAMETERS_H

#include <QString>

/// Interface for request parameters. Implemented by AlorRequestParameters and
/// FinamRequestParameters.
class RequestParameters
{
public:
    /// @return Request parameters in form of get request parameters.
    /// (param1=value1&param2=value2&...)
    virtual QString toGetRequestParameters() const = 0;
};

#endif // REQUESTPARAMETERS_H
