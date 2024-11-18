#include "strkpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Strike {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}

		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}