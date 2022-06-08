#include "mzpch.h"
#include "texture.h"

#include "renderer.h"
#include "platform/openGL/openGLTexture.h"

namespace Man520 {

    Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
        switch(Renderer::getAPI()) {
            case RendererAPI::API::None: MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(width, height);
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::create(const std::string &path) {
        switch(Renderer::getAPI()) {
            case RendererAPI::API::None: MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;      
    }

}
