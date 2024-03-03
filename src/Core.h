#pragma once

#include "Context.h"
class Core
{
public:
	bool Initialize();

public:
	void Update();

public:
	static void OnGlViewportChanged(GLFWwindow* window, int width, int height);
	static void OnKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	GLFWwindow*					_window = nullptr;
	std::unique_ptr<Context>	_context;
};