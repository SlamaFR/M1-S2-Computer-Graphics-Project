#include <assert.h>
#include "../../include/trees/node.h"

void propagateScale(Node *node, double x, double y, double z, int sibling) {
    if (node == NULL) return;
    if (node->instance != NULL) {
        node->instance->updateScale((Node *) node, x, y, z);
    } else {
        node->scaleFactor.x *= x;
        node->scaleFactor.y *= y;
        node->scaleFactor.z *= z;
    }
    if (node->child) {
        propagateScale(node->child, x, y, z, 1);
    }
    if (node->sibling && sibling == 1) {
        propagateScale(node->sibling, x, y, z, 1);
    }
}

Node *applyTransformMatrix(Node *node, G3Xhmat matrix) {
    node->transformMatrix = g3x_Mat_x_Mat(matrix, node->transformMatrix);
    return node;
}

Node *applyTranslation3d(Node *node, double x, double y, double z) {
    applyTransformMatrix(node, g3x_Translation3d(x, y, z));
    return node;
}

Node *applyRotation(Node *node, G3Xhmat rotation) {
    applyTransformMatrix(node, rotation);
    return node;
}

Node *applyHomothety3d(Node *node, double x, double y, double z) {
    propagateScale(node, x, y, z, 0);
    applyTransformMatrix(node, g3x_Homothetie3d(x, y, z));
    return node;
}

void inheritProperties(Node *ancester, Node *descendant) {
    memcpy(descendant->material, ancester->material, 4 * sizeof(float));
    descendant->color = ancester->color;
    propagateScale(descendant, ancester->scaleFactor.x, ancester->scaleFactor.y, ancester->scaleFactor.z, 0);
}

void addSibling(Node *node, Node *sibling) {
    assert(node != NULL);
    if (sibling == NULL) return;

    sibling->sibling = node->sibling;
    node->sibling = sibling;
}

void addChild(Node *node, Node *child) {
    assert(node != NULL);
    if (child == NULL) return;

    if (node->child == NULL) {
        node->child = child;
    } else {
        addSibling(node->child, child);
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
