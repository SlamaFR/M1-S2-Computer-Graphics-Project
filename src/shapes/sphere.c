#include <math.h>

#include "../../include/shapes/sphere.h"
#include "../../include/utils.h"
#include "../../include/trees/node.h"

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

void updateSphereScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmax(x, y);
    ((Node *) node)->scaleFactor.y *= fmax(fmax(x, y), z);
}

Shape *createSphere(int n1, int n2) {
    double theta = 2 * PI / (n1 - 1);
    double phi = PI / (n2 - 1);

    Shape *sphere;
    if ((sphere = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        exit(-1);
    }

    if ((sphere->vertexes = malloc(sizeof(G3Xpoint) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        exit(-1);
    }
    if ((sphere->normals = malloc(sizeof(G3Xvector) * n1 * n2)) == NULL) {
        fprintf(stderr, "Failed to allocate memory for sphere\n");
        exit(-1);
    }

    double cosTheta, sinTheta, cosPhi, sinPhi;
    for (int i = 0; i < n1; i++) {
        cosTheta = cos(i * theta);
        sinTheta = sin(i * theta);
        for (int j = 0; j < n2; j++) {
            cosPhi = cos(j * phi);
            sinPhi = sin(j * phi);
            sphere->vertexes[i * n2 + j] = (G3Xpoint) {cosTheta * sinPhi, sinTheta * sinPhi, cosPhi};
            sphere->normals[i * n2 + j] = (G3Xvector) {cosTheta * sinPhi, sinTheta * sinPhi, cosPhi};
        }
    }

    sphere->n1 = n1;
    sphere->n2 = n2;
    sphere->drawFaces = drawSphereFaces;
    sphere->drawPoints = drawSpherePoints;
    sphere->updateScale = updateSphereScale;
    return sphere;
}
