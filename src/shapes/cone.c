#include <math.h>

#include "../../include/shapes/cone.h"
#include "../../include/utils.h"
#include "../../include/trees/node.h"

void drawConePoints(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;
    int n3 = this->n3;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;
    int step3 = scale.z > 0 ? 1. / scale.z : 1;

    int offset = n1 * n2;
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < n1; i += step1) {
        for (int j = 0; j < n2; j += step2) {
            g3x_NormalVertex3dv(this, i * n2 + j);
        }
        for (int j = 0; j < n3; j += step3) {
            g3x_NormalVertex3dv(this, offset + i * n3 + j);
        }
    }
    glEnd();
}

void drawConeFaces(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;
    int n3 = this->n3;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;
    int step3 = scale.z > 0 ? 1. / scale.z : 1;

    int offset = n1 * n2;
    glBegin(GL_QUADS);
    int iNext, jNext;
    for (int i = 0; i < n1 - 1; i += step1) {
        iNext = min(i + step1, n1 - 1);
        for (int j = 0; j < n2 - 1; j += step2) {
            jNext = min(j + step2, n2 - 1);
            g3x_NormalVertex3dv(this, iNext * n2 + jNext);
            g3x_NormalVertex3dv(this, i * n2 + jNext);
            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, iNext * n2 + j);
        }

        for (int j = step3; j < n3 - 1; j += step3) {
            jNext = min(j + step3, n3 - 1);
            g3x_NormalVertex3dv(this, offset + iNext * n3 + j);
            g3x_NormalVertex3dv(this, offset + iNext * n3 + jNext);
            g3x_NormalVertex3dv(this, offset + i * n3 + jNext);
            g3x_NormalVertex3dv(this, offset + i * n3 + j);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n1 - 1; i += step1) {
        iNext = min(i + step1, n1 - 1);
        jNext = min(step3, n3 - 1);
        g3x_NormalVertex3dv(this, offset + iNext * n3 + jNext);
        g3x_NormalVertex3dv(this, offset + i * n3 + jNext);
        g3x_NormalVertex3dv(this, offset + i * n3);

        g3x_NormalVertex3dv(this, offset + iNext * n3);
        g3x_NormalVertex3dv(this, offset + iNext * n3 + jNext);
        g3x_NormalVertex3dv(this, offset + i * n3);
    }
    glEnd();
}

void updateConeScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmax(x, y);
    ((Node *) node)->scaleFactor.y *= z;
    ((Node *) node)->scaleFactor.z *= fmax(x, y);
}

Shape *createCone(int n1, int n2, int n3) {
    double theta = 2 * PI / (n1 - 1);

    Shape *cone;
    if ((cone = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        exit(-1);
    }

    if ((cone->vertexes = malloc(sizeof(G3Xpoint) * (n1 * n2 + n1 * n3))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        exit(-1);
    }
    if ((cone->normals = malloc(sizeof(G3Xvector) * (n1 * n2 + n1 * n3))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        exit(-1);
    }

    int offset = n1 * n2;
    double cosTheta, sinTheta;
    for (int i = 0; i < n1; i++) {
        cosTheta = cos(i * theta);
        sinTheta = sin(i * theta);
        for (int j = 0; j < n2; j++) {
            double t = j * (2. / (n2 - 1)) - 1;
            cone->vertexes[i * n2 + j] = (G3Xpoint) {
                    (1 - t) / 2. * cosTheta,
                    (1 - t) / 2. * sinTheta,
                    t
            };
            cone->normals[i * n2 + j] = (G3Xvector) {cosTheta, sinTheta, 1};
        }
        for (int j = 0; j < n3; j++) {
            cone->vertexes[offset + i * n3 + j] = (G3Xpoint) {
                    cosTheta * j * (1. / (n3 - 1)),
                    sinTheta * j * (1. / (n3 - 1)),
                    -1
            };
            cone->normals[offset + i * n3 + j] = (G3Xvector) {0, 0, -1};
        }
    }

    cone->n1 = n1;
    cone->n2 = n2;
    cone->n3 = n3;
    cone->drawFaces = drawConeFaces;
    cone->drawPoints = drawConePoints;
    cone->updateScale = updateConeScale;
    return cone;
}
