#include "gestionTemps.h"

time_t initialiserTimer() {
    time_t end = time(0) + 60;
    return end;
}

time_t getTime() {
    return time(0);
}

int tempsAtteint(time_t end) {
    return (time(0) >= end);
}
