#include "jeu.h"

int actionsBlock(s_Niveau *niveau, int directionX, int directionY) {
    if (niveau->score > 12) {
        return 1;
    } else {
        return 0;
    }
}

void pauseGame(s_Niveau *niveau) {
    if (!niveau->pause) {
        niveau->pause = !niveau->pause;
        niveau->end -= getTime();
    } else {
        niveau->pause = !niveau->pause;
        niveau->end += getTime();
    }
}

void mouvement(s_Niveau *niveau, int touche) {
    int x = niveau->snoopy.x;
    int y = niveau->snoopy.y;

    int directionX = 0;
    int directionY = 0;

    switch (touche) {
        case 72: // Flèche haute
            if (x > 0) {
                directionX = -1;
                directionY = 0;
            }
            break;
        case 80: // Flèche bas
            if (x < HAUTEUR - 1) {
                directionX = 1;
                directionY = 0;
            }
            break;
        case 75: // Flèche gauche
            if (y > 0) {
                directionX = 0;
                directionY = -1;
            }
            break;
        case 77: // Flèche droite
            if (y < LARGEUR - 1) {
                directionX = 0;
                directionY = 1;
            }
            break;
        case 'p':
            pauseGame(niveau);
            break;
        default:
            break;
    }

    if (!niveau->pause && !actionsBlock(niveau, directionX, directionY)) {
        niveau->snoopy.x += directionX;
        niveau->snoopy.y += directionY;

        niveau->matrice[x][y] = 0;
        niveau->matrice[x + directionX][y + directionY] = 8;
    }
}

void jeu() {
    s_Jeu gameHolder = {NOMBRE_NIVEAUX, 0, 3};

    for (int niveauIdx = 0; niveauIdx < gameHolder.nombreNiveaux; niveauIdx++) {
        s_Niveau niveau = gameHolder.niveaux[niveauIdx];
        niveau.idNiveau = niveauIdx + 1;
        niveau.score = 0;
        niveau.pause = 0;
        niveau.niveauFini = 0;
        loadNiveau(&niveau);
        niveau.end = initialiserTimer();
        while (niveau.pause || (!tempsAtteint(niveau.end) && !niveau.niveauFini)) {
            system("cls");
            afficherMatrice(&niveau);
            if (_kbhit()) {
                mouvement(&niveau, getch());
            } else {
                sleep(200);
            }
        }
        niveau.score = niveau.end - getTime();
    }
}
