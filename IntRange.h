#ifndef INTRANGE_H
#define INTRANGE_H

/// Iteratable integer range. It don't alocate memory for each elements.
/// Can be use in range-base for.
/// @note Range includes both of it's ends.
/// Example:
///     for (int i : Range(1, 5))
///         std::cout << i << ", ";
///     std::cout << std::endl;
///     // Output: 1, 2, 3, 4, 5
class Range
{
public:
    class iterator {
    public:
        iterator(int value);
        iterator(const iterator& other);
        iterator& operator=(const iterator& other);
        iterator& operator++();
        int operator*() const;
        bool operator !=(const iterator& other);
        friend void swap(iterator& lhs, iterator& rhs);
    private:
        int m_value;
    };

    Range(int min, int max);

    iterator begin();
    iterator end();

private:
    int m_min;
    int m_max;
};

#endif // INTRANGE_H
