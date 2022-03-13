#include <math.h>

#include "sphere.h"
#include "../utils.h"
#include "../trees/node.h"

void drawSpherePoints(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;

    int step1 = min(1, scale.x > 0 ? 1. / scale.x : 1);
    int step2 = min(1, scale.y > 0 ? 1. / scale.y : 1);

    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < n1 - 1; i += step1) {
        for (int j = 0; j < n2 - 1; j += step2) {
            g3x_NormalVertex3dv(this, i * n2 + j);
        }
    }
    glEnd();
}

void drawSphereFaces(struct shape__s_ *this, G3Xvector scale) {
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

void updateSphereScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmin(fmax(x, y), 1);
    ((Node *) node)->scaleFactor.y *= fmin(fmax(fmax(x, y), z), 1);
}

G3Xvector applySphereScale(void *node, double x, double y, double z) {
    return (G3Xvector) {
            x / ((Node *) node)->scaleFactor.x,
            y / ((Node *) node)->scaleFactor.x,
            z / ((Node *) node)->scaleFactor.y
    };
}

Shape *createSphere(int n1, int n2) {
    double theta = 2 * PI / (n1 - 1);
    double phi = PI / (n2 - 1);

    Shape *sphere;
    if ((sphere = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        return NULL;
    }

    if ((sphere->vertexes = malloc(sizeof(G3Xpoint) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        return NULL;
    }
    if ((sphere->normals = malloc(sizeof(G3Xvector) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        return NULL;
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            sphere->vertexes[i * n2 + j] = (G3Xpoint) {cos(i * theta) * sin(j * phi),
                                                       sin(i * theta) * sin(j * phi),
                                                       cos(j * phi)};
            sphere->normals[i * n2 + j] = (G3Xvector) {cos(i * theta) * sin(j * phi),
                                                       sin(i * theta) * sin(j * phi),
                                                       cos(j * phi)};
        }
    }

    sphere->n1 = n1;
    sphere->n2 = n2;
    sphere->drawFaces = drawSphereFaces;
    sphere->drawPoints = drawSpherePoints;
    sphere->updateScale = updateSphereScale;
    sphere->applyScale3d = applySphereScale;
    return sphere;
}
