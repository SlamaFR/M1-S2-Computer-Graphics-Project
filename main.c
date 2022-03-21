/*=================================================================*/
/*= E.Incerti - eric.incerti@univ-eiffel.fr                       =*/
/*= Université Gustave Eiffel                                     =*/
/*= Code "squelette" pour prototypage avec libg3x.6c              =*/
/*=================================================================*/

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

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 1024, WHEIGHT = 1024;

Shape *sphere;
Shape *cone;
Shape *torus;
Shape *cylinder;
Shape *cube;

SceneTree scene;
G3Xvector scale = {1, 1, 1};

/* la fonction d'initialisation : appelée 1 seule fois, au début */
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

}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void) {}

/* la fonction de dessin : appelée en boucle */
static void draw(void) {
    drawTree(scene);
    glEnable(GL_CULL_FACE);
}

/* la fonction d'animation (facultatif) */
static void anim(void) {
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void) {
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS ou presque                    */
/***************************************************************************/
int main(int argc, char **argv) {
    /* creation de la fenetre - titre et tailles (pixels) */
    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);

    g3x_SetInitFunction(init); /* fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}
