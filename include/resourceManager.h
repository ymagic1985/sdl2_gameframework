#pragma once

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h> 

namespace Man520 {

    class ResourceManager {
        private:
            ResourceManager();
            ~ResourceManager();
            ResourceManager(ResourceManager const&);
            ResourceManager& operator=(ResourceManager const&);
            
            std::unordered_map<std::string, SDL_Surface*> m_surfaces;
            
        public:
            void clear();
            static ResourceManager& getInstance();
            SDL_Surface* getSurface(const std::string& name);
    };

}
