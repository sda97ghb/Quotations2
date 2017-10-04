#ifndef APPLICATION_H
#define APPLICATION_H

#include "Data/DataLoader.h"

class Global
{
public:
    static Global& instance();

    DataLoader& dataLoader();

private:
    Global() = default;
    Global(const Global&) = delete;
    void operator =(const Global&) = delete;

    DataLoader m_dataLoader;
};

#endif // APPLICATION_H
