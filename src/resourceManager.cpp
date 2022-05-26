#include "resourceManager.h"

namespace Man520 {

    ResourceManager::ResourceManager() {
    }
    
    ResourceManager::~ResourceManager() {
        clear();
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

    void ResourceManager::clear() {
        auto it = m_surfaces.begin();
        for(; it != m_surfaces.end(); it++) {
            SDL_FreeSurface(it->second);
        }
        m_surfaces.clear();
    } 

}
