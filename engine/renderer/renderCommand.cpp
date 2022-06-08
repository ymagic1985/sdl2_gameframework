#include "mzpch.h"
#include "renderCommand.h"

namespace Man520 {

    Scope<RendererAPI> RenderCommand::sRendererAPI = RendererAPI::create();

}
