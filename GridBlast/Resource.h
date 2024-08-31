#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
public:
    Resource(const std::string& id) : id(id) {}
    virtual ~Resource() {}

    const std::string& GetID() const { return id; }

    // Virtual method to load the resource; this will be overridden by derived classes
    virtual bool Load() = 0;

protected:
    std::string id;  // Unique identifier for the resource
};

#endif // RESOURCE_H
