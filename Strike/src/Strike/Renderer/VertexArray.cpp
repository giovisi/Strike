#include "strkpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Strike/Platform/OpenGL/OpenGLVertexArray.h"

namespace Strike {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		STRK_CORE_ASSERT(false, "RendererAPI::None currently not supprorted!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}