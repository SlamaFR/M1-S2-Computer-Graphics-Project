#include "../../include/scenes/tables.h"

extern Shape *cube;
extern Shape *cylinder;

SceneTree getFloor(Material mat) {
    SceneTree floor = createNode();
    memcpy(floor->material, mat, 4 * sizeof(float));
    applyHomothety3d(floor, 1, 1, .01);
    Node *grayTiles = createNode();
    Node *whiteTiles = createNode();
    addChild(floor, grayTiles);
    addChild(floor, whiteTiles);
    grayTiles->color = G3Xwb;
    whiteTiles->color = G3Xw;

    addChild(grayTiles, applyTranslation3d(createLeaf(cube), -1, -1, 0));
    addChild(grayTiles, applyTranslation3d(createLeaf(cube), 1, 1, 0));

    addChild(whiteTiles, applyTranslation3d(createLeaf(cube), -1, 1, 0));
    addChild(whiteTiles, applyTranslation3d(createLeaf(cube), 1, -1, 0));

    return floor;
}

SceneTree getRoundTable(Material mat) {
    SceneTree table = createNode();
    memcpy(table->material, mat, 4 * sizeof(float));

    Node *plate = createLeaf(cylinder);
    addChild(table, plate);
    applyHomothety3d(plate, 1, 1, .05);
    applyTranslation3d(plate, 0, 0, 1);
    plate->color = (G3Xcolor) {.38, .27, .22, 0};

    Node *feet = createNode();
    addChild(table, feet);
    applyTranslation3d(feet, 0, 0, .5);
    feet->color = (G3Xcolor) {.43, .37, .26, 0};

    Node *foot1 = createLeaf(cube);
    addChild(feet, foot1);
    applyHomothety3d(foot1, .06, .06, .5);
    applyTranslation3d(foot1, .55, .55, 0);
    Node *foot2 = createLeaf(cube);
    addChild(feet, foot2);
    applyHomothety3d(foot2, .06, .06, .5);
    applyTranslation3d(foot2, -.55, .55, 0);
    Node *foot3 = createLeaf(cube);
    addChild(feet, foot3);
    applyHomothety3d(foot3, .06, .06, .5);
    applyTranslation3d(foot3, -.55, -.55, 0);
    Node *foot4 = createLeaf(cube);
    addChild(feet, foot4);
    applyHomothety3d(foot4, .06, .06, .5);
    applyTranslation3d(foot4, .55, -.55, 0);

    return table;
}

SceneTree getSquareTable(Material mat) {
    SceneTree table = createNode();
    memcpy(table->material, mat, 4 * sizeof(float));

    Node *plate = createLeaf(cube);
    addChild(table, plate);
    applyHomothety3d(plate, 1, .5, .05);
    applyTranslation3d(plate, 0, 0, 1);
    plate->color = (G3Xcolor) {.44, .31, .20, 0};

    Node *feet = createNode();
    addChild(table, feet);
    applyTranslation3d(feet, 0, 0, .5);
    feet->color = (G3Xcolor) {.49, .50, .56, 0};

    Node *foot1 = createLeaf(cylinder);
    addChild(feet, foot1);
    applyHomothety3d(foot1, .075, .075, .5);
    applyTranslation3d(foot1, .9, .4, 0);
    Node *foot2 = createLeaf(cylinder);
    addChild(feet, foot2);
    applyHomothety3d(foot2, .075, .075, .5);
    applyTranslation3d(foot2, -.9, .4, 0);
    Node *foot3 = createLeaf(cylinder);
    addChild(feet, foot3);
    applyHomothety3d(foot3, .075, .075, .5);
    applyTranslation3d(foot3, -.9, -.4, 0);
    Node *foot4 = createLeaf(cylinder);
    addChild(feet, foot4);
    applyHomothety3d(foot4, .075, .075, .5);
    applyTranslation3d(foot4, .9, -.4, 0);

    return table;
}

SceneTree getTablesScene() {
    static float mat[4] = {.3, .9, .6, 1};
    SceneTree scene = createRoot(mat, G3Xb, g3x_Identity(), (G3Xvector) {1, 1, 1});

    SceneTree objects = createNode();
    applyHomothety3d(objects, .75, .75, .75);

    Node *table1 = getSquareTable(mat);
    applyRotation(table1, g3x_RotationZ(-PI / 3));
    applyTranslation3d(table1, 1.33, 1.33, 0);
    addChild(objects, table1);

    Node *table2 = getSquareTable(mat);
    applyRotation(table2, g3x_RotationZ(4 * PI / 5));
    applyTranslation3d(table2, -1.33, 1.33, 0);
    addChild(objects, table2);

    Node *table3 = getRoundTable(mat);
    applyHomothety3d(table3, .75, .75, 1);
    applyRotation(table3, g3x_RotationZ(PI / 4));
    applyTranslation3d(table3, 1, -1, 0);
    addChild(objects, table3);

    Node *table4 = getRoundTable(mat);
    applyHomothety3d(table4, .75, .75, 1);
    applyRotation(table4, g3x_RotationZ(-20 * PI / 21));
    applyRotation(table4, g3x_RotationX(PI));
    applyTranslation3d(table4, 0, 0, 2.1);
    applyTranslation3d(table4, 1.2, .8, 0);
    addChild(objects, table4);

    addChild(scene, getFloor(mat));
    addChild(scene, objects);
    return scene;
}
