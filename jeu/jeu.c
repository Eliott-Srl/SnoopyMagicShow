#include "jeu.h"

void casserBlock(Niveau *niveau) {
    if (niveau->pause) {
        return;
    }

    int posX = niveau->snoopy.x;
    int posY = niveau->snoopy.y;

    if (niveau->matrice[posX + 1][posY] == 1) {
        niveau->matrice[posX + 1][posY] = 0;
    }
    if (niveau->matrice[posX - 1][posY] == 1) {
        niveau->matrice[posX - 1][posY] = 0;
    }
    if (niveau->matrice[posX][posY + 1] == 1) {
        niveau->matrice[posX][posY + 1] = 0;
    }
    if (niveau->matrice[posX][posY - 1] == 1) {
        niveau->matrice[posX][posY - 1] = 0;
    }
}

void bougerBalle(Niveau *niveau, int *vies) {
    if (niveau->pause) {
        return;
    }

    for (int i = 0; i < niveau->balles; i++) {
        if (niveau->balle[i].lastUpdate < getTime()) {
            int posX = niveau->balle[i].position.x;
            int posY = niveau->balle[i].position.y;
            int dirX = niveau->balle[i].direction.x;
            int dirY = niveau->balle[i].direction.y;

            if (posX + dirX < 0 || posX + dirX >= HAUTEUR) {
                niveau->balle[i].direction.x = -(dirX);
            }

            if (posY + dirY < 0 || posY + dirY >= LARGEUR) {
                niveau->balle[i].direction.y = -(dirY);
            }

            niveau->matrice[posX][posY] = niveau->balle[i].blockBehind;

            niveau->balle[i].position.x = posX + niveau->balle[i].direction.x;
            niveau->balle[i].position.y = posY + niveau->balle[i].direction.y;

            if (niveau->matrice[niveau->balle[i].position.x][niveau->balle[i].position.y] != 8) {
                niveau->balle[i].blockBehind = niveau->matrice[niveau->balle[i].position.x][niveau->balle[i].position.y];
            }

            niveau->matrice[niveau->balle[i].position.x][niveau->balle[i].position.y] = 7;

            if (niveau->snoopy.x == niveau->balle[i].position.x && niveau->snoopy.y == niveau->balle[i].position.y) {
                (*vies)--;
            }

        }
        niveau->balle[i].lastUpdate = getTime();
    }
}

