#include "graphicsContext.h"

#include "renderer.h"
#include "platform/openGL/openGLContext.h"
#include "rendererAPI.h"

#include <SDL2/SDL.h>

namespace Man520 {

    Scope<GraphicsContext> GraphicsContext::create(void* window) {
        switch(Renderer::getAPI()) {
            case RendererAPI::API::None: MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return createScope<OpenGLContext>(static_cast<SDL_Window*>(window));
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
