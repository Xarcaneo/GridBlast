#include "ServiceRegistry.h"

// Initialize the static member
std::unique_ptr<ServiceRegistry> ServiceRegistry::instance = nullptr;

ServiceRegistry& ServiceRegistry::getInstance()
{
    if (!instance)
    {
        instance = std::unique_ptr<ServiceRegistry>(new ServiceRegistry());
    }
    return *instance;
}

// Explicit template instantiation
template void ServiceRegistry::registerService<IGameService>(std::shared_ptr<IGameService> service);
