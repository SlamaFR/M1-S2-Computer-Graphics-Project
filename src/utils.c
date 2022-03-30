#include "../include/utils.h"

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void g3x_NormalVertex3dv(Shape *shape, int i) {
    g3x_Normal3dv(shape->normals[i]);
    g3x_Vertex3dv(shape->vertexes[i]);
}
