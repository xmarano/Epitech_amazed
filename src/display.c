/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** main.c
*/
#include "amazed.h"
#include "my.h"


void display_rooms(char **lines, int *i, int *rooms)
{
    if (*rooms == 0) {
        my_printf("#rooms\n");
        *rooms = 1;
    }
    if (my_strstr(lines[*i], "##start") != NULL) {
        my_printf("##start\n");
    } else if (my_strstr(lines[*i], "##end") != NULL) {
        my_printf("##end\n");
    } else {
        my_printf("%s", lines[*i]);
    }
}

void display_tunnels(char **lines, int *i, int *tunnels)
{
    if (*tunnels == 0) {
        my_printf("#tunnels\n");
        *tunnels = 1;
    }
    my_printf("%s", lines[*i]);
}

void display_comments(char **lines, int *i, int *rooms, int *tunnels)
{
    if (my_strchr(lines[*i], '-') != NULL) {
        display_tunnels(lines, i, tunnels);
    } else {
        display_rooms(lines, i, rooms);
    }
}
