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

void fill_matrix(S_t *s, char *line);
int get_num_rooms(char *line, S_t *s);
void display_comments(char **lines, int *i, int *rooms_printed,
    int *tunnels_printed);
void display_rooms(char **lines, int *i, int *rooms);
void display_tunnels(char **lines, int *i, int *tunnels);
void display_comments(char **lines, int *i, int *rooms, int *tunnels);
#endif
