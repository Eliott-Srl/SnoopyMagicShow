#include "jeu/jeu.h"

int main() {
    int choice = 0;

    int niveau = 0;
    int jeulanch = 0;
    int jeufini = 0;
    int score = 0;
    do {
        printf("+-[Menu]-------------------+\n");
        printf("| 1. Jouer                 |\n");
        //printf("| 2. Charger une partie    |\n");
        printf("| 3. Mot de passe          |\n");
        //printf("| 4. Scores                |\n");
        printf("| 99. Quitter              |\n");
        printf("+--------------------------+\n");
        printf(">>> ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                jeu();
                break;
            case 2:
                // chargerPartie();
                break;
            case 3:
                printf("Quel niveau voulez-vous ?\n>>> ");
                do {
                    scanf("%d", &niveau);
                } while(niveau > NOMBRE_NIVEAUX && niveau < 0);
                niveau--;
                motdepasse(&niveau, &jeulanch, &jeufini, &score);
                break;
            case 4:
                // scores();
                break;
            default:
                printf("Recommence!");
                break;
        }
    } while(choice != 99);
    return 0;
}
