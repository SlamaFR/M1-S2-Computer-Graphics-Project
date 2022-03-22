#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "pillarsway.h"
#include "../shapes/torus.h"
#include "../utils.h"

extern Shape *sphere;
extern Shape *cylinder;
extern Shape *cube;

static Shape *torus;
static int initialized = 0;

void initPillarsWay() {
    assertThat(!initialized) {
        fprintf(stderr, "Pillars way scene is already initialized\n");
    }
    torus = createTorus((3 * PI / 2) * MAXRES, PI * MAXRES / 2, 1., .25);
    sranddev();
    initialized = 1;
}

SceneTree getSpinningTop(Material mat) {
    assertThat(initialized) {
        fprintf(stderr, "Pillars way scene is not initialized\n");
    }
    SceneTree st = createNode();
    memcpy(st->material, mat, 4 * sizeof(float));
    st->color = G3Xwb;

    Node *ball = createLeaf(sphere);
    Node *ring = createLeaf(torus);
    Node *shaft = createLeaf(cylinder);

    applyHomothety3d(ball, .25, .25, .25);
    applyHomothety3d(ring, .25, .25, .25);
    applyHomothety3d(shaft, .04, .04, 1);
    applyTranslation3d(shaft, 0, 0, .5);

    addChild(st, ball);
    addChild(st, ring);
    addChild(st, shaft);
    return st;
}

SceneTree getRandomPillar(Material mat) {
    SceneTree pillar = createNode();
    memcpy(pillar->material, mat, 4 * sizeof(float));
    pillar->color = G3Xwb;

    Node *spinningTop = getSpinningTop(mat);
    applyRotation(spinningTop, g3x_RotationX(1 * PI / 17));
    applyRotation(spinningTop, g3x_RotationY(2 * PI / 20));
    applyTranslation3d(spinningTop, 0, 0, .4);
    applyHomothety3d(spinningTop, .3, .3, .3);
    applyTranslation3d(spinningTop, 0, 0, 1);

    Node *column = createLeaf(cylinder);
    applyHomothety3d(column, .1, .1, 1);

    Node *base = createLeaf(torus);
    applyHomothety3d(base, .75, .75, .75);
    applyHomothety3d(base, .1, .1, .1);
    applyTranslation3d(base, 0, 0, -1);

    Node *pedestal = createLeaf(cube);
    applyHomothety3d(pedestal, .4, .2, .125);
    applyTranslation3d(pedestal, 0, 0, -1.125);


    addChild(pillar, column);
    addChild(pillar, base);
    addChild(pillar, pedestal);
    addChild(pillar, spinningTop);

    int rotation = rand() % 100;
    applyRotation(spinningTop, g3x_RotationZ(rotation * PI / 50));

    return pillar;
}

SceneTree getPillarsWay(int n) {
    assert(n >= 1);
    SceneTree scene = createNode();
    float mat[4] = {.3, .9, .6, 1};

    Node *leftPillars = createNode();
    Node *rightPillars = createNode();
    applyTranslation3d(leftPillars, 0, -1, 0);
    applyTranslation3d(rightPillars, 0, 1, 0);

    Node *floor = createNode();
    memcpy(floor->material, mat, 4 * sizeof(float));
    applyHomothety3d(floor, 1, 1, .0625);
    applyTranslation3d(floor, 0, 0, -1.25 + .0625);

    for (int i = 0; i < n; i++) {
        Node *leftPillar = getRandomPillar(mat);
        Node *rightPillar = getRandomPillar(mat);
        applyTranslation3d(leftPillar, i * .8, 0, 0);
        applyTranslation3d(rightPillar, i * .8, 0, 0);
        addChild(leftPillars, leftPillar);
        addChild(rightPillars, rightPillar);

        Node *leftTile = createLeaf(cube);
        Node *rightTile = createLeaf(cube);
        applyHomothety3d(leftTile, .4, .4, 1);
        applyHomothety3d(rightTile, .4, .4, 1);
        applyTranslation3d(leftTile, i * .8, -.4, 0);
        applyTranslation3d(rightTile, i * .8, .4, 0);
        addChild(floor, leftTile);
        addChild(floor, rightTile);
        leftTile->color = i % 2 == 0 ? G3Xwb : G3Xwc;
        rightTile->color = i % 2 != 0 ? G3Xwb : G3Xwc;
    }

    addChild(scene, leftPillars);
    addChild(scene, rightPillars);
    addChild(scene, floor);

    applyTranslation3d(scene, (n - 1) * -.4, 0, 0);
    return scene;
}
