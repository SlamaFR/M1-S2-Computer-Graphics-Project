#include "tree.h"

void drawTree(SceneTree tree) {
    if (tree == NULL) return;
    g3x_Material(tree->color, tree->material[0], tree->material[1], tree->material[2], tree->material[3], 1);
    glPushMatrix();
    glMultMatrixd(tree->transformMatrix.m);
    if (tree->instance != NULL) {
        /* Adaptative resolution computations */

        // Retrieving final shape location
        GLdouble matrixd[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, matrixd);
        G3Xpoint shapePos = {matrixd[12], matrixd[13], matrixd[14]};

        // Considering camera at (0, 0, 0) eye-coordinates.
        G3Xpoint camPos = {0, 0, 0};

        // Weighted scale factor accordingly to distance to camera.
        G3Xvector scaleFactor = {
                fmin(1., 5. / g3x_Dist(camPos, shapePos)) * tree->scaleFactor.x,
                fmin(1., 5. / g3x_Dist(camPos, shapePos)) * tree->scaleFactor.y,
                fmin(1., 5. / g3x_Dist(camPos, shapePos)) * tree->scaleFactor.z
        };

        // Drawing shape with adapted scale factor.
        tree->instance->drawFaces(tree->instance, scaleFactor);
    }
    drawTree(tree->child);
    glPopMatrix();
    drawTree(tree->sibling);
}