#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

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

    return window;
}

void Update(GLFWwindow* window)
{
    SPDLOG_INFO("Update");

    while (!::glfwWindowShouldClose(window))
    {
        ::glfwPollEvents();
    }
}

int main(int argc, char** argv)
{   
    auto ret = Glfw_Initialize();
    assert(ret);

    auto window = Glfw_CreateWindow();
    assert(window);

    Update(window);

    ::glfwTerminate();

    return 0;
}