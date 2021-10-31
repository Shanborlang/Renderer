//
// Created by shanb on 18-10-2020.
//

#ifndef RENDERER_GLSL_SHADER_HPP
#define RENDERER_GLSL_SHADER_HPP

#include "core/core.hpp"

#include <string>
#include <map>
#include <glm/glm.hpp>
#include <stdexcept>

class ShaderException : public std::runtime_error {
public:
    ShaderException(const std::string &msg) : std::runtime_error(msg) {}
};

enum class ShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    COMPUTE = GL_COMPUTE_SHADER
};

class Shader {
private:
    GLuint handle;
    bool linked;
    std::map<std::string, int32_t> uniformLocations;

    inline GLint getUniformLocation(const char* name);
    void detachAndDeleteShaderObjects();
    bool fileExists(const std::string &fileName);
    std::string getExtension(const char* fileName);

public:
    Shader();
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void compileShader(const char* fileName);
    void compileShader(const char* fileName, ShaderType type);
    void compileShader(const std::string &source, ShaderType type, const char* fileName = nullptr);

    void link();
    void validate();
    void use();

    int getHandle() const;
    bool isLinked() const;

    void bindAttribLocation(GLuint location, const char* name);
    void bindFragDataLocation(GLuint location, const char* name);

    void setUniform(const char *name, float x, float y, float z);
    void setUniform(const char *name, const glm::vec2 &v);
    void setUniform(const char *name, const glm::vec3 &v);
    void setUniform(const char *name, const glm::vec4 &v);
    void setUniform(const char *name, const glm::mat4 &m);
    void setUniform(const char *name, const glm::mat3 &m);
    void setUniform(const char *name, float val);
    void setUniform(const char *name, int val);
    void setUniform(const char *name, bool val);
    void setUniform(const char *name, GLuint val);

    // For debug purpose
    void findUniformLocations();
    void printActiveUniforms();
    void printActiveUniformBlocks();
    void printActiveAttribs();

    const char* getTypeString(GLenum type);
};

#endif //RENDERER_GLSL_SHADER_HPP
