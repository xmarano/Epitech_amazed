/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** main.c
*/
#include "amazed.h"
#include "my.h"

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
            for (int j = 0; lines[i][j] != '#'; j++)
                my_printf("%c", lines[i][j]);
            my_printf("\n");
        }
        display_comments(lines, &i, &rooms_printed, &tunnels_printed);
        i++;
    }
}

int parse_file(S_t *s, char **lines)
{
    int i = 0;

    s->nb_robots = my_atoi(lines[i]);
    i++;
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
    return 0;
}

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

static void init_struct(pars_t *pars)
{
    pars->start = 0;
    pars->end = 0;
    pars->error = 0;
}

static int parsing_error2(pars_t *pars, char **lines, int i)
{
    for (int j = 0; lines[i][j] != '\n'; j++) {
        if (lines[i][j] == '#')
            return 0;
    }
    pars->space = 0;
    pars->tiret = 0;
    for (int j = 0; lines[i][j] != '\n'; j++) {
        if (lines[i][j] > '9' && lines[i][j] != ' ' && lines[i][j] != '-')
            pars->error++;
        if (lines[i][j] == ' ')
            pars->space++;
        if (lines[i][j] == '-')
            pars->tiret++;
    }
    if (pars->space != 2 && pars->tiret != 1)
        pars->error++;
    return 0;
}

int parsing_error(pars_t *pars, char **lines)
{
    init_struct(pars);
    if (lines[0] == NULL) {
        pars->error++;
        return 0;
    }
    for (int i = 1; lines[i] != NULL; i++) {
        if (my_strcmp("##start\n", lines[i]) == 0) {
            pars->start++;
            continue;
        }
        if (my_strcmp("##end\n", lines[i]) == 0) {
            pars->end++;
            continue;
        }
        parsing_error2(pars, lines, i);
    }
    if (pars->start != 1 || pars->end != 1)
        pars->error++;
    return 0;
}

int main(int argc, char **argv)
{
    S_t s;
    pars_t pars;
    char **lines = read_file_to_array();

    parsing_error(&pars, lines);
    parse_file(&s, lines);
    display_file(lines);
    if (pars.error != 0)
        return 84;
    return 0;
}
