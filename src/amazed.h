/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** amazed.h
*/
#include "my.h"
#ifndef AMAZED_H
    #define AMAZED_H

typedef struct S {
    int nb_rooms;
    int nb_robots;
    int **tab;
} S_t;

typedef struct {
    char room1[100];
    char room2[100];
    int index;
    int is_second;
    int room1_index;
    int room2_index;
} LineProcessing;

#endif
