/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** amazed.h
*/
#include "my.h"
#ifndef AMAZED_H
    #define AMAZED_H
    #define MAX 100

typedef struct S {
    int tunnel;
    int room;
    int start;
    int end;
    int current_line;
    int nb_rooms;
    int nb_robots;
    int **tab;
    int start_room;
    int end_room;
    int rear;
    int front;
    int *queue;
} S_t;
void BFS(S_t *s);
typedef struct pars {
    int start;
    int end;
    int space;
    int tiret;
    int error;
    int err_nb_robot;
} pars_t;

typedef struct {
    char room1[100];
    char room2[100];
    int index;
    int is_second;
    int room1_index;
    int room2_index;
} LineProcessing_t;

void display_robots(S_t *s, pars_t *pars);
void display_tunnels(char **lines, S_t *s);
void display_rooms(char **lines, S_t *s);
void fill_matrix(S_t *s, char *line);
int get_num_rooms(char *line, S_t *s);
#endif
