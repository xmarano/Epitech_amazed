/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** main.c
*/
#include "amazed.h"
#include "my.h"

void display_robots(S_t *s, pars_t *pars)
{
    my_printf("#number_of_robots\n");
    if (pars->err_nb_robot == 0) {
        my_printf("%d\n", s->nb_robots);
        s->current_line = 1;
    }
}

void display_numbers(char **lines, S_t *s)
{
    for (int i = 0; lines[s->current_line][i] != '\n'; i++) {
        if (lines[s->current_line][i] == '#')
            return;
        my_printf("%c", lines[s->current_line][i]);
    }
}

void display_rooms(char **lines, S_t *s)
{
    if (my_strchr(lines[s->current_line], '-') != NULL)
        return;
    if (s->room == 0) {
        my_printf("#rooms\n");
        s->room = 1;
    }
    if (s->start == 0 && my_strcmp(lines[s->current_line], "##start\n") == 0) {
        my_printf("##start\n");
        s->start = 1;
        return;
    }
    if (s->end == 0 && my_strcmp(lines[s->current_line], "##end\n") == 0) {
        my_printf("##end\n");
        s->end = 1;
        return;
    }
    display_numbers(lines, s);
    if (lines[s->current_line][0] != '#')
        my_printf("\n");
}

void display_tunnels(char **lines, S_t *s)
{
    if (my_strchr(lines[s->current_line], '-') != NULL) {
        if (s->tunnel == 0) {
            my_printf("#tunnels\n");
            s->tunnel = 1;
        }
        my_printf("%s", lines[s->current_line]);
    }
}
