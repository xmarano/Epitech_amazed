/*
** EPITECH PROJECT, 2023
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** print_file.c
*/

#include "amazed.h"
#include "my.h"

void display_comments(char **lines, int *i, int *rooms_printed,
    int *tunnels_printed)
{
    if (my_strstr(lines[*i], "##start") != NULL) {
        if (*rooms_printed == 0) {
            my_printf("#rooms\n");
            *rooms_printed = 1;
        }
        my_printf("##start\n");
    } else if (my_strstr(lines[*i], "##end") != NULL) {
        if (*rooms_printed == 0) {
            my_printf("#rooms\n");
            *rooms_printed = 1;
        }
        my_printf("##end\n");
    } else if (my_strchr(lines[*i], '-') != NULL) {
        if (*tunnels_printed == 0) {
            my_printf("#tunnels\n");
            *tunnels_printed = 1;
        }
        my_printf("%s", lines[*i]);
    } else {
        if (*rooms_printed == 0) {
            my_printf("#rooms\n");
            *rooms_printed = 1;
        }
        my_printf("%s", lines[*i]);
    }
}

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
    if (!my_strrchr(line, '#') && !my_strrchr(line, '-'))
        nb_rooms ++;
    return nb_rooms;
}
