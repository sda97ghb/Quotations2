#include "FinamRequestParameters.h"

namespace finam
{

Ticker::operator QString() const
{
    return toHumanReadableString();
}

QString Ticker::toHumanReadableString() const
{
    switch (value())
    {
    case SBER: return "SBER";
    case GAZP: return "GAZP";

    default: return "UNKNOWN";
    }
}

QString Ticker::toEm() const
{
    switch (value())
    {
    case SBER: return "3";
    case GAZP: return "16842";

    default: return "";
    }
}

TimeFrame::operator QString() const
{
    switch (value())
    {
    case Ticks:       return "1";
    case Minute:      return "2";
    case Minute_x_5:  return "3";
    case Minute_x_10: return "4";
    case Minute_x_15: return "5";
    case Minute_x_30: return "6";
    case Hour:        return "7";
    case Day:         return "8";
    case Week:        return "9";
    case Month:       return "10";

    default: return "";
    }
}

FileFormat::operator QString() const
{
    switch (value())
    {
    case Txt: return ".txt";
    case Csv: return ".csv";

    default: return "";
    }
}

DateFormat::operator QString() const
{
    switch (value())
    {
    case YYYY_MM_DD:           return "1";
    case YY_MM_DD:             return "2";
    case DD_MM_YY:             return "3";
    case DD_slash_MM_slash_YY: return "4";
    case MM_slash_DD_slash_YY: return "5";

    default: return "";
    }
}

TimeFormat::operator QString() const
{
    switch (value())
    {
    case HH_MM_SS:             return "1";
    case HH_MM:                return "2";
    case HH_colon_MM_colon_SS: return "3";
    case HH_colon_MM:          return "4";

    default: return "";
    }
}

CandleTime::operator QString() const
{
    switch (value())
    {
    case Open:  return "0";
    case Close: return "1";

    default: return "";
    };
}

FieldSeparator::operator QString() const
{
    switch (value())
    {
    case Comma:     return "1";
    case Dot:       return "2";
    case Semicolon: return "3";
    case Tab:       return "4";
    case Space:     return "5";

    default: return "";
    }
}

DecimalSeparator::operator QString() const
{
    switch (value())
    {
    case None:        return "1";
    case Dot:         return "2";
    case Comma:       return "3";
    case Space:       return "4";
    case SingleQuote: return "5";

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
    case TICKER_PER_DATE_TIME_LAST_VOL:                return "6";
    case TICKER_DATE_TIME_LAST_VOL:                    return "7";
    case TICKER_DATE_TIME_LAST:                        return "8";
    case DATE_TIME_LAST_VOL:                           return "9";
    case DATE_TIME_LAST:                               return "10";
    case DATE_TIME_LAST_VOL_ID:                        return "11";
    case DATE_TIME_LAST_VOL_ID_OPER:                   return "12";

    default: return "";
    }
}

FinamRequestParameters FinamRequestParameters::forQuotations(Ticker ticker, QDate date)
{
    FinamRequestParameters params;
    params.setTicker(ticker);
    params.setMarket(1);
    params.setApply(0);
    params.setFrom(date);
    params.setTo(date);
    params.setTimeFrame(TimeFrame::Minute);
    params.setFileName(QString("%1_%2").arg(ticker.toHumanReadableString())
                       .arg(date.toString("yyyyMMdd")));
    params.setFileFormat(FileFormat::Txt);
    params.setDateFormat(DateFormat::YYYY_MM_DD);
    params.setTimeFormat(TimeFormat::HH_MM);
    params.setCandleTime(CandleTime::Open);
    params.setMoscowTime(true);
    params.setFieldSeparator(FieldSeparator::Comma);
    params.setDecimalSeparator(DecimalSeparator::None);
    params.setRecordFormat(RecordFormat::TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE);
    params.setAddHeader(false);
    params.setFillPeriods(false);
    return params;
}

FinamRequestParameters FinamRequestParameters::forDeals(Ticker ticker, QDate date)
{
    FinamRequestParameters params;
    params.setTicker(ticker);
    params.setMarket(1);
    params.setApply(0);
    params.setFrom(date);
    params.setTo(date);
    params.setTimeFrame(TimeFrame::Ticks);
    params.setFileName(QString("%1_%2").arg(ticker.toHumanReadableString())
                       .arg(date.toString("yyyyMMdd")));
    params.setFileFormat(FileFormat::Txt);
    params.setDateFormat(DateFormat::YYYY_MM_DD);
    params.setTimeFormat(TimeFormat::HH_MM_SS);
    params.setCandleTime(CandleTime::Open);
    params.setMoscowTime(true);
    params.setFieldSeparator(FieldSeparator::Comma);
    params.setDecimalSeparator(DecimalSeparator::None);
    params.setRecordFormat(RecordFormat::DATE_TIME_LAST_VOL_ID_OPER);
    params.setAddHeader(false);
    params.setFillPeriods(false);
    return params;
}

FinamRequestParameters::FinamRequestParameters() :
    m_ticker(Ticker::GAZP),
    m_market(1),
    m_apply(0),
    m_from(QDate(2017, 9, 1)),
    m_to(QDate(2017, 9, 1)),
    m_timeFrame(TimeFrame::Minute),
    m_fileName("doesnotmatter"),
    m_fileFormat(FileFormat::Txt),
    m_dateFormat(DateFormat::YYYY_MM_DD),
    m_timeFormat(TimeFormat::HH_MM_SS),
    m_candleTime(CandleTime::Open),
    m_moscowTime(true),
    m_fieldSeparator(FieldSeparator::Comma),
    m_decimalSeparator(DecimalSeparator::None),
    m_recordFormat(RecordFormat::DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL),
    m_addHeader(false),
    m_fillPeriods(false)
{
    // Designed as empty
}

QString FinamRequestParameters::toGetRequestParameters() const
{
    auto p = [](QString parameterName, QString parameterValue) -> QString
    {
        return parameterName + "=" + parameterValue + "&";
    };

    QString parameters =
           p("market",    QString::number(m_market)) +
           p("em",        m_ticker.toEm()) +
           p("code",      m_ticker.toString()) +
           p("apply",     QString::number(m_apply)) +
           p("df",        QString::number(m_from.day())) +
           p("mf",        QString::number(m_from.month() - 1)) +
           p("yf",        QString::number(m_from.year())) +
           p("from",      m_from.toString("dd.MM.yyyy")) +
           p("dt",        QString::number(m_to.day())) +
           p("mt",        QString::number(m_to.month() - 1)) +
           p("yt",        QString::number(m_to.year())) +
           p("to",        m_to.toString("dd.MM.yyyy")) +
           p("p",         m_timeFrame.toString()) +
           p("f",         m_fileName) +
           p("e",         m_fileFormat.toString()) +
           p("cn",        m_ticker.toString()) +
           p("dtf",       m_dateFormat.toString()) +
           p("tmf",       m_timeFormat.toString()) +
           p("MSOR",      m_candleTime.toString()) +
//           p("mstime",    m_moscowTime ? "1" : "0") +
           p("mstime",    m_moscowTime ? "on" : "off") +
           p("mstimever", "1") +
           p("sep",       m_fieldSeparator.toString()) +
           p("sep2",      m_decimalSeparator.toString()) +
           p("datf",      m_recordFormat.toString()) +
           p("at",        m_addHeader ? "1" : "0") +
           p("fsp",       m_fillPeriods ? "1" : "0");

    // QStringRef to remove last ampersand
    return QStringRef(&parameters, 0, parameters.size() - 1).toString();
}

int FinamRequestParameters::market() const
{
    return m_market;
}

void FinamRequestParameters::setMarket(int market)
{
    m_market = market;
}

int FinamRequestParameters::apply() const
{
    return m_apply;
}

void FinamRequestParameters::setApply(int apply)
{
    m_apply = apply;
}

QDate FinamRequestParameters::from() const
{
    return m_from;
}

void FinamRequestParameters::setFrom(const QDate& from)
{
    m_from = from;
}

QDate FinamRequestParameters::to() const
{
    return m_to;
}

void FinamRequestParameters::setTo(const QDate& to)
{
    m_to = to;
}

TimeFrame FinamRequestParameters::timeFrame() const
{
    return m_timeFrame;
}

void FinamRequestParameters::setTimeFrame(TimeFrame timeFrame)
{
    m_timeFrame = timeFrame;
}

QString FinamRequestParameters::fileName() const
{
    return m_fileName;
}

void FinamRequestParameters::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

FileFormat FinamRequestParameters::fileFormat() const
{
    return m_fileFormat;
}

void FinamRequestParameters::setFileFormat(FileFormat fileFormat)
{
    m_fileFormat = fileFormat;
}

DateFormat FinamRequestParameters::dateFormat() const
{
    return m_dateFormat;
}

void FinamRequestParameters::setDateFormat(DateFormat dateFormat)
{
    m_dateFormat = dateFormat;
}

TimeFormat FinamRequestParameters::timeFormat() const
{
    return m_timeFormat;
}

void FinamRequestParameters::setTimeFormat(TimeFormat timeFormat)
{
    m_timeFormat = timeFormat;
}

CandleTime FinamRequestParameters::candleTime() const
{
    return m_candleTime;
}

void FinamRequestParameters::setCandleTime(CandleTime candleTime)
{
    m_candleTime = candleTime;
}

bool FinamRequestParameters::moscowTime() const
{
    return m_moscowTime;
}

void FinamRequestParameters::setMoscowTime(bool moscowTime)
{
    m_moscowTime = moscowTime;
}

FieldSeparator FinamRequestParameters::fieldSeparator() const
{
    return m_fieldSeparator;
}

void FinamRequestParameters::setFieldSeparator(FieldSeparator fieldSeparator)
{
    m_fieldSeparator = fieldSeparator;
}

DecimalSeparator FinamRequestParameters::decimalSeparator() const
{
    return m_decimalSeparator;
}

void FinamRequestParameters::setDecimalSeparator(DecimalSeparator decimalSeparator)
{
    m_decimalSeparator = decimalSeparator;
}

RecordFormat FinamRequestParameters::recordFormat() const
{
    return m_recordFormat;
}

void FinamRequestParameters::setRecordFormat(RecordFormat recordFormat)
{
    m_recordFormat = recordFormat;
}

bool FinamRequestParameters::addHeader() const
{
    return m_addHeader;
}

void FinamRequestParameters::setAddHeader(bool addHeader)
{
    m_addHeader = addHeader;
}

bool FinamRequestParameters::fillPeriods() const
{
    return m_fillPeriods;
}

void FinamRequestParameters::setFillPeriods(bool fillPeriods)
{
    m_fillPeriods = fillPeriods;
}

Ticker FinamRequestParameters::ticker() const
{
    return m_ticker;
}

void FinamRequestParameters::setTicker(const Ticker& ticker)
{
    m_ticker = ticker;
}

} // namespace finam
