#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

bool Glfw_Initialize()
{
    SPDLOG_INFO("GLFW Initialize");

    if (::glfwInit() == GLFW_FALSE)
    {
        const char* errorMsg = nullptr;
        ::glfwGetError(&errorMsg);
        SPDLOG_ERROR("Failed to initialize glfw : {}", errorMsg);
        return false;
    }

    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

GLFWwindow* Glfw_CreateWindow()
{
    SPDLOG_INFO("GLFW CreateWindow");

    GLFWwindow* window = nullptr;
    window = ::glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (window == nullptr)
    {
        SPDLOG_ERROR("Failed to create window glfw");
        ::glfwTerminate();
    }
    else
        ::glfwMakeContextCurrent(window);

    return window;
}

bool GladLoad()
{
    if (!::gladLoadGLLoader((GLADloadproc)::glfwGetProcAddress))
    {
        SPDLOG_ERROR("Failed to Load Glad");
        ::glfwTerminate();
        return false;
    }

    return true;
}

void Render(GLFWwindow* window)
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ::glfwSwapBuffers(window);
}

void Update(GLFWwindow* window)
{
    SPDLOG_INFO("Update");

    while (!::glfwWindowShouldClose(window))
    {
        ::glfwPollEvents();
        Render(window);
    }
}

void OnGlViewportChanged(GLFWwindow* window, int width, int height)
{
    SPDLOG_INFO("Gl ViewPort Changed : ({} , {})", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("Keyboard Event - [ key : {}, scancode : {}, action : {}, mods : {}{}{}", key, scancode,
        action == GLFW_PRESS ? "Pressed" : action == GLFW_RELEASE ? "Released" : action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "Ctrl" : "_", mods & GLFW_MOD_SHIFT ? "Shift" : "_", mods & GLFW_MOD_ALT ? "Alt" : "_");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        ::glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv)
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto ret = Glfw_Initialize();
    assert(ret);

    auto window = Glfw_CreateWindow();
    assert(window);

    auto loaded = GladLoad();
    assert(loaded);

    auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    SPDLOG_INFO("Opengl Version : {}", version);

    ::glfwSetFramebufferSizeCallback(window, OnGlViewportChanged);
    ::glfwSetKeyCallback(window, OnKeyboardEvent);

    Update(window);

    ::glfwTerminate();

    return 0;
}