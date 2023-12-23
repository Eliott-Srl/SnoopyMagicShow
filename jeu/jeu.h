#ifndef TEST_JEU_H
#define TEST_JEU_H

#include "gestionTemps.h"
#include "conio.h"
#include "../utils/matrice.h"
#include "../utils/types.h"
#include "../files/files.h"

void bougerBalle(Niveau *niveau, int *vies);
int actionsBlock(Niveau *niveau, int directionX, int directionY, int *vies);
void pauseGame(Niveau *iveau);
void mouvement(Niveau *niveau, Jeu *gameHolder, int *vies, int touche);
void motdepasse(int *niveau, int *jeulanch, int *jeufini, int *score);
void jeu();

#endif //TEST_JEU_H
