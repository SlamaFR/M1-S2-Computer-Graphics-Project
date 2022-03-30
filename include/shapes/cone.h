#pragma once

#include "shapes.h"

/**
 * Create a cone.
 *
 * @param n1 Number of meridians
 * @param n2 Number of parallels
 * @param n3 Number of discs on base
 * @return Created cone shape
 */
Shape *createCone(int n1, int n2, int n3);