int actionsBlock(Niveau *niveau, int directionX, int directionY, int *vies) {
    if (directionY == 0 && directionX == 0) {
        return 0;
    }

    switch(niveau->matrice[niveau->snoopy.x + directionX][niveau->snoopy.y + directionY]) {
        case 1: {
            return 1;
        }
        case 2: {
            if (niveau->matrice[niveau->snoopy.x + 2*directionX][niveau->snoopy.y + 2*directionY] == 0) {
                niveau->snoopy.x += directionX;
                niveau->snoopy.y += directionY;

                niveau->matrice[niveau->snoopy.x + directionX][niveau->snoopy.y + directionY] = 4;
                niveau->matrice[niveau->snoopy.x][niveau->snoopy.y] = niveau->matrice[niveau->snoopy.x - directionX][niveau->snoopy.y - directionY];
                niveau->matrice[niveau->snoopy.x - directionX][niveau->snoopy.y - directionY] = 0;
            }
            return 1;
        }
        case 3: {
            (*vies)--;
            return 1;
        }
        case 4: {
            return 1;
        }
        case 5: {
            // TODO: Téléporteur
            return 1;
        }
        case 6: {
            return 1;
        }
        case 7: {
            (*vies)--;
        }
        case 9: {
            niveau->oiseaux++;
            if (niveau->oiseaux == 4) {
                niveau->niveauFini = 1;
            }
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

void mouvement(Niveau *niveau, Jeu *gameHolder, int *vies, int touche) {
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
        case 'c':
            casserBlock(niveau);
            break;
        case 's':
            //sauvegarderPartie(gameHolder, niveau, "lol");
        default:
            break;
    }

    if (!niveau->pause && !actionsBlock(niveau, directionX, directionY, vies)) {
        niveau->snoopy.x += directionX;
        niveau->snoopy.y += directionY;

        niveau->matrice[x][y] = 0;
        niveau->matrice[x + directionX][y + directionY] = 8;
    }
}

void motdepasse(int *idniveau, int *jeulanch, int *jeufini, int *score) {
    Jeu gameHolder = {NOMBRE_NIVEAUX, 0, 3};
    char *motDePasses[] = {"", "complexe?", "thelastone"};
    srand(time(0));

    if (strcmp(motDePasses[(*idniveau)], "")) {
        char answer[MAX_PATH];
        system("cls");
        printf("Quelle est le mot de passe du niveau %d\n>>> ", (*idniveau) + 1);
        scanf("%s", answer);

        if(!strcmp(motDePasses[(*idniveau)], answer)) {
            printf("On y vas!\n");
            Sleep(1000);
            (*jeulanch) = 1;
        } else {
            printf("Mauvais mot de passe!\n");
            Sleep(1000);
        }
    } else {
        (*jeulanch) = 1;
    }

    if ((*jeulanch) == 1) {
        Niveau niveau = gameHolder.niveaux[(*idniveau)];
        niveau.idNiveau = (*idniveau) + 1;
        niveau.score = 0;
        niveau.pause = 0;
        niveau.niveauFini = 0;
        niveau.oiseaux = 0;
        niveau.snoopy.x = HAUTEUR/2;
        niveau.snoopy.y = LARGEUR/2;
        niveau.blockSousSnoopy = 0;
        loadNiveau(&niveau);
        niveau.end = initialiserTimer();
        for(int i = 0; i < niveau.balles; i++) {
            (niveau.balle[i]).lastUpdate = getTime();
        }
        while (niveau.pause || (gameHolder.vies != 0 && !tempsAtteint(niveau.end) && !niveau.niveauFini)) {
            system("cls");
            printf(" Vies: %d                 Oiseaux restants: %d\n", gameHolder.vies, 4 - niveau.oiseaux);
            afficherMatrice(&niveau);
            bougerBalle(&niveau, &gameHolder.vies);
            niveau.matrice[niveau.snoopy.x][niveau.snoopy.y] = 8;
            if (_kbhit()) {
                mouvement(&niveau, &gameHolder, &gameHolder.vies, getch());
            } else {
                Sleep(200);
            }
        }
        system("cls");
        printf(" Vies: %d                 Oiseaux restants: %d\n", gameHolder.vies, 4 - niveau.oiseaux);
        afficherMatrice(&niveau);
        if (gameHolder.vies != 0 && !tempsAtteint(niveau.end) && niveau.niveauFini) {
            printf("Bravo! Vous avez fini le jeu !!!!!!! :)\n");
            (*score) += (int)(niveau.end - getTime())*100;
            if ((*idniveau) + 1 != NOMBRE_NIVEAUX) {
                printf("Le mot de passe du prochain niveau: %s\nAppuie sur une touche quand tu as retenu\n", motDePasses[(*idniveau) + 1]);
                Sleep(1000);
                getch();
            }
        } else {
            printf("Vous avez perdu, essayez plus fort!\n");
        }
        (*jeufini) = niveau.niveauFini;
    }
}

void jeu() {
    Jeu gameHolder = {NOMBRE_NIVEAUX, 0, 3};
    char *motDePasses[] = {"", "complexe?", "thelastone"};
    int scoreTotal = 0;
    int jeuFini = 0;
    int jeuLanch = 0;
    srand(time(0));
    for (int niveauIdx = 0; niveauIdx < gameHolder.nombreNiveaux; niveauIdx++) {
        jeuFini = 0;
        jeuLanch = 0;
        motdepasse(&niveauIdx, &jeuLanch, &jeuFini, &scoreTotal);
        if (!jeuFini) {
            break;
        }
    }

    printf("Votre score est de %d points\n", scoreTotal);
    Sleep(2000);
    getch();
}
