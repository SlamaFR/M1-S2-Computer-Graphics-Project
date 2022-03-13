#include <math.h>

#include "cylinder.h"
#include "../utils.h"
#include "../trees/node.h"

void drawCylinderPoints(struct shape__s_ *this, G3Xvector scale) {
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
            g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3 + j);
        }
    }
    glEnd();
}

void drawCylinderFaces(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;
    int n3 = this->n3;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;
    int step3 = scale.z > 0 ? 1. / scale.z : 1;

    int offset = n1 * n2;
    glBegin(GL_QUADS);
    for (int i = 0; i < n1 - 1; i += step1) {
        for (int j = 0; j < n2 - 1; j += step2) {
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, i * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + j);
        }

        for (int j = step3; j < n3 - 1; j += step3) {
            g3x_NormalVertex3dv(this, offset + i * n3 + j);
            g3x_NormalVertex3dv(this, offset + i * n3 + min(j + step3, n3 - 1));
            g3x_NormalVertex3dv(this, offset + min(i + step1, n1 - 1) * n3 + min(j + step3, n3 - 1));
            g3x_NormalVertex3dv(this, offset + min(i + step1, n1 - 1) * n3 + j);

            g3x_NormalVertex3dv(this, offset + (n1 * n3) + min(i + step1, n1 - 1) * n3 + j);
            g3x_NormalVertex3dv(this, offset + (n1 * n3) + min(i + step1, n1 - 1) * n3 + min(j + step3, n3 - 1));
            g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3 + min(j + step3, n3 - 1));
            g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3 + j);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n1 - 1; i += step1) {
        g3x_NormalVertex3dv(this, offset + i * n3);
        g3x_NormalVertex3dv(this, offset + i * n3 + min(step3, n3 - 1));
        g3x_NormalVertex3dv(this, offset + min(i + step1, n1 - 1) * n3 + min(step3, n3 - 1));

        g3x_NormalVertex3dv(this, offset + i * n3);
        g3x_NormalVertex3dv(this, offset + min(i + step1, n1 - 1) * n3 + min(step3, n3 - 1));
        g3x_NormalVertex3dv(this, offset + min(i + step1, n1 - 1) * n3);


        g3x_NormalVertex3dv(this, offset + (n1 * n3) + min(i + step1, n1 - 1) * n3 + min(step3, n3 - 1));
        g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3 + min(step3, n3 - 1));
        g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3);

        g3x_NormalVertex3dv(this, offset + (n1 * n3) + min(i + step1, n1 - 1) * n3);
        g3x_NormalVertex3dv(this, offset + (n1 * n3) + min(i + step1, n1 - 1) * n3 + min(step3, n3 - 1));
        g3x_NormalVertex3dv(this, offset + (n1 * n3) + i * n3);
    }
    glEnd();
}

void updateCylinderScale(void *node, double x, double y, double z) {
    ((Node *) node)->scaleFactor.x *= fmin(fmax(x, y), 1);
    ((Node *) node)->scaleFactor.y *= fmin(z, 1);
    ((Node *) node)->scaleFactor.z *= fmin(fmax(x, y), 1);
}

G3Xvector applyCylinderScale(void *node, double x, double y, double z) {
    return (G3Xvector) {
        x / ((Node *) node)->scaleFactor.x,
        y / ((Node *) node)->scaleFactor.x,
        z / ((Node *) node)->scaleFactor.y
    };
}

Shape *createCylinder(int n1, int n2, int n3) {
    double theta = 2 * PI / (n1 - 1);

    Shape *cylinder;
    if ((cylinder = malloc(sizeof(Shape))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }

    if ((cylinder->vertexes = malloc(sizeof(G3Xpoint) * (n1 * n2 + 2 * (n1 * n3)))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }
    if ((cylinder->normals = malloc(sizeof(G3Xvector) * (n1 * n2 + 2 * (n1 * n3)))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for torus\n");
        return NULL;
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            cylinder->vertexes[i * n2 + j] = (G3Xpoint) {cos(i * theta), sin(i * theta), j * (2. / (n2 - 1)) - 1};
            cylinder->normals[i * n2 + j] = (G3Xvector) {cos(i * theta), sin(i * theta), 0};
        }
    }

    int offset = n1 * n2;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n3; j++) {
            cylinder->vertexes[offset + i * n3 + j] = (G3Xpoint) {cos(i * theta) * j * (1. / (n3 - 1)),
                                                                  sin(i * theta) * j * (1. / (n3 - 1)),
                                                                  1};
            cylinder->normals[offset + i * n3 + j] = (G3Xvector) {0, 0, 1};

            cylinder->vertexes[offset + (n1 * n3) + i * n3 + j] = (G3Xpoint) {cos(i * theta) * j * (1. / (n3 - 1)),
                                                                              sin(i * theta) * j * (1. / (n3 - 1)),
                                                                              -1};
            cylinder->normals[offset + (n1 * n3) + i * n3 + j] = (G3Xvector) {0, 0, -1};
        }
    }

    cylinder->n1 = n1;
    cylinder->n2 = n2;
    cylinder->n3 = n3;
    cylinder->drawFaces = drawCylinderFaces;
    cylinder->drawPoints = drawCylinderPoints;
    cylinder->updateScale = updateCylinderScale;
    cylinder->applyScale3d = applyCylinderScale;
    return cylinder;
}
