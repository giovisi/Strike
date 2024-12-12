#include "strkpch.h"
#include "WindowsWindow.h"

#include "Strike/Events/ApplicationEvent.h"
#include "Strike/Events/KeyEvent.h"
#include "Strike/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Strike {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		STRK_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		STRK_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		STRK_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		STRK_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		STRK_CORE_INFO("Creating new window {0} {1} {2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			STRK_PROFILE_SCOPE("glfwInit");

			int success = glfwInit();
			STRK_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		{
			STRK_PROFILE_SCOPE("glfwCreateWindow");

			m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, props.Title.c_str(), nullptr, nullptr);
		}

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS) {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
			}
			else if (action == GLFW_REPEAT) {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS) {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		STRK_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		STRK_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		STRK_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }
}