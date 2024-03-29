#include "files.h"

void loadNiveau(Niveau *niveau) {
    char filepath[MAX_PATH];
    GetModuleFileName(NULL, filepath, MAX_PATH);
    char *ret = strrchr(filepath, '\\');
    *ret = '\0';
    strcat(filepath, "\\niveaux\\");
    char buffer[10];
    sprintf(buffer, "%d", niveau->idNiveau);
    strcat(filepath, buffer);
    strcat(filepath, ".sgn");

    FILE *file;

    file = fopen(filepath, "r");
    if (!file) {
        printf("The file doesn't exist in %s !\n", filepath);
        return;
    }

    char chaine[MAX_PATH];
    for (int h = 0; h < HAUTEUR; h++) {
        if (fgets(chaine, MAX_PATH, file)) {
            for (int l = 0; l < LARGEUR; l++) {
                int nb = chaine[l] - 48;
                if (nb <= 9 && nb >= 0) {
                    if (nb == 8) {
                        niveau->snoopy.x = h;
                        niveau->snoopy.y = l;
                    } else if (nb == 7) {
                        if(niveau->balles < NOMBRE_BALL_MAX) {
                            niveau->balle[niveau->balles].position.x = h;
                            niveau->balle[niveau->balles].position.y = l;
                            niveau->balle[niveau->balles].direction.x = (rand()%2)*2-1;
                            niveau->balle[niveau->balles].direction.y = (rand()%2)*2-1;
                            niveau->balles++;
                            printf("%d", niveau->balles);
                        }
                    }
                    niveau->matrice[h][l] = nb;
                } else {
                    printf("The file doesn't have the correct format!");
                }
            }
        } else {
            printf("The file doesn't have the correct format!");
        }
    }
    fclose(file);
}
void sauvegarderPartie(Jeu *jeu, Niveau *niveau, char *nom) {
    char filepath[MAX_PATH];
    GetModuleFileName(NULL, filepath, MAX_PATH);
    char *ret = strrchr(filepath, '\\');
    *ret = '\0';
    strcat(filepath, "\\sauvegardes\\");
    strcat(filepath, nom);
    strcat(filepath, ".dat");

    FILE *file;

    file = fopen(filepath, "w");

    if (!file) {
        printf("The file doesn't exist in %s !\n", filepath);
        return;
    }

    fwrite(jeu, sizeof(Jeu), 1, file);

    fclose(file);
}
void loadPartie(Jeu *jeu, Niveau *niveau, char *nom) {
    char filepath[MAX_PATH];
    GetModuleFileName(NULL, filepath, MAX_PATH);
    char *ret = strrchr(filepath, '\\');
    *ret = '\0';
    strcat(filepath, "\\sauvegardes\\");
    strcat(filepath, nom);
    strcat(filepath, ".dat");

    FILE *file;

    file = fopen(filepath, "r");

    if (!file) {
        printf("The file doesn't exist in %s !\n", filepath);
        return;
    }

    fread(jeu, sizeof(Jeu), 1, file);

    fclose(file);
}
