#include <assert.h>
#include "node.h"

void applyTransformMatrix(Node *node, G3Xhmat matrix) {
    node->transformMatrix = g3x_Mat_x_Mat(matrix, node->transformMatrix);
}

void applyTranslation3d(Node *node, double x, double y, double z) {
    applyTransformMatrix(node, g3x_Translation3d(x, y, z));
}

void applyTranslation1v(Node *node, G3Xvector vector) {
    applyTransformMatrix(node, g3x_Translation1v(vector));
}

void applyRotation(Node *node, G3Xhmat rotation) {
    applyTransformMatrix(node, rotation);
}

void applyHomothety3d(Node *node, double x, double y, double z) {
    if (node->instance != NULL) {
        node->instance->update_scale((Node *) node, x, y, z);
    }
    applyTransformMatrix(node, g3x_Homothetie3d(x, y, z));
}

void applyHomothety1v(Node *node, G3Xvector homothety) {
    if (node->instance != NULL) {
        node->instance->update_scale((Node *) node, homothety.x, homothety.y, homothety.z);
    }
    applyTransformMatrix(node, g3x_Homothetie1v(homothety));
}

void inheritProperties(Node *ancester, Node *descendant) {
    memcpy(descendant->material, ancester->material, 4 * sizeof(float));
    descendant->color = ancester->color;
    descendant->scaleFactor.x *= ancester->scaleFactor.x;
    descendant->scaleFactor.y *= ancester->scaleFactor.y;
    descendant->scaleFactor.z *= ancester->scaleFactor.z;
}

void addSibling(Node *node, Node *sibling) {
    assert(node != NULL);
    if (sibling == NULL) return;

    for (; node->sibling; node = node->sibling);
    node->sibling = sibling;
}

void addChild(Node *node, Node *child) {
    assert(node != NULL);
    if (child == NULL) return;

    applyTransformMatrix(child, node->transformMatrix);
    if (node->child == NULL) {
        node->child = child;
    } else {
        addSibling(node, child);
    }
    inheritProperties(node, child);
}

SceneTree createRoot(float *material, G3Xcolor color, G3Xhmat transformMatrix, G3Xvector scaleFactor) {
    Node *root;

    if ((root = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for masterTree root\n");
        exit(-1);
    }

    memcpy(root->material, material, 4 * sizeof(float));
    root->color = color;
    root->transformMatrix = transformMatrix;
    root->scaleFactor = scaleFactor;
    root->sibling = NULL;
    root->child = NULL;
    root->instance = NULL;
    return root;
}

Node *createNode() {
    Node *node;

    if ((node = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Failed to allocate memory for masterTree node\n");
        exit(-1);
    }

    node->transformMatrix = g3x_Identity();
    node->scaleFactor = (G3Xvector) {1, 1, 1};
    node->sibling = NULL;
    node->child = NULL;
    node->instance = NULL;
    return node;
}

Node *createLeaf(Shape *shape) {
    Node *leaf = createNode();
    leaf->instance = shape;
    return leaf;
}
