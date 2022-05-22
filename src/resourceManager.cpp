#include "resourceManager.h"

namespace Man520 {

    ResourceManager::ResourceManager() {
    }

    ResourceManager::ResourceManager(ResourceManager const&) {
    }

    ResourceManager& ResourceManager::operator=(ResourceManager const&) {
        return *this;
    }

    ResourceManager& ResourceManager::getInstance() {
        static ResourceManager* s_instance = new ResourceManager();
        return *s_instance;
    }

    SDL_Surface* ResourceManager::getSurface(const std::string& name) {
        auto it = m_surfaces.find(name);
        if(it == m_surfaces.end()) {
            SDL_Surface* surface = SDL_LoadBMP(name.c_str());
            m_surfaces.insert(std::make_pair(name, surface));
        }
        return m_surfaces[name];
    }

}
