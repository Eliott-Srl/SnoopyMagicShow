#ifndef TEST_TYPES_H
#define TEST_TYPES_H

#include <time.h>

#define NOMBRE_NIVEAUX 3
#define HAUTEUR 10
#define LARGEUR 20

typedef struct {
    int x;
    int y;
} coordonnees;

typedef struct {
    int idNiveau;
    int score;
    time_t end;
    int niveauFini;
    int pause;
    coordonnees snoopy;
    int matrice[HAUTEUR][LARGEUR];
} s_Niveau;

typedef struct {
    int nombreNiveaux;
    int score;
    int vies;
    s_Niveau niveaux[NOMBRE_NIVEAUX];
    int matrice[HAUTEUR][LARGEUR];
} s_Jeu;

#endif //TEST_TYPES_H
