#ifndef APPLICATION_H
#define APPLICATION_H

#include "DataManager.h"

class Application
{
public:
    static Application& instance();

    DataManager& dataManager();

private:
    Application() = default;
    Application(const Application&) = delete;
    void operator =(const Application&) = delete;

    DataManager m_dataManager;
};

#endif // APPLICATION_H
