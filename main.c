#include <math.h>
#include <g3x.h>

#include "shapes/sphere.h"
#include "shapes/torus.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/cube.h"

#include "trees/node.h"
#include "trees/tree.h"

#include "scenes/tables.h"
#include "scenes/pillarsway.h"

// Window size in pixels
static int WWIDTH = 1024, WHEIGHT = 1024;

Shape *sphere;
Shape *cone;
Shape *torus;
Shape *cylinder;
Shape *cube;

SceneTree scene;
G3Xvector scale = {1, 1, 1};

/* Init function, called once at the beginning */
static void init(void) {
    sphere = createSphere(PI * MAXRES, PI * MAXRES / 2);
    cone = createCone(PI * MAXRES, MAXRES, MAXRES / 2);
    torus = createTorus((3 * PI / 2) * MAXRES, PI * MAXRES / 2, 1., .5);
    cylinder = createCylinder(PI * MAXRES, MAXRES, MAXRES / 2);
    cube = createCube(MAXRES);

    static float mat[4] = {.3, .9, .6, 1};
    scene = createRoot(mat, G3Xb, g3x_Identity(), (G3Xvector) {1, 1, 1});

    initPillarsWay();
    addChild(scene, getPillarsWay(20));
    applyTranslation3d(scene, 0, -1, -.5);
    sanitizeHomothety(scene);
}

/* Draw function, called in mail loop */
static void draw(void) {
    drawTree(scene);
    glEnable(GL_CULL_FACE);
}

/* Exit function, called at the end of the program */
static void quit(void) {
    freeShape(&sphere);
    freeShape(&cone);
    freeShape(&torus);
    freeShape(&cylinder);
    freeShape(&cube);
    freeTree(&scene);
    freePillarsWay();
}

int main(int argc, char **argv) {
    // Window creation
    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);

    // Initialization function
    g3x_SetInitFunction(init);
    // Draw function
    g3x_SetDrawFunction(draw);
    // Exit function
    g3x_SetExitFunction(quit);

    // Main loop
    return g3x_MainStart();
}
