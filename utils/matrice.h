#ifndef TEST_MATRICE_H
#define TEST_MATRICE_H

#include "utils.h"
#include <time.h>
#include <stdio.h>
#include "../jeu/gestionTemps.h"
#include "../jeu/jeu.h"
#include "../utils/types.h"

#define COULEUR 1

void initialiseMatrice(Niveau *niveau);
void afficherMatrice(Niveau *niveau);

#endif //TEST_MATRICE_H
