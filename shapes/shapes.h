#pragma once

#include <g3x.h>

typedef struct shape__s_ {
    int n1, n2, n3;
    G3Xpoint *vertexes;
    G3Xvector *normals;

    void (*draw_points)(struct shape__s_ *, G3Xvector scale_factor);

    void (*draw_faces)(struct shape__s_ *, G3Xvector scale_factor);

    void (*update_scale)(void *, double x, double y, double z);
} Shape;
