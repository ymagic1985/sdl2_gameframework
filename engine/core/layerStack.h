#pragma once

#include "mzpch.h"
#include "layer.h"

namespace Man520 {
    
    class LayerStack {
        public:
            LayerStack() = default;
            ~LayerStack();

            void pushLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popLayer(Layer* layer);
            void popOverlay(Layer* overlay);

            std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
            std::vector<Layer*>::iterator end() { return mLayers.end(); }
            std::vector<Layer*>::reverse_iterator rbegin() { return mLayers.rbegin(); }
            std::vector<Layer*>::reverse_iterator rend() { return mLayers.rend(); }
                
            std::vector<Layer*>::const_iterator begin() const { return mLayers.begin(); }
            std::vector<Layer*>::const_iterator end()	const { return mLayers.end(); }
            std::vector<Layer*>::const_reverse_iterator rbegin() const { return mLayers.rbegin(); }
            std::vector<Layer*>::const_reverse_iterator rend() const { return mLayers.rend(); }
        private:
            std::vector<Layer*> mLayers;
            unsigned int mLayerInsertIndex{0};
    };

}
