#include "Application.h"

Application& Application::instance()
{
    static Application instance;
    return instance;
}

DataManager& Application::dataManager()
{
    return m_dataManager;
}
