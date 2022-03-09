#include "sphere.h"
#include "../utils.h"

void drawSpherePoints(struct shape__s_ *this, G3Xvector scale) {
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

void drawSphereFaces(struct shape__s_ *this, G3Xvector scale) {
    int n1 = this->n1;
    int n2 = this->n2;

    int step1 = scale.x > 0 ? 1. / scale.x : 1;
    int step2 = scale.y > 0 ? 1. / scale.y : 1;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n1 - 1; i += step1) {
        for (int j = 0; j < n2 - 1; j += step2) {
            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, i * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + min(j + step2, n2 - 1));

            g3x_NormalVertex3dv(this, i * n2 + j);
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + min(j + step2, n2 - 1));
            g3x_NormalVertex3dv(this, min(i + step1, n1 - 1) * n2 + j);
        }
    }

    for (int j = 0; j < n2 - 1; j += step2) {
        g3x_NormalVertex3dv(this, (n1 - 1) * n2 + j);
        g3x_NormalVertex3dv(this, (n1 - 1) * n2 + min(j + step2, n2 - 1));
        g3x_NormalVertex3dv(this, min(j + step2, n2 - 1));

        g3x_NormalVertex3dv(this, (n1 - 1) * n2 + j);
        g3x_NormalVertex3dv(this, min(j + step2, n2 - 1));
        g3x_NormalVertex3dv(this, j);
    }
    glEnd();
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
            sphere->vertexes[i * n2 + j].x = sphere->normals[i * n2 + j].x = cos(i * theta) * sin(j * phi);
            sphere->vertexes[i * n2 + j].y = sphere->normals[i * n2 + j].y = sin(i * theta) * sin(j * phi);
            sphere->vertexes[i * n2 + j].z = sphere->normals[i * n2 + j].z = cos(j * phi);
        }
    }

    sphere->n1 = n1;
    sphere->n2 = n2;
    sphere->draw_faces = drawSphereFaces;
    sphere->draw_points = drawSpherePoints;
    return sphere;
}
