#ifndef RENDERER_TRIANGLEMESH_H
#define RENDERER_TRIANGLEMESH_H

#include "core/core.hpp"
#include "utils/drawable.h"

class TriangleMesh : public Drawable {
public:
    virtual ~TriangleMesh();

    virtual void render() const;
    [[nodiscard]] inline GLuint getVao() const { return vao; }
    [[nodiscard]] inline GLuint getNumVerts() const { return nVerts; }
    GLuint getElementBuffer() { return buffers[0]; }
    GLuint getPositionBuffer() { return buffers[1]; }
    GLuint getNormalBuffer() { return buffers[2]; }
    GLuint getTcBuffer() { if(buffers.size() > 3) return buffers[3]; else return 0; }

protected:
    GLuint vao;
    GLuint nVerts;

    // Vertex buffers
    std::vector<GLuint> buffers;

    virtual void initBuffers(
            std::vector<GLuint>* indices,
            std::vector<GLfloat>* points,
            std::vector<GLfloat>* normals,
            std::vector<GLfloat>* texCoords = nullptr,
            std::vector<GLfloat>* tangents = nullptr
    );

    virtual void deleteBuffers();

};

#endif //RENDERER_TRIANGLEMESH_H
