#include "OpenGLContext.h"

#include "../../Core/Log.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Platform {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			LOG_WARN("Warning: Failed to initialize GLEW");
		}

		LOG_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
		LOG_INFO("GLSL version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}