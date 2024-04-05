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
    if (!my_strrchr(line, '#') && !my_strrchr(line, '-')) {
        nb_rooms ++;
    }
    return nb_rooms;
}

int parse_file(S_t *s, char **lines)
{
    int i = 0;

    s->nb_robots = my_atoi(lines[i++]);
    s->tab = malloc(sizeof(int *) * 100);
    for (int j = 0; j < 100; j ++) {
        s->tab[j] = malloc(sizeof(int) * 100);
        for (int k = 0; k < 100; k++)
            s->tab[j][k] = 0;
    }
    while (lines[i] != NULL) {
        if (my_strchr(lines[i], '-'))
            fill_matrix(s, lines[i]);
        else
            s->nb_rooms = get_num_rooms(lines[i], s);
        i++;
    }
    printf("%d\n", s->nb_robots);
    return 0;
}

int main(int argc, char **argv)
{
    S_t s;
    char **lines = read_file_to_array();

    parse_file(&s, lines);
    display_file(lines);
    return 0;
}
