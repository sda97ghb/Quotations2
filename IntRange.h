#ifndef INTRANGE_H
#define INTRANGE_H

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
