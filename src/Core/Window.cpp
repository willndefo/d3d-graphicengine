#include "Window.h"
#include "utilities.h"


GWindow::GWindow(int InWidth, int InHeight, std::string&& InTitle):
	Width(InWidth),
	Height(InHeight),
	Title(InTitle)
{
}

GWindow::~GWindow()
{
	glfwTerminate();
}

void GWindow::Init()
{
	if (!glfwInit())
	{
		DEBUG_LOG(LOG_ERROR, "GLFW init error.");
		abort();
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

	if (!Window)
	{
		DEBUG_LOG(LOG_ERROR, "Failed to create window.");
		glfwTerminate();
		abort();
	}
}

void GWindow::Run()
{
	//glfwSwapBuffers(window);
	glfwPollEvents();
}

bool GWindow::IsVisible() const
{
	return !glfwWindowShouldClose(Window);
}

GLFWwindow* GWindow::GetWindowHandler() const
{
	return Window;
}

HWND GWindow::GetWindowNativeHandler() const
{
	return glfwGetWin32Window(Window);
}

int GWindow::GetWidth() const
{
	return Width;
}

int GWindow::GetHeight() const
{
	return Height;
}
