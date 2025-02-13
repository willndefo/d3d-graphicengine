#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <string>

class GWindow
{
private:
	GLFWwindow* Window;
	int Width;
	int Height;
	std::string Title;

public:
	GWindow(int InWidth, int InHeight, std::string&& Title);
	~GWindow();

	void Init();
	void Run();

	bool IsVisible() const;
	GLFWwindow* GetWindowHandler() const;
	HWND GetWindowNativeHandler() const;

	int GetWidth() const;
	int GetHeight() const;
};