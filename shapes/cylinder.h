#pragma once

#include "shapes.h"

/**
 * Create a cylinder.
 *
 * @param n1 Number of meridians
 * @param n2 Number of parallels
 * @param n3 Number of discs on bases
 * @return Created cylinder shape
 */
Shape *createCylinder(int n1, int n2, int n3);
