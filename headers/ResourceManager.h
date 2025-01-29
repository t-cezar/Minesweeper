#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>
#include "../headers/GameException.h"

//pot folosi ResourceManager daca in viitor vreau sa adaug animatii/sunete
template <typename T>
class ResourceManager {
protected:
    std::shared_ptr<std::map<std::string, T>> resources;

public:
    explicit ResourceManager(std::shared_ptr<std::map<std::string, T>> res)
        : resources(res) {}

    void add(const std::string& name, const std::string& path) const {
        T resource;
        if (resource.loadFromFile(path)) {
            (*resources)[name] = resource;
        } else {
            throw TextureException("Esuare incarcare resursa din path-ul: " + path);
        }
    }
};

#endif // RESOURCEMANAGER_H