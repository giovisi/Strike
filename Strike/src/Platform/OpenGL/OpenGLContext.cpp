#include "strkpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Strike{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) {
		STRK_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		STRK_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		STRK_CORE_ASSERT(status, "Failed to initialize Glad!");

		STRK_CORE_INFO("OpenGL Info");
		STRK_CORE_INFO("  Vendor: {0}", (const char*) glGetString(GL_VENDOR));
		STRK_CORE_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
		STRK_CORE_INFO("  Version: {0}", (const char*) glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		STRK_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}