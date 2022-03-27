#include "sphere.h"
#include "../utils.h"
#include "../trees/node.h"

void drawCubePoints(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;
    int step3 = scale.z > 0 ? 1. / scale.z : 1;
    int offset = n1 * n1;

    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < n1; i += step2) {
        for (int j = 0; j < n1; j += step1) {
            g3x_NormalVertex3dv(this, i * n1 + j);
            g3x_NormalVertex3dv(this, offset + i * n1 + j);
        }
    }
    for (int i = 0; i < n1; i += step2) {
        for (int j = 0; j < n1; j += step3) {
            g3x_NormalVertex3dv(this, (2 * offset) + i * n1 + j);
            g3x_NormalVertex3dv(this, (3 * offset) + i * n1 + j);
        }
    }
    for (int i = 0; i < n1; i += step1) {
        for (int j = 0; j < n1; j += step3) {
            g3x_NormalVertex3dv(this, (4 * offset) + i * n1 + j);
            g3x_NormalVertex3dv(this, (5 * offset) + i * n1 + j);
        }
    }
    glEnd();
}

void drawCubeFaces(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;
    int step3 = scale.z > 0 ? 1. / scale.z : 1;
    int offset = n1 * n1;

    glBegin(GL_QUADS);
    int iNext, jNext;
    for (int i = 0; i < n1 - 1; i += step2) {
        iNext = min(i + step2, n1 - 1);
        for (int j = 0; j < n1 - 1; j += step3) {
            jNext = min(j + step3, n1 - 1);
            g3x_NormalVertex3dv(this, iNext * n1 + j);
            g3x_NormalVertex3dv(this, iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, i * n1 + jNext);
            g3x_NormalVertex3dv(this, i * n1 + j);

            g3x_NormalVertex3dv(this, offset + i * n1 + j);
            g3x_NormalVertex3dv(this, offset + i * n1 + jNext);
            g3x_NormalVertex3dv(this, offset + iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, offset + iNext * n1 + j);
        }
    }

    for (int i = 0; i < n1 - 1; i += step1) {
        iNext = min(i + step1, n1 - 1);
        for (int j = 0; j < n1 - 1; j += step3) {
            jNext = min(j + step3, n1 - 1);
            g3x_NormalVertex3dv(this, (2 * offset) + i * n1 + j);
            g3x_NormalVertex3dv(this, (2 * offset) + i * n1 + jNext);
            g3x_NormalVertex3dv(this, (2 * offset) + iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, (2 * offset) + iNext * n1 + j);

            g3x_NormalVertex3dv(this, (3 * offset) + iNext * n1 + j);
            g3x_NormalVertex3dv(this, (3 * offset) + iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, (3 * offset) + i * n1 + jNext);
            g3x_NormalVertex3dv(this, (3 * offset) + i * n1 + j);
        }
    }

    for (int i = 0; i < n1 - 1; i += step1) {
        iNext = min(i + step1, n1 - 1);
        for (int j = 0; j < n1 - 1; j += step2) {
            jNext = min(j + step2, n1 - 1);
            g3x_NormalVertex3dv(this, (4 * offset) + iNext * n1 + j);
            g3x_NormalVertex3dv(this, (4 * offset) + iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, (4 * offset) + i * n1 + jNext);
            g3x_NormalVertex3dv(this, (4 * offset) + i * n1 + j);

            g3x_NormalVertex3dv(this, (5 * offset) + i * n1 + j);
            g3x_NormalVertex3dv(this, (5 * offset) + i * n1 + jNext);
            g3x_NormalVertex3dv(this, (5 * offset) + iNext * n1 + jNext);
            g3x_NormalVertex3dv(this, (5 * offset) + iNext * n1 + j);
        }
    }
    glEnd();
}

void updateCubeScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= x;
    ((Node *) node)->scaleFactor.y *= y;
    ((Node *) node)->scaleFactor.z *= z;
}

Shape *createCube(int n1) {
    Shape *cube;
    if ((cube = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for cube\n");
        return NULL;
    }

    if ((cube->vertexes = malloc(sizeof(G3Xpoint) * n1 * n1 * 6)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for cube\n");
        return NULL;
    }
    if ((cube->normals = malloc(sizeof(G3Xvector) * n1 * n1 * 6)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for cube\n");
        return NULL;
    }

    double d = 2. / (n1 - 1);
    int offset = n1 * n1;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            // X axis
            cube->vertexes[i * n1 + j] = (G3Xpoint) {1, i * d - 1, j * d - 1};
            cube->normals[i * n1 + j] = (G3Xvector) {1, 0, 0};
            cube->vertexes[offset + i * n1 + j] = (G3Xpoint) {-1, i * d - 1, j * d - 1};
            cube->normals[offset + i * n1 + j] = (G3Xvector) {-1, 0, 0};

            // Y axis
            cube->vertexes[(2 * offset) + i * n1 + j] = (G3Xpoint) {i * d - 1, 1, j * d - 1};
            cube->normals[(2 * offset) + i * n1 + j] = (G3Xvector) {0, 1, 0};
            cube->vertexes[(3 * offset) + i * n1 + j] = (G3Xpoint) {i * d - 1, -1, j * d - 1};
            cube->normals[(3 * offset) + i * n1 + j] = (G3Xvector) {0, -1, 0};

            // Z axis
            cube->vertexes[(4 * offset) + i * n1 + j] = (G3Xpoint) {i * d - 1, j * d - 1, 1};
            cube->normals[(4 * offset) + i * n1 + j] = (G3Xvector) {0, 0, 1};
            cube->vertexes[(5 * offset) + i * n1 + j] = (G3Xpoint) {i * d - 1, j * d - 1, -1};
            cube->normals[(5 * offset) + i * n1 + j] = (G3Xvector) {0, 0, -1};
        }
    }

    cube->n1 = n1;
    cube->drawFaces = drawCubeFaces;
    cube->drawPoints = drawCubePoints;
    cube->updateScale = updateCubeScale;
    return cube;
}
