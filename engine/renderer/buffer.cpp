#include "buffer.h"
#include "renderer.h"
#include "platform/openGL/openGLBuffer.h"

namespace Man520 {

    Ref<VertexBuffer> VertexBuffer::create(uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None: MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return createRef<OpenGLVertexBuffer>(size);
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:    MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return createRef<OpenGLVertexBuffer>(vertices, size);
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:    MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return createRef<OpenGLIndexBuffer>(indices, size);
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
