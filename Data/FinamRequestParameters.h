#ifndef FINAMREQUESTPARAMETERS_H
#define FINAMREQUESTPARAMETERS_H

#include "BetterCpp.h"
#include "RequestParameters.h"

#include <QDate>

namespace finam
{

class Ticker
{
    BETTER_ENUM
public:
    enum
    {
        SBER,
        GAZP
    };

    BETTER_ENUM_SHORT_INIT(Ticker)

    operator QString() const;
    QString toString() const { return QString(*this); }
    QString toHumanReadableString() const;
};

class TimeFrame
{
    BETTER_ENUM
public:
    enum
    {
        Ticks,
        Minute,
        Minute_x_5,
        Minute_x_10,
        Minute_x_15,
        Minute_x_30,
        Hour,
        Day,
        Week,
        Month
    };

    BETTER_ENUM_SHORT_INIT(TimeFrame)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class FileFormat
{
    BETTER_ENUM
public:
    enum
    {
        Txt,
        Csv
    };

    BETTER_ENUM_SHORT_INIT(FileFormat)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class DateFormat
{
    BETTER_ENUM
public:
    enum
    {
        YYYY_MM_DD,             ///< ГГГГММДД
        YY_MM_DD,               ///< ГГММДД
        DD_MM_YY,               ///< ДДММГГ
        DD_slash_MM_slash_YY,   ///< ДД/ММ/ГГ
        MM_slash_DD_slash_YY,   ///< ММ/ДД/ГГ
    };

    BETTER_ENUM_SHORT_INIT(DateFormat)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class TimeFormat
{
    BETTER_ENUM
public:
    enum
    {
        HH_MM_SS,             ///< ЧЧММСС
        HH_MM,                ///< ЧЧММ
        HH_colon_MM_colon_SS, ///< ЧЧ:ММ:СС
        HH_colon_MM           ///< ЧЧ:ММ
    };

    BETTER_ENUM_SHORT_INIT(TimeFormat)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class CandleTime
{
    BETTER_ENUM
public:
    enum
    {
        Open,
        Close
    };

    BETTER_ENUM_SHORT_INIT(CandleTime)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class FieldSeparator
{
    BETTER_ENUM
public:
    enum
    {
        Comma,
        Dot,
        Semicolon,
        Tab,
        Space
    };

    BETTER_ENUM_SHORT_INIT(FieldSeparator)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

/// @warning It doesn't separate integer and fractional parst of numbers.
/// DecimalSeparator::SingleQuote => 10'000'000.123
class DecimalSeparator
{
    BETTER_ENUM
public:
    enum
    {
        None,
        Dot,
        Comma,
        Space,
        SingleQuote
    };

    BETTER_ENUM_SHORT_INIT(DecimalSeparator)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class RecordFormat
{
    BETTER_ENUM
public:
    enum
    {
        TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL,
        TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE,
        TICKER_PER_DATE_TIME_CLOSE_VOL,
        TICKER_PER_DATE_TIME_CLOSE,
        DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL,
        TICKER_PER_DATE_TIME_LAST_VOL, // disabled
        TICKER_DATE_TIME_LAST_VOL, // disabled
        TICKER_DATE_TIME_LAST, // disabled
        DATE_TIME_LAST_VOL, // disabled
        DATE_TIME_LAST, // disabled
        DATE_TIME_LAST_VOL_ID, // disabled
        DATE_TIME_LAST_VOL_ID_OPER
    };

    BETTER_ENUM_SHORT_INIT(RecordFormat)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class FinamRequestParameters : public RequestParameters
{
public:
    static FinamRequestParameters forQuotations(Ticker ticker, QDate date);
    static FinamRequestParameters forDeals(Ticker ticker, QDate date);

    FinamRequestParameters();

    QString toGetRequestParameters() const override;

    int market() const;
    void setMarket(int market);

    int apply() const;
    void setApply(int apply);

    QDate from() const;
    void setFrom(const QDate& from);

    QDate to() const;
    void setTo(const QDate& to);

    TimeFrame timeFrame() const;
    void setTimeFrame(TimeFrame timeFrame);

    QString fileName() const;
    void setFileName(const QString& fileName);

    FileFormat fileFormat() const;
    void setFileFormat(FileFormat fileFormat);

    DateFormat dateFormat() const;
    void setDateFormat(DateFormat dateFormat);

    TimeFormat timeFormat() const;
    void setTimeFormat(TimeFormat timeFormat);

    CandleTime candleTime() const;
    void setCandleTime(CandleTime candleTime);

    bool moscowTime() const;
    void setMoscowTime(bool moscowTime);

    FieldSeparator fieldSeparator() const;
    void setFieldSeparator(FieldSeparator fieldSeparator);

    DecimalSeparator decimalSeparator() const;
    void setDecimalSeparator(DecimalSeparator decimalSeparator);

    RecordFormat recordFormat() const;
    void setRecordFormat(RecordFormat recordFormat);

    bool addHeader() const;
    void setAddHeader(bool addHeader);

    bool fillPeriods() const;
    void setFillPeriods(bool fillPeriods);

    Ticker ticker() const;
    void setTicker(const Ticker& ticker);

private:
    Ticker m_ticker;
    int m_market;
    int m_apply;
    QDate m_from;
    QDate m_to;
    TimeFrame m_timeFrame;
    QString m_fileName;
    FileFormat m_fileFormat;
    DateFormat m_dateFormat;
    TimeFormat m_timeFormat;
    CandleTime m_candleTime;
    bool m_moscowTime;
    FieldSeparator m_fieldSeparator;
    DecimalSeparator m_decimalSeparator;
    RecordFormat m_recordFormat;
    bool m_addHeader;
    bool m_fillPeriods;
};

const QString EXPORT_SERVICE_ADDRESS = "http://export.finam.ru/export9.out";

} // namespace finam

#endif // FINAMREQUESTPARAMETERS_H
