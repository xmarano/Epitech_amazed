/*
** EPITECH PROJECT, 2023
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** print_file.c
*/

#include "amazed.h"
#include "my.h"

char **read_file_to_array(void)
{
    char **lines = malloc(sizeof(char *) * 100);
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);
    int i = 0;

    while (read != -1) {
        lines[i] = malloc(sizeof(char) * (my_strlen(line) + 1));
        my_strcpy(lines[i], line);
        i++;
        read = getline(&line, &len, stdin);
    }
    free(line);
    lines[i] = NULL;
    return lines;
}

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

void display_file(char **lines)
{
    int i = 0;
    int rooms_printed = 0;
    int tunnels_printed = 0;

    my_printf("#number_of_robots\n");
    my_printf("%s", lines[i++]);
    while (lines[i] != NULL) {
        if (lines[i][0] == '#' && my_strstr(lines[i], "##start") == NULL &&
            my_strstr(lines[i], "##end") == NULL) {
            i++;
            continue;
        }
        if (my_strchr(lines[i], '#') != NULL) {
            for (int j = 0; lines[i][j] != '#'; j++) {
                my_printf("%c", lines[i][j]);
            }
            my_printf("\n");
            /*i ++;
            continue;*/
        }
        display_comments(lines, &i, &rooms_printed, &tunnels_printed);
        i++;
    }
}
