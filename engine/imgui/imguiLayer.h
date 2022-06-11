#pragma once

#include "core/layer.h"

namespace Man520 {

    class ImguiLayer : public Layer {
        public:
            ImguiLayer();
            ~ImguiLayer() = default;

            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual bool onEvent(SDL_Event& event) override;
            virtual void onImguiRender() override;
            void begin();
            void end();

            void blockEvents(bool block) { mBlockEvents = block; }
        private:
            bool mBlockEvents = true;
    };

}
