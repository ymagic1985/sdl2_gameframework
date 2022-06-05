#pragma once

#include <SDL2/SDL.h>
#include "mzpch.h"

namespace Man520 {

    class Layer {
        public:
            Layer(const std::string& name = "New Layer") : mName{name} {}
            virtual ~ Layer() {}

            virtual void onAttach() {}
            virtual void onDetach() {}
            virtual void onUpdate() {}
            virtual void onEvent(SDL_Event& event) {}

            inline const std::string& getName() const { return mName; }
        protected:
            std::string mName;
    };

}
