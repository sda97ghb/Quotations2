#include "IntRange.h"

#include <algorithm>

Range::iterator::iterator(int value) :
    m_value(value)
{
    // Designed as empty
}

Range::iterator::iterator(const Range::iterator& other) :
    m_value(other.m_value)
{
    // Designed as empty
}

Range::iterator& Range::iterator::operator=(const Range::iterator& other)
{
    m_value = other.m_value;
    return *this;
}

Range::iterator& Range::iterator::operator++() //prefix increment
{
    m_value++;
    return *this;
}

int Range::iterator::operator*() const
{
    return m_value;
}

bool Range::iterator::operator !=(const Range::iterator& other)
{
    return m_value != other.m_value;
}

void swap(Range::iterator& lhs, Range::iterator& rhs)
{
    std::swap(lhs.m_value, rhs.m_value);
}

Range::Range(int min, int max) :
    m_min(min < max ? min : max),
    m_max(min < max ? max : min)
{
    // Designed as empty
}

Range::iterator Range::begin()
{
    return iterator(m_min);
}

Range::iterator Range::end()
{
    return iterator(m_max + 1);
}
