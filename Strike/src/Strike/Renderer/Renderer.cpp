#include "strkpch.h"
#include "Renderer.h"

namespace Strike {
	void Renderer::BeginScene() {
	}
	
	void Renderer::EndScene() {
	}
	
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}
}