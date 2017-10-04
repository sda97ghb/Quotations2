#include "Global.h"

Global& Global::instance()
{
    static Global instance;
    return instance;
}

DataLoader& Global::dataLoader()
{
    return m_dataLoader;
}
