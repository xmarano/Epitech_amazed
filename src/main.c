/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** main.c
*/
#include "amazed.h"
#include "my.h"

void process_line(char *line, LineProcessing *lp)
{
    if (line[lp->index] == '-') {
        lp->is_second = 1;
    } else if (lp->is_second == 0) {
        lp->room1[lp->room1_index] = line[lp->index];
        (lp->room1_index)++;
    } else {
        lp->room2[lp->room2_index] = line[lp->index];
        (lp->room2_index)++;
    }
}

void fill_matrix(S_t *s, char *line)
{
    LineProcessing lp = {{0}, {0}, 0, 0, 0, 0};

    while (line[lp.index] != '\n' && line[lp.index] != '\0') {
        process_line(line, &lp);
        lp.index++;
    }
    s->tab[my_atoi(lp.room1)][my_atoi(lp.room2)] = 1;
    s->tab[my_atoi(lp.room2)][my_atoi(lp.room1)] = 1;
}

int get_num_rooms(char *line, S_t *s)
{
    static int nb_rooms = 0;
    static int first_line = 1;

    if (first_line) {
        first_line = 0;
        return nb_rooms;
    }
    if (!strrchr(line, '#') && !strrchr(line, '-')) {
        nb_rooms ++;
    }
    return nb_rooms;
}

int parse_file(S_t *s, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

    s->nb_robots = my_atoi(line);
    s->tab = malloc(sizeof(int *) * 100);
    for (int i = 0; i < 100; i ++) {
        s->tab[i] = malloc(sizeof(int) * 100);
        for (int j = 0; j < 100; j++)
            s->tab[i][j] = 0;
    }
    while (read != -1) {
        if (my_strrchr(line, '-'))
            fill_matrix(s, line);
        else
            s->nb_rooms = get_num_rooms(line, s);
        read = getline(&line, &len, stdin);
    }
    free(line);
    return 0;
}

int main(int argc, char **argv)
{
    S_t s;

    parse_file(&s, argv);
    return 0;
}
