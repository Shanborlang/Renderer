#include "core/core.hpp"
#include "core/scene.hpp"
#include "core/scene_runner.hpp"
#include "common/glsl_shader.hpp"
#include "utils/torus.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

class Example : public Scene {
public:
    Example() : torus(0.7f, 0.3f, 30, 30) {}

    void initScene() override {
        compileAndLinkShader();

        glEnable(GL_DEPTH_TEST);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f,0.0f,0.0f));
        model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f,1.0f,0.0f));
        view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
        projection = glm::mat4(1.0f);

        shader.setUniform("Kd", 0.9f, 0.5f, 0.3f);
        shader.setUniform("Ld", 1.0f, 1.0f, 1.0f);
        shader.setUniform("LightPosition", view * glm::vec4(5.0f,5.0f,2.0f,1.0f) );
    }

    void update(float t) override {

    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setMatrices();
        torus.render();
    };

    void resize(int w, int h) override {
        glViewport(0, 0, w, h);
        width = w;
        height = h;
        projection = glm::perspective(glm::radians(70.0f), (float)w/(float)h, 0.3f, 100.f);
    }

private:
    Shader shader;
    Torus torus;

    void setMatrices() {
        glm::mat4 mv = view * model;
        shader.setUniform("ModelViewMatrix", mv);
        shader.setUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
        shader.setUniform("MVP", projection * mv);
    }

    void compileAndLinkShader() {
        try {
            shader.compileShader("../assets/shaders/diffuse.vert");
            shader.compileShader("../assets/shaders/diffuse.frag");
            shader.link();
            shader.use();
        }catch (ShaderException& e) {
            fprintf(stderr, "%s\n", e.what());
            exit(EXIT_FAILURE);
        }
    }
};

int main(int argc, char* argv[]) {
    SceneRunner runner("Example");

    auto scene = std::unique_ptr<Scene>(new Example());

    return runner.run(std::move(scene));
}