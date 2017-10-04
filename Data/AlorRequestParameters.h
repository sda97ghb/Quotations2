#ifndef REQUESTPARAMATERS_H
#define REQUESTPARAMATERS_H

#include "BetterCpp.h"
#include "RequestParameters.h"

#include <QDate>

namespace alor
{

class MarketPlace
{
    BETTER_ENUM
public:
    enum
    {
        MICEX,    ///< Фондовый рынок
        CURRENCY, ///< Валютный рынок
        FORTSF,   ///< Срочный рынок (фьючерсы)
        FORTSO,   ///< Срочный рынок (опционы)
        INDICES,  ///< Индексы
    };

    BETTER_ENUM_SHORT_INIT(MarketPlace)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class TimeFrame
{
    BETTER_ENUM
public:
    enum
    {
        Minute,
        Minute_x_5,
        Minute_x_10,
        Minute_x_15,
        Minute_x_20,
        Minute_x_30,
        Hour,
        Day
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
    QString toString() const {return QString(*this); }
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
        TICKER_PER_DATE_TIME_HIGH_LOW_CLOSE_VOL
    };

    BETTER_ENUM_SHORT_INIT(RecordFormat)

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
        YYYY_minus_MM_minus_DD, ///< ГГГГ-ММ-ДД
        YYYY_dot_MM_dot_DD,     ///< ГГГГ.ММ.ДД
        DD_minus_MM_minus_YYYY, ///< ДД-ММ-ГГГГ
        DD_dot_MM_dot_YYYY      ///< ДД.ММ.ГГГГ
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
        HH_colon_MM_colon_SS, ///< ЧЧ:ММ:СС
        HH_MM,                ///< ЧЧММ
        HH_colon_MM           ///< ЧЧ:ММ
    };

    BETTER_ENUM_SHORT_INIT(TimeFormat)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class FieldSeparator
{
    BETTER_ENUM
public:
    enum
    {
        Semicolon,
        Comma,
        Dot,
        Space,
        Tab
    };

    BETTER_ENUM_SHORT_INIT(FieldSeparator)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class DecimalSeparator
{
    BETTER_ENUM
public:
    enum
    {
        Dot,
        Comma,
        Space,
        SingleQuote,
        None
    };

    BETTER_ENUM_SHORT_INIT(DecimalSeparator)

    operator QString() const;
    QString toString() const { return QString(*this); }
};

class AlorRequestParameters : public RequestParameters
{
public:
    static AlorRequestParameters forQuotations(QString ticker, QDate date);

    AlorRequestParameters();

    QString toGetRequestParameters() const override;

    MarketPlace marketPlace() const;
    QString ticker() const;
    TimeFrame timeFrame() const;
    QDate from() const;
    QDate to() const;
    QString fileName() const;
    FileFormat fileFormat() const;
    RecordFormat recordFormat() const;
    DateFormat dateFormat() const;
    TimeFormat timeFormat() const;
    FieldSeparator fieldSeparator() const;
    DecimalSeparator decimalSeparator() const;
    bool addHeader() const;

    void setMarketPlace(MarketPlace marketPlace);
    void setTicker(const QString& ticker);
    void setTimeFrame(TimeFrame timeFrame);
    void setFrom(const QDate& from);
    void setTo(const QDate& to);
    void setFileName(const QString& fileName);
    void setFileFormat(FileFormat fileFormat);
    void setRecordFormat(RecordFormat recordFormat);
    void setDateFormat(DateFormat dateFormat);
    void setTimeFormat(TimeFormat timeFormat);
    void setFieldSeparator(FieldSeparator fieldSeparator);
    void setDecimalSeparator(DecimalSeparator decimalSeparator);
    void setAddHeader(bool addHeader);

private:
    MarketPlace m_marketPlace;
    QString m_ticker;
    TimeFrame m_timeFrame;
    QDate m_from;
    QDate m_to;
    QString m_fileName;
    FileFormat m_fileFormat;
    RecordFormat m_recordFormat;
    DateFormat m_dateFormat;
    TimeFormat m_timeFormat;
    FieldSeparator m_fieldSeparator;
    DecimalSeparator m_decimalSeparator;
    bool m_addHeader;
};

} // namespace alor

#endif // REQUESTPARAMATERS_H
