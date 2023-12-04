cmake_minimum_required(VERSION 3.26)
project(test C)

set(CMAKE_C_STANDARD 11)

add_executable(test main.c
        utils/matrice.c
        utils/matrice.h
        jeu/gestionTemps.c
        jeu/gestionTemps.h
        utils/utils.c
        utils/utils.h
        jeu/jeu.c
        jeu/jeu.h
        utils/types.h
        files/files.c
        files/files.h)
