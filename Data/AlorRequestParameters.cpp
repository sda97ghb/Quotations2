#include "AlorRequestParameters.h"

namespace alor
{

MarketPlace::operator QString() const
{
    switch (value())
    {
    case MICEX:    return "MICEX";
    case CURRENCY: return "CURRENCY";
    case FORTSF:   return "FORTSF";
    case FORTSO:   return "FORTSO";
    case INDICES:  return "INDICES";

    default: return "";
    }
}

TimeFrame::operator QString() const
{
    switch (value())
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

FileFormat::operator QString() const
{
    switch (value())
    {
    case Txt: return "1";
    case Csv: return "2";

    default: return "";
    }
}

RecordFormat::operator QString() const
{
    switch (value())
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

DateFormat::operator QString() const
{
    switch (value())
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

TimeFormat::operator QString() const
{
    switch (value())
    {
    case HH_MM_SS:             return "1";
    case HH_colon_MM_colon_SS: return "2";
    case HH_MM:                return "3";
    case HH_colon_MM:          return "4";

    default: return "";
    }
}

FieldSeparator::operator QString() const
{
    switch (value())
    {
    case Semicolon: return "1";
    case Comma:     return "2";
    case Dot:       return "3";
    case Space:     return "4";
    case Tab:       return "5";

    default: return "";
    }
}

DecimalSeparator::operator QString() const
{
    switch (value())
    {
    case Dot:         return "1";
    case Comma:       return "2";
    case Space:       return "3";
    case SingleQuote: return "4";
    case None:        return "5";

    default: return "";
    }
}

AlorRequestParameters AlorRequestParameters::forQuotations(QString ticker, QDate date)
{
    AlorRequestParameters requestParameters;
    requestParameters.setMarketPlace(MarketPlace::MICEX);
    requestParameters.setTicker(ticker);
    requestParameters.setTimeFrame(TimeFrame::Minute);
    requestParameters.setFrom(date);
    requestParameters.setTo(date);
    requestParameters.setFileName("");
    requestParameters.setFileFormat(FileFormat::Txt);
    requestParameters.setRecordFormat(RecordFormat::TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE);
    requestParameters.setDateFormat(DateFormat::YYYY_MM_DD);
    requestParameters.setTimeFormat(TimeFormat::HH_MM);
    requestParameters.setFieldSeparator(FieldSeparator::Comma);
    requestParameters.setDecimalSeparator(DecimalSeparator::Dot);
    requestParameters.setAddHeader(false);
    return requestParameters;
}

AlorRequestParameters::AlorRequestParameters() :
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

QString AlorRequestParameters::toGetRequestParameters() const
{
    return "board=" + marketPlace().toString() + "&" +
           "ticker=" + ticker() + "&" +
           "period=" + timeFrame().toString() + "&" +
           "from=" + from().toString("dd.MM.yyyy") + "&" +
           "to=" + to().toString("dd.MM.yyyy") + "&" +
           "file_name=" + fileName() + "&" +
           "formatFiles=" + fileFormat().toString() + "&" +
           "format=" + recordFormat().toString() + "&" +
           "formatDate=" + dateFormat().toString() + "&" +
           "formatTime=" + timeFormat().toString() + "&" +
           "fieldSeparator=" + fieldSeparator().toString() + "&" +
           "formatSeparatorDischarge=" + decimalSeparator().toString() + "&" +
           "addTopic=" + (addHeader() ? "on" : "off");
}

MarketPlace AlorRequestParameters::marketPlace() const
{
    return m_marketPlace;
}

QString AlorRequestParameters::ticker() const
{
    return m_ticker;
}

TimeFrame AlorRequestParameters::timeFrame() const
{
    return m_timeFrame;
}

QDate AlorRequestParameters::from() const
{
    return m_from;
}

QDate AlorRequestParameters::to() const
{
    return m_to;
}

QString AlorRequestParameters::fileName() const
{
    return m_fileName;
}

FileFormat AlorRequestParameters::fileFormat() const
{
    return m_fileFormat;
}

RecordFormat AlorRequestParameters::recordFormat() const
{
    return m_recordFormat;
}

DateFormat AlorRequestParameters::dateFormat() const
{
    return m_dateFormat;
}

TimeFormat AlorRequestParameters::timeFormat() const
{
    return m_timeFormat;
}

FieldSeparator AlorRequestParameters::fieldSeparator() const
{
    return m_fieldSeparator;
}

DecimalSeparator AlorRequestParameters::decimalSeparator() const
{
    return m_decimalSeparator;
}

bool AlorRequestParameters::addHeader() const
{
    return m_addHeader;
}

void AlorRequestParameters::setMarketPlace(MarketPlace marketPlace)
{
    m_marketPlace = marketPlace;
}

void AlorRequestParameters::setTicker(const QString& ticker)
{
    m_ticker = ticker;
}

void AlorRequestParameters::setTimeFrame(TimeFrame timeFrame)
{
    m_timeFrame = timeFrame;
}

void AlorRequestParameters::setFrom(const QDate& from)

{
    m_from = from;
}

void AlorRequestParameters::setTo(const QDate& to)
{
    m_to = to;
}

void AlorRequestParameters::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void AlorRequestParameters::setFileFormat(FileFormat fileFormat)
{
    m_fileFormat = fileFormat;
}

void AlorRequestParameters::setRecordFormat(RecordFormat recordFormat)
{
    m_recordFormat = recordFormat;
}

void AlorRequestParameters::setDateFormat(DateFormat dateFormat)
{
    m_dateFormat = dateFormat;
}

void AlorRequestParameters::setTimeFormat(TimeFormat timeFormat)
{
    m_timeFormat = timeFormat;
}

void AlorRequestParameters::setFieldSeparator(FieldSeparator fieldSeparator)
{
    m_fieldSeparator = fieldSeparator;
}

void AlorRequestParameters::setDecimalSeparator(DecimalSeparator decimalSeparator)
{
    m_decimalSeparator = decimalSeparator;
}

void AlorRequestParameters::setAddHeader(bool addHeader)
{
    m_addHeader = addHeader;
}

} // namespace alor
