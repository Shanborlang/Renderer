//
// Created by shanb on 18-10-2020.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include "glm/glm.hpp"

class Scene {

public:
    uint32_t width;
    uint32_t height;

    Scene() : m_animate{true}, width{800}, height{600} {}

    virtual ~Scene() = default;

    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }

    // Load textures, initialize shaders, etc.
    virtual void initScene() = 0;

    // Called prior to every frame
    virtual void update(float t) = 0;

    // Draw
    virtual void render() = 0;

    virtual void resize(int, int) = 0;

    void animate(bool value) { m_animate = value; }

    [[nodiscard]] bool animating() const { return m_animate; }

protected:
    glm::mat4 model, view, projection;
    bool m_animate;
};

#endif //RENDERER_SCENE_HPP
