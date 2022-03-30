#include "../../include/shapes/shapes.h"

void freeShape(Shape **shape) {
    free((*shape)->vertexes);
    free((*shape)->normals);
    free((*shape));
    *shape = NULL;
}
