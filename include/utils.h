#pragma once

#include <g3x.h>
#include "shapes/shapes.h"

#define assertThat(e) for(; !(e); assert(e))

int min(int a, int b);

int max(int a, int b);

void g3x_NormalVertex3dv(Shape *shape, int i);
