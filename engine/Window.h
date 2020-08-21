//
// Created by larsewi on 19.08.2020.
//

#ifndef ACRYLIC_WINDOW_H
#define ACRYLIC_WINDOW_H

#include <string>
#include <vector>
#include <GLFW/glfw3.h>


class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() { return glfwWindowShouldClose(m_pGLFWwindow) != 0; }
    static void pollEvents() { glfwPollEvents(); }

    static std::vector<const char*> getRequiredExtensions();

private:
    static int count;
    GLFWwindow* m_pGLFWwindow;
};


#endif //ACRYLIC_WINDOW_H
