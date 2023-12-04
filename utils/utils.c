#include "utils.h"

void colorScreen(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

