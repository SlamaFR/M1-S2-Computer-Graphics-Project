#pragma once

#include "shapes.h"

/**
 * Create a sphere.
 *
 * @param n1 Number of meridians
 * @param n2 Number of parallels
 * @param r1 Radius of inner circle
 * @param r2 Radius of ring
 * @return Created sphere shape
 */
Shape *createTorus(int n1, int n2, double r1, double r2);
