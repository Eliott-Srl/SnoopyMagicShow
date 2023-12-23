#ifndef TEST_FILES_H
#define TEST_FILES_H

#include "../utils/types.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

void loadNiveau(Niveau *niveau);
void sauvegarderPartie(Jeu *jeu, Niveau *niveau, char *nom);
void loadPartie(Jeu *jeu, Niveau *niveau, char *nom);

#endif //TEST_FILES_H
