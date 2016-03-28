/*
From; http://www.glfw.org/documentation.html
*/

#include <GLFW/glfw3.h>

int main(void) {
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(640, 480, __FILE__, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        /* Required if we want the window to close when the X is clicked. */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
