#include "Application.h"
#include "LoadDataFromServer.h"

LoadDataFromServer::LoadDataFromServer(const LoadDataFromServer&) :
    QObject()
{
    // Designed as empty
}

void LoadDataFromServer::execute()
{
    Application::instance().dataManager().loadData();
}
