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
    coordonnees position;
    coordonnees direction;
    time_t lastUpdate;
    int blockBehind;
} Balle;

typedef struct {
    int idNiveau;
    int score;
    time_t end;
    int niveauFini;
    int pause;
    int oiseaux;
    coordonnees snoopy;
    int blockSousSnoopy;
    Balle balle;
    int matrice[HAUTEUR][LARGEUR];
} Niveau;

typedef struct {
    int nombreNiveaux;
    int score;
    int vies;
    Niveau niveaux[NOMBRE_NIVEAUX];
    int matrice[HAUTEUR][LARGEUR];
} Jeu;

#endif //TEST_TYPES_H
