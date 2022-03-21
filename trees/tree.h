#pragma once

#include "node.h"

/**
 * Recursively draw a scene tree.
 * <p>
 * This method takes into account distance to camera to compute
 * adapted scale factor so that furthest shapes are less detailed
 * than closest ones.
 */
void drawTree(SceneTree tree);
