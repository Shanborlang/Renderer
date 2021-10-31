#include "core/core.hpp"
#include "core/scene.hpp"
#include "core/scene_runner.hpp"
#include <memory>

class Example : public Scene {
public:
    void initScene() override {

    }

    void update(float t) override {

    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT);
    };

    void resize(int w, int h) override {
        glViewport(0, 0, w, h);
        width = w;
        height = h;
    }
};

int main(int argc, char* argv[]) {
    SceneRunner runner("Example");

    auto scene = std::unique_ptr<Scene>(new Example());

    return runner.run(std::move(scene));
}