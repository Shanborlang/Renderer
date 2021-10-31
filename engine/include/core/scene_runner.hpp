//
// Created by shanb on 18-10-2020.
//

#ifndef RENDERER_SCENE_RUNNER_HPP
#define RENDERER_SCENE_RUNNER_HPP

#include "core.hpp"
#include "scene.hpp"
#include "common/debug.hpp"

#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class SceneRunner {
private:
    GLFWwindow *window {nullptr};
    int fbw{}, fbh{};
    bool debug;

public:
    explicit SceneRunner(const std::string &l_windowTitle, int l_width = WIDTH, int l_height = HEIGHT, int l_samples = 0) : debug{true} {
        if (!glfwInit()) exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        if (debug) {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        }
        if (l_samples > 0) {
            glfwWindowHint(GLFW_SAMPLES, l_samples);
        }

        window = glfwCreateWindow(l_width, l_height, l_windowTitle.c_str(), nullptr, nullptr);
        if (!window) {
            std::cerr << "Unable to create OpenGL context." << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);

        glfwGetFramebufferSize(window, &fbw, &fbh);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        debug::dump_gl_info();

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

#ifndef __APPLE__
        if (debug) {
            glDebugMessageCallback(debug::debug_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, GL_DEBUG_SEVERITY_NOTIFICATION,
                                 -1, "Start debugging");
        }
#endif
    }

    int run(std::unique_ptr<Scene> scene) {
        mainLoop(window, std::move(scene));

#ifndef __APPLE__
        if (debug)
            glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "End debug");
#endif

        // Close window and terminate GLFW
        glfwTerminate();

        // Exit program
        return EXIT_SUCCESS;
    }

private:
    void mainLoop(GLFWwindow *l_window, std::unique_ptr<Scene> l_scene) const {
        l_scene->setDimensions(fbw, fbh);
        l_scene->initScene();
        l_scene->resize(fbw, fbh);

        while (!glfwWindowShouldClose(l_window) && !glfwGetKey(l_window, GLFW_KEY_ESCAPE)) {
            debug::check_for_opengl_error(__FILE__, __LINE__);

            l_scene->update(static_cast<float>(glfwGetTime()));
            l_scene->render();

            glfwSwapBuffers(l_window);
            glfwPollEvents();
            int state = glfwGetKey(l_window, GLFW_KEY_SPACE);
            if (state == GLFW_PRESS)
                l_scene->animate(!l_scene->animating());
        }
    }
};

#endif //RENDERER_SCENE_RUNNER_HPP
