#pragma once

#include <g3x.h>

typedef struct shape__s_ {
    int n1, n2, n3;
    G3Xpoint *vertexes;
    G3Xvector *normals;

    void (*drawPoints)(struct shape__s_ *, G3Xvector scale_factor);

    void (*drawFaces)(struct shape__s_ *, G3Xvector scale_factor);

    void (*updateScale)(void *, double x, double y, double z);

    G3Xvector (*applyScale3d)(void *, double x, double y, double z);
} Shape;
