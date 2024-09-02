#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include "IGameService.h"

class ServiceRegistry
{
private:
    std::unordered_map<std::type_index, std::shared_ptr<IGameService>> serviceDictionary;
    static std::unique_ptr<ServiceRegistry> instance;

    ServiceRegistry() = default;

public:
    static ServiceRegistry& getInstance();

    template <typename T>
    std::shared_ptr<T> getService()
    {
        std::type_index serviceName = typeid(T);
        auto it = serviceDictionary.find(serviceName);
        if (it == serviceDictionary.end())
        {
            throw std::runtime_error("Service of type " + std::string(serviceName.name()) + " is not registered.");
        }
        return std::static_pointer_cast<T>(it->second);
    }

    template <typename T>
    void registerService(std::shared_ptr<T> service)
    {
        std::type_index serviceName = typeid(T);
        if (serviceDictionary.find(serviceName) != serviceDictionary.end())
        {
            throw std::runtime_error("Service of type " + std::string(serviceName.name()) + " is already registered.");
        }
        serviceDictionary[serviceName] = service;
    }

    template <typename T>
    void unregisterService()
    {
        std::type_index serviceName = typeid(T);
        auto it = serviceDictionary.find(serviceName);
        if (it == serviceDictionary.end())
        {
            throw std::runtime_error("Service of type " + std::string(serviceName.name()) + " is not registered.");
        }
        serviceDictionary.erase(it);
    }
};

// Include the implementation of the template functions if you need them separate
// Alternatively, put them in the same header file as shown here.

#endif // SERVICEREGISTRY_H
