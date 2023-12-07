#ifndef TEST_JEU_H
#define TEST_JEU_H

#include "gestionTemps.h"
#include "conio.h"
#include "../utils/matrice.h"
#include "../utils/types.h"
#include "../files/files.h"

void pauseGame(s_Niveau *iveau);
void mouvement(s_Niveau *niveau, int touche);
void jeu();

#endif //TEST_JEU_H
