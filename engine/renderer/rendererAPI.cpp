#include "rendererAPI.h"
#include "mzpch.h"
#include "platform/openGL/openGLRendererAPI.h"

namespace Man520 {

    RendererAPI::API RendererAPI::sAPI = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::create() {
        switch(sAPI) {
            case RendererAPI::API::None:
                MAN520_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return createScope<OpenGLRendererAPI>();
        }
        MAN520_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

}
