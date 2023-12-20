#include "matrice.h"

void initialiseMatrice(Niveau *niveau) {
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            niveau->matrice[h][l] = 0;
        }
    }
}

void afficherMatrice(Niveau *niveau) {
    int emoji[] = {0x20, 0xB0, 0xC5, 0xCF, 0xB2, 0x40, 0xCE, 0x4F, 0xA9, 0xF8};
    time_t timer = (niveau->pause ? niveau->end : niveau->end - getTime());

    if (COULEUR) {
        colorScreen(15, 2);
    }

    for (int l = LARGEUR/2 - 1; l > 0; l--) {
        if (timer >= l) {
            printf(" #");
        } else {
            if (COULEUR) {
                colorScreen(8, 2);
            }
            printf(" #");
            if (COULEUR) {
                colorScreen(15, 2);
            }
        }
    }

    printf(" [ %d %d ]", ((int) niveau->idNiveau/10)%10, niveau->idNiveau%10);

    for (int l = 0; l < LARGEUR/2 - 1; l++) {
        if (timer >= 60 - l) {
            printf(" #");
        } else {
            if (COULEUR) {
                colorScreen(8, 2);
            }
            printf(" #");
            if (COULEUR) {
                colorScreen(15, 2);
            }
        }
    }

    printf(" \n");

    for (int h = 0; h < HAUTEUR; h++) {
        if ((60 - (timer + 40)) <= (HAUTEUR - h)) {
            printf(" # ");
        } else {
            if (COULEUR) {
                colorScreen(8, 2);
            }
            printf(" # ");
            if (COULEUR) {
                colorScreen(15, 2);
            }
        }

        for (int l = 0; l < LARGEUR; l++) {
            printf("%c ", emoji[niveau->matrice[h][l]]);
        }

        if (timer >= (60 - 9 - h)) {
            printf("# \n");
        } else {
            if (COULEUR) {
                colorScreen(8, 2);
            }
            printf("# \n");
            if (COULEUR) {
                colorScreen(15, 2);
            }
        }
    }

    for (int l = LARGEUR + 2; l > 0; l--) {
        if (60 - timer >= (LARGEUR/2 - 1 + HAUTEUR + l)) {
            if (COULEUR) {
                colorScreen(8, 2);
            }
            printf(" #");
            if (COULEUR) {
                colorScreen(15, 2);
            }
        } else {
            printf(" #");
        }
    }
    printf(" \n");

    if (COULEUR) {
        colorScreen(15, 0);
    }

    if (niveau->pause) {
        printf("Jeu en pause !\n");
    } else {
        printf("");
    }
}
