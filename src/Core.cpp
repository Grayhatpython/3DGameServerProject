#include "Core.h"
#include "Context.h"

bool Core::Initialize()
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

    SPDLOG_INFO("GLFW CreateWindow");

    _window = ::glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (_window == nullptr)
    {
        SPDLOG_ERROR("Failed to create window glfw");
        ::glfwTerminate();
        return false;
    }
   
    ::glfwMakeContextCurrent(_window);

    if (!::gladLoadGLLoader((GLADloadproc)::glfwGetProcAddress))
    {
        SPDLOG_ERROR("Failed to Load Glad");
        ::glfwTerminate();
        return false;
    }

    auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    SPDLOG_INFO("Opengl Version : {}", version);

    ::glfwSetFramebufferSizeCallback(_window, Core::OnGlViewportChanged);
    ::glfwSetKeyCallback(_window, Core::OnKeyboardEvent);

    _context = Context::Create();
    if (_context == nullptr)
    {
        SPDLOG_ERROR("Failed to create context");
        ::glfwTerminate();
        return false;
    }

	return true;
}

void Core::Update()
{
    SPDLOG_INFO("Update");

    while (!::glfwWindowShouldClose(_window))
    {
        //  Poll
        ::glfwPollEvents();

        //  Render
        _context->Render();
        ::glfwSwapBuffers(_window);
    }

    _context.reset();
    ::glfwTerminate();
}

void Core::OnGlViewportChanged(GLFWwindow* window, int width, int height)
{
    SPDLOG_INFO("Gl ViewPort Changed : ({} , {})", width, height);
    glViewport(0, 0, width, height);
}

void Core::OnKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("Keyboard Event - [ key : {}, scancode : {}, action : {}, mods : {}{}{}", key, scancode,
        action == GLFW_PRESS ? "Pressed" : action == GLFW_RELEASE ? "Released" : action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "Ctrl" : "_", mods & GLFW_MOD_SHIFT ? "Shift" : "_", mods & GLFW_MOD_ALT ? "Alt" : "_");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        ::glfwSetWindowShouldClose(window, true);
}
