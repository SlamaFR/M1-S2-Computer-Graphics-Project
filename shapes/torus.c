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
    for (int i = 0; i < n1 - 1; i += step1) {
        for (int j = 0; j < n2 - 1; j += step2) {
            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, i * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + j);
        }
    }
    glEnd();
}

void updateTorusScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmin(fmax(x, y), 1);
    ((Node *) node)->scaleFactor.y *= fmin(fmax(fmax(x, y), z), 1);
}

G3Xvector applyTorusScale(void *node, double x, double y, double z) {
    return (G3Xvector) {
            x / ((Node *) node)->scaleFactor.x,
            y / ((Node *) node)->scaleFactor.x,
            z / ((Node *) node)->scaleFactor.y
    };
}

Shape *createTorus(int n1, int n2) {
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
            torus->vertexes[i * n2 + j] = (G3Xpoint) {cos(i * theta) * (1 + .5 * cos(j * phi)),
                                                      -sin(i * theta) * (1 + .5 * cos(j * phi)),
                                                      .5 * sin(j * phi)};
            torus->normals[i * n2 + j] = (G3Xvector) {cos(i * theta) * cos(j * phi),
                                                      -sin(i * theta) * cos(j * phi),
                                                      sin(j * phi)};
        }
    }

    torus->n1 = n1;
    torus->n2 = n2;
    torus->drawFaces = drawTorusFaces;
    torus->drawPoints = drawTorusPoints;
    torus->updateScale = updateTorusScale;
    torus->applyScale3d = applyTorusScale;
    return torus;
}
