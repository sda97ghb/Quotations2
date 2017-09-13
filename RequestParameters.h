#ifndef REQUESTPARAMATERS_H
#define REQUESTPARAMATERS_H

#include <QString>
#include <QDate>

class MarketPlace
{
public:
    enum Value
    {
        MICEX,    ///< Фондовый рынок
        CURRENCY, ///< Валютный рынок
        FORTSF,   ///< Срочный рынок (фьючерсы)
        FORTSO,   ///< Срочный рынок (опционы)
        INDICES,  ///< Индексы
    };

    static QString toString(Value value);
};

class TimeFrame
{
public:
    enum Value
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

    static QString toString(Value value);
};

class FileFormat
{
public:
    enum Value
    {
        Txt,
        Csv
    };

    static QString toString(Value value);
};

class RecordFormat
{
public:
    enum Value
    {
        TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL,
        TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE,
        TICKER_PER_DATE_TIME_CLOSE_VOL,
        TICKER_PER_DATE_TIME_CLOSE,
        DATE_TIME_OPEN_HIGH_LOW_CLOSE_VOL,
        TICKER_PER_DATE_TIME_HIGH_LOW_CLOSE_VOL
    };

    static QString toString(Value value);
};

class DateFormat
{
public:
    enum Value
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

    static QString toString(Value value);
};

class TimeFormat
{
public:
    enum Value
    {
        HH_MM_SS,             ///< ЧЧММСС
        HH_colon_MM_colon_SS, ///< ЧЧ:ММ:СС
        HH_MM,                ///< ЧЧММ
        HH_colon_MM           ///< ЧЧ:ММ
    };

    static QString toString(Value value);
};

class FieldSeparator
{
public:
    enum Value
    {
        Semicolon,
        Comma,
        Dot,
        Space,
        Tab
    };

    static QString toString(Value value);
};

class DecimalSeparator
{
public:
    enum Value
    {
        Dot,
        Comma,
        Space,
        SingleQuote,
        None
    };

    static QString toString(Value value);
};

class RequestParameters
{
public:
    RequestParameters();

    QString toGetRequestParameters();

    MarketPlace::Value marketPlace() const;
    QString ticker() const;
    TimeFrame::Value timeFrame() const;
    QDate from() const;
    QDate to() const;
    QString fileName() const;
    FileFormat::Value fileFormat() const;
    RecordFormat::Value recordFormat() const;
    DateFormat::Value dateFormat() const;
    TimeFormat::Value timeFormat() const;
    FieldSeparator::Value fieldSeparator() const;
    DecimalSeparator::Value decimalSeparator() const;
    bool addHeader() const;

    void setMarketPlace(const MarketPlace::Value& marketPlace);
    void setTicker(const QString& ticker);
    void setTimeFrame(const TimeFrame::Value& timeFrame);
    void setFrom(const QDate& from);
    void setTo(const QDate& to);
    void setFileName(const QString& fileName);
    void setFileFormat(const FileFormat::Value& fileFormat);
    void setRecordFormat(const RecordFormat::Value& recordFormat);
    void setDateFormat(const DateFormat::Value& dateFormat);
    void setTimeFormat(const TimeFormat::Value& timeFormat);
    void setFieldSeparator(const FieldSeparator::Value& fieldSeparator);
    void setDecimalSeparator(const DecimalSeparator::Value& decimalSeparator);
    void setAddHeader(bool addHeader);

private:
    MarketPlace::Value m_marketPlace;
    QString m_ticker;
    TimeFrame::Value m_timeFrame;
    QDate m_from;
    QDate m_to;
    QString m_fileName;
    FileFormat::Value m_fileFormat;
    RecordFormat::Value m_recordFormat;
    DateFormat::Value m_dateFormat;
    TimeFormat::Value m_timeFormat;
    FieldSeparator::Value m_fieldSeparator;
    DecimalSeparator::Value m_decimalSeparator;
    bool m_addHeader;
};

#endif // REQUESTPARAMATERS_H
