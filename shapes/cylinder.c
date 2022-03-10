#include "cylinder.h"
#include "../utils.h"

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

    for (int j = 0; j < n2 - 1; j += step2) {
        g3x_NormalVertex3dv(this, min(j + step2, n2 - 1));
        g3x_NormalVertex3dv(this, (n1 - 1) * n2 + min(j + step2, n2 - 1));
        g3x_NormalVertex3dv(this, (n1 - 1) * n2 + j);
        g3x_NormalVertex3dv(this, j);
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
            cylinder->vertexes[i * n2 + j].x = cos(i * theta);
            cylinder->vertexes[i * n2 + j].y = sin(i * theta);
            cylinder->vertexes[i * n2 + j].z = j * (2. / (n2 - 1)) - 1;
            cylinder->normals[i * n2 + j].x = cos(i * theta);
            cylinder->normals[i * n2 + j].y = sin(i * theta);
            cylinder->normals[i * n2 + j].z = 0;
        }
    }

    int offset = n1 * n2;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n3; j++) {
            cylinder->vertexes[offset + i * n3 + j].x = cos(i * theta) * j * (1. / (n3 - 1));
            cylinder->vertexes[offset + i * n3 + j].y = sin(i * theta) * j * (1. / (n3 - 1));
            cylinder->vertexes[offset + i * n3 + j].z = 1;
            cylinder->normals[offset + i * n3 + j].x = 0;
            cylinder->normals[offset + i * n3 + j].y = 0;
            cylinder->normals[offset + i * n3 + j].z = 1;

            cylinder->vertexes[offset + (n1 * n3) + i * n3 + j].x = cos(i * theta) * j * (1. / (n3 - 1));
            cylinder->vertexes[offset + (n1 * n3) + i * n3 + j].y = sin(i * theta) * j * (1. / (n3 - 1));
            cylinder->vertexes[offset + (n1 * n3) + i * n3 + j].z = -1;
            cylinder->normals[offset + (n1 * n3) + i * n3 + j].x = 0;
            cylinder->normals[offset + (n1 * n3) + i * n3 + j].y = 0;
            cylinder->normals[offset + (n1 * n3) + i * n3 + j].z = -1;
        }
    }

    cylinder->n1 = n1;
    cylinder->n2 = n2;
    cylinder->n3 = n3;
    cylinder->draw_faces = drawCylinderFaces;
    cylinder->draw_points = drawCylinderPoints;
    return cylinder;
}
