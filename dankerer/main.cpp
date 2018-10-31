#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <experimental/filesystem>
#include "absl/strings/str_cat.h"

#include "gfx/window.h"

using namespace dk::gfx;
namespace fs = std::experimental::filesystem;
namespace chr = std::chrono;

void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Error: " << message << '\n';
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Could not start GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
    std::cout << "Running in debug mode!\n";
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "DanVonkRenderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not open window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(errorCallback, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
#endif

    Window gameWindow(window, 800, 600);

    glfwSetWindowUserPointer(window, (void*)&gameWindow);

    auto keybFunc = [](GLFWwindow* window, int key, int scanCode, int actions, int mods) {
        static_cast<Window*>(glfwGetWindowUserPointer(window))->handleKeyboard(window, key, scanCode, actions, mods);
    };

    auto mouseFunc = [](GLFWwindow* window, double xpos, double ypos) {
        static_cast<Window*>(glfwGetWindowUserPointer(window))->handleMouse(window, xpos, ypos);
    };

    glfwSetKeyCallback(window, keybFunc);
    glfwSetCursorPosCallback(window, mouseFunc);

    auto currentTime = chr::high_resolution_clock::now();
    using ms = chr::milliseconds;

    gameWindow.init();

    while (!glfwWindowShouldClose(window)) {
        auto newTime = std::chrono::high_resolution_clock::now();
        auto frameTime = newTime - currentTime;
        currentTime = newTime;

        gameWindow.update(chr::duration_cast<ms>(frameTime).count());
        gameWindow.setTitle(absl::StrCat("DanVonkRenderer @ ", ((float) 1/ (float) chr::duration_cast<ms>(frameTime).count()) * 1000.0f, " fps, "));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        GLenum err;
        while ((err = static_cast<GLenum>(glGetError() != GL_NO_ERROR))) {
            std::cerr << "glGetError() returns: " << err << '\n';
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
