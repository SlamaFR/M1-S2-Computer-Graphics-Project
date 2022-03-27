#include <math.h>

#include "torus.h"
#include "../utils.h"
#include "../trees/node.h"

void drawTorusPoints(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;

    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < n1 - 1; i += step1) {
        for (int j = 0; j < n2 - 1; j += step2) {
            g3x_NormalVertex3dv(this, i * n2 + j);
        }
    }
    glEnd();
}

void drawTorusFaces(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;

    glBegin(GL_QUADS);
    int iNext, jNext;
    for (int i = 0; i < n1 - 1; i += step1) {
        iNext = min(i + step1, n1 - 1);
        for (int j = 0; j < n2 - 1; j += step2) {
            jNext = min(j + step2, n2 - 1);
            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, i * n2 + jNext);
            g3x_NormalVertex3dv(this, iNext * n2 + jNext);
            g3x_NormalVertex3dv(this, iNext * n2 + j);
        }
    }
    glEnd();
}

void updateTorusScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmax(x, y);
    ((Node *) node)->scaleFactor.y *= fmax(fmax(x, y), z);
}

Shape *createTorus(int n1, int n2, double r1, double r2) {
    double theta = 2 * PI / (n1 - 1);
    double phi = 2 * PI / (n2 - 1);
    Shape *torus;

    if ((torus = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }

    if ((torus->vertexes = malloc(sizeof(G3Xpoint) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }
    if ((torus->normals = malloc(sizeof(G3Xvector) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            torus->vertexes[i * n2 + j] = (G3Xpoint) {
                    cos(i * theta) * ((r1 + r2) + r2 * cos(j * phi)),
                    -sin(i * theta) * ((r1 + r2) + r2 * cos(j * phi)),
                    r2 * sin(j * phi)
            };
            torus->normals[i * n2 + j] = (G3Xvector) {
                    cos(i * theta) * cos(j * phi),
                    -sin(i * theta) * cos(j * phi),
                    sin(j * phi)
            };
        }
    }

    torus->n1 = n1;
    torus->n2 = n2;
    torus->drawFaces = drawTorusFaces;
    torus->drawPoints = drawTorusPoints;
    torus->updateScale = updateTorusScale;
    return torus;
}
