#include "strkpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Strike/Platform/OpenGL/OpenGLBuffer.h"

namespace Strike {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		STRK_CORE_ASSERT(false, "RendererAPI::None currently not supprorted!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		STRK_CORE_ASSERT(false, "RendererAPI::None currently not supprorted!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}

		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}