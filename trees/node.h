#pragma once

#include "../shapes/shapes.h"
#include <g3x.h>

/**
 * Array of 4 floats between 0 and 1 for ambiant light, specularity, diffusion and shine.
 */
typedef float Material[4];

typedef struct node__s_ {
    struct node__s_ *child, *sibling;
    Material material;
    G3Xcolor color;
    G3Xhmat transformMatrix;
    G3Xvector scaleFactor;
    Shape *instance;
} Node, *SceneTree;

Node *applyTranslation3d(Node *node, double x, double y, double z);

Node *applyRotation(Node *node, G3Xhmat rotation);

Node *applyHomothety3d(Node *node, double x, double y, double z);

Node *applyTransformMatrix(Node *node, G3Xhmat matrix);

void addSibling(Node *node, Node *sibling);

void addChild(Node *node, Node *child);

SceneTree createRoot(Material material, G3Xcolor color, G3Xhmat transformMatrix, G3Xvector scaleFactor);

Node *createNode();

Node *createLeaf(Shape *shape);

