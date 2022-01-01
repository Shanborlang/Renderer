#ifndef RENDERER_TORUS_H
#define RENDERER_TORUS_H

#include "core/core.hpp"
#include "utils/trianglemesh.h"

class Torus : public TriangleMesh {
public:
    Torus(GLfloat outerRadius, GLfloat innerRadius, GLuint nsides, GLuint nrings);
};

#endif //RENDERER_TORUS_H
