
#include "vertexArray.h"

#include "renderer.h"
#include "platform/openGL/openGLVertexArray.h"

namespace Man520 {

	Ref<VertexArray> VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None:    MAN520_CORE_ERROR("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return createRef<OpenGLVertexArray>();
		}

		MAN520_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}

}

