#include "RequestParameters.h"

QString MarketPlace::toString(MarketPlace::Value value)
{
    switch (value)
    {
    case MICEX:    return "MICEX";
    case CURRENCY: return "CURRENCY";
    case FORTSF:   return "FORTSF";
    case FORTSO:   return "FORTSO";
    case INDICES:  return "INDICES";

    default: return "";
    }
}

QString TimeFrame::toString(TimeFrame::Value value)
{
    switch (value)
    {
    case Minute:      return "1";
    case Minute_x_5:  return "5";
    case Minute_x_10: return "10";
    case Minute_x_15: return "15";
    case Minute_x_20: return "20";
    case Minute_x_30: return "30";
    case Hour:        return "60";
    case Day:         return "1440";

    default: return "";
    }
}

QString FileFormat::toString(FileFormat::Value value)
{
    switch (value)
    {
    case Txt: return "1";
    case Csv: return "2";

    default: return "";
    }
}

QString RecordFormat::toString(RecordFormat::Value value)
{
    switch (value)
    {
    case TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL: return "1";
    case TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE:     return "2";
    case TICKER_PER_DATE_TIME_CLOSE_VOL:               return "3";
    case TICKER_PER_DATE_TIME_CLOSE:                   return "4";
    case DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL:            return "5";
    case TICKER_PER_DATE_TIME_HIGH_LOW_CLOSE_VOL:      return "6";

    default: return "";
    }
}

QString DateFormat::toString(DateFormat::Value value)
{
    switch (value)
    {
    case YYYY_MM_DD:             return "1";
    case YY_MM_DD:               return "2";
    case DD_MM_YY:               return "3";
    case DD_slash_MM_slash_YY:   return "4";
    case MM_slash_DD_slash_YY:   return "5";
    case YYYY_minus_MM_minus_DD: return "6";
    case YYYY_dot_MM_dot_DD:     return "7";
    case DD_minus_MM_minus_YYYY: return "8";
    case DD_dot_MM_dot_YYYY:     return "9";

    default: return "";
    }
}

QString TimeFormat::toString(TimeFormat::Value value)
{
    switch (value)
    {
    case HH_MM_SS:             return "1";
    case HH_colon_MM_colon_SS: return "2";
    case HH_MM:                return "3";
    case HH_colon_MM:          return "4";

    default: return "";
    }
}

QString FieldSeparator::toString(FieldSeparator::Value value)
{
    switch (value)
    {
    case Semicolon: return "1";
    case Comma:     return "2";
    case Dot:       return "3";
    case Space:     return "4";
    case Tab:       return "5";

    default: return "";
    }
}

QString DecimalSeparator::toString(DecimalSeparator::Value value)
{
    switch (value)
    {
    case Dot:         return "1";
    case Comma:       return "2";
    case Space:       return "3";
    case SingleQuote: return "4";
    case None:        return "5";

    default: return "";
    }
}

RequestParameters::RequestParameters() :
    m_marketPlace(MarketPlace::MICEX),
    m_ticker(""),
    m_timeFrame(TimeFrame::Minute),
    m_from(QDate(2017, 9, 1)),
    m_to(QDate(2017, 9, 1)),
    m_fileName(""),
    m_fileFormat(FileFormat::Txt),
    m_recordFormat(RecordFormat::TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL),
    m_dateFormat(DateFormat::YYYY_MM_DD),
    m_timeFormat(TimeFormat::HH_MM_SS),
    m_fieldSeparator(FieldSeparator::Comma),
    m_decimalSeparator(DecimalSeparator::Dot),
    m_addHeader(false)
{
    // Designed as empty
}

QString RequestParameters::toGetRequestParameters()
{
    return "board=" + MarketPlace::toString(marketPlace()) + "&" +
           "ticker=" + ticker() + "&" +
           "period=" + TimeFrame::toString(timeFrame()) + "&" +
           "from=" + from().toString("dd.MM.yyyy") + "&" +
           "to=" + to().toString("dd.MM.yyyy") + "&" +
           "file_name=" + fileName() + "&" +
           "formatFiles=" + FileFormat::toString(fileFormat()) + "&" +
           "format=" + RecordFormat::toString(recordFormat()) + "&" +
           "formatDate=" + DateFormat::toString(dateFormat()) + "&" +
           "formatTime=" + TimeFormat::toString(timeFormat()) + "&" +
           "fieldSeparator=" + FieldSeparator::toString(fieldSeparator()) + "&" +
           "formatSeparatorDischarge=" + DecimalSeparator::toString(decimalSeparator()) + "&" +
           "addTopic=" + (addHeader() ? "on" : "off");
}

MarketPlace::Value RequestParameters::marketPlace() const
{
    return m_marketPlace;
}

QString RequestParameters::ticker() const
{
    return m_ticker;
}

TimeFrame::Value RequestParameters::timeFrame() const
{
    return m_timeFrame;
}

QDate RequestParameters::from() const
{
    return m_from;
}

QDate RequestParameters::to() const
{
    return m_to;
}

QString RequestParameters::fileName() const
{
    return m_fileName;
}

FileFormat::Value RequestParameters::fileFormat() const
{
    return m_fileFormat;
}

RecordFormat::Value RequestParameters::recordFormat() const
{
    return m_recordFormat;
}

DateFormat::Value RequestParameters::dateFormat() const
{
    return m_dateFormat;
}

TimeFormat::Value RequestParameters::timeFormat() const
{
    return m_timeFormat;
}

DecimalSeparator::Value RequestParameters::decimalSeparator() const
{
    return m_decimalSeparator;
}

bool RequestParameters::addHeader() const
{
    return m_addHeader;
}

void RequestParameters::setMarketPlace(const MarketPlace::Value& marketPlace)
{
    m_marketPlace = marketPlace;
}

void RequestParameters::setTicker(const QString& ticker)
{
    m_ticker = ticker;
}

void RequestParameters::setTimeFrame(const TimeFrame::Value& timeFrame)
{
    m_timeFrame = timeFrame;
}

void RequestParameters::setFrom(const QDate& from)

{
    m_from = from;
}

void RequestParameters::setTo(const QDate& to)
{
    m_to = to;
}

void RequestParameters::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void RequestParameters::setFileFormat(const FileFormat::Value& fileFormat)
{
    m_fileFormat = fileFormat;
}

void RequestParameters::setRecordFormat(const RecordFormat::Value& recordFormat)
{
    m_recordFormat = recordFormat;
}

void RequestParameters::setDateFormat(const DateFormat::Value& dateFormat)
{
    m_dateFormat = dateFormat;
}

void RequestParameters::setTimeFormat(const TimeFormat::Value& timeFormat)
{
    m_timeFormat = timeFormat;
}

FieldSeparator::Value RequestParameters::fieldSeparator() const
{
    return m_fieldSeparator;
}

void RequestParameters::setFieldSeparator(const FieldSeparator::Value& fieldSeparator)
{
    m_fieldSeparator = fieldSeparator;
}

void RequestParameters::setDecimalSeparator(const DecimalSeparator::Value& decimalSeparator)
{
    m_decimalSeparator = decimalSeparator;
}

void RequestParameters::setAddHeader(bool addHeader)
{
    m_addHeader = addHeader;
}
