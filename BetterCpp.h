#ifndef BETTERCPP_H
#define BETTERCPP_H

#define unless(_condition_) if(!(_condition_))

#define return_after return(void)

#define BETTER_ENUM \
public: \
    using value_t = int; \
    operator int() const { return m_value; } \
    value_t operator =(value_t value) { m_value = value; return m_value; } \
protected: \
    value_t value() const { return m_value; } \
private: \
    value_t m_value;

#define BETTER_ENUM_SHORT_INIT(class_name) \
    class_name(value_t value) : m_value(value) {}

#define BETTER_ENUM_DEFAULT(class_name, default_value) \
    class_name() : m_value(default_value) {}

#include "IntRange.h"

#endif // BETTERCPP_H
