#include "jeu.h"

void bougerBalle(Niveau *niveau, int *vies) {
    if (niveau->pause) {
        return;
    }

    if (niveau->balle.lastUpdate < getTime()) {
        niveau->balle.lastUpdate = getTime();


        int posX = niveau->balle.position.x;
        int posY = niveau->balle.position.y;
        int dirX = niveau->balle.direction.x;
        int dirY = niveau->balle.direction.y;

        if (posX + dirX < 0 || posX + dirX >= HAUTEUR) {
            niveau->balle.direction.x = -(dirX);
        }

        if (posY + dirY < 0 || posY + dirY >= LARGEUR) {
            niveau->balle.direction.y = -(dirY);
        }

        niveau->matrice[posX][posY] = niveau->balle.blockBehind;

        niveau->balle.position.x = posX + niveau->balle.direction.x;
        niveau->balle.position.y = posY + niveau->balle.direction.y;

        niveau->balle.blockBehind = niveau->matrice[niveau->balle.position.x][niveau->balle.position.y];
        niveau->matrice[niveau->balle.position.x][niveau->balle.position.y] = 7;

        if (niveau->snoopy.x == niveau->balle.position.x && niveau->snoopy.y == niveau->balle.position.y) {
            (*vies)--;
        }
    }
}

int actionsBlock(Niveau *niveau, int directionX, int directionY) {
    if (directionY == 0 && directionX == 0) {
        return 0;
    }

    switch(niveau->matrice[niveau->snoopy.x + directionX][niveau->snoopy.y + directionY]) {
        case 1: {
            return 0;
        }
        case 2: {
            niveau->snoopy.x += directionX;
            niveau->snoopy.y += directionY;

            niveau->matrice[niveau->snoopy.x + directionX][niveau->snoopy.y + directionY] = niveau->matrice[niveau->snoopy.x][niveau->snoopy.y];
            niveau->matrice[niveau->snoopy.x][niveau->snoopy.y] = niveau->matrice[niveau->snoopy.x - directionX][niveau->snoopy.y - directionY];
            niveau->matrice[niveau->snoopy.x - directionX][niveau->snoopy.y - directionY] = 0;
            return 1;
        }
        case 4: {
            return 1;
        }
        case 9: {

        }
        default: {
            return 0;
        }
    }
}

void pauseGame(Niveau *niveau) {
    if (!niveau->pause) {
        niveau->pause = !niveau->pause;
        niveau->end -= getTime();
    } else {
        niveau->pause = !niveau->pause;
        niveau->end += getTime();
    }
}

void mouvement(Niveau *niveau, int touche) {
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
    Jeu gameHolder = {NOMBRE_NIVEAUX, 0, 3};
    srand(time(0));
    for (int niveauIdx = 0; niveauIdx < gameHolder.nombreNiveaux; niveauIdx++) {
        Niveau niveau = gameHolder.niveaux[niveauIdx];
        niveau.idNiveau = niveauIdx + 1;
        niveau.score = 0;
        niveau.pause = 0;
        niveau.niveauFini = 0;
        niveau.snoopy.x = 0;
        niveau.snoopy.y = 0;
        niveau.blockSousSnoopy = 0;
        niveau.balle.position.x = 0;
        niveau.balle.position.y = 0;
        niveau.balle.direction.x = rand()%2 == 0 ? -1 : 1;
        niveau.balle.direction.y = rand()%2 == 0 ? -1 : 1;

        loadNiveau(&niveau);
        niveau.end = initialiserTimer();
        niveau.balle.lastUpdate = getTime();
        while (niveau.pause || (gameHolder.vies != 0 && !tempsAtteint(niveau.end) && !niveau.niveauFini)) {
            system("cls");
            printf("Vies: %d\n", gameHolder.vies);
            afficherMatrice(&niveau);
            bougerBalle(&niveau, &gameHolder.vies);
            if (_kbhit()) {
                mouvement(&niveau, getch());
            } else {
                Sleep(200);
            }
        }
        niveau.score = niveau.end - getTime();
    }
    printf("You lost, you crusty bastard!");
    getch();
}
