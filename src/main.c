/*
** EPITECH PROJECT, 2024
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** main.c
*/
#include "amazed.h"
#include "my.h"

void display_file(S_t *s, pars_t *pars, char **lines)
{
    display_robots(s, pars);
    while (lines[s->current_line] != NULL) {
        if (not_display(lines, s) == 84)
            return;
        if (s->start == 1 &&
        my_strcmp(lines[s->current_line], "##start\n") == 0)
            return;
        if (s->end == 1 && my_strcmp(lines[s->current_line], "##end\n") == 0)
            return;
        display_rooms(lines, s);
        display_tunnels(lines, s);
        s->current_line++;
    }
}

static void verif(S_t *s, char **lines, int *i)
{
    if (my_strcmp(lines[*i], "##start\n") == 0) {
        s->start_room = my_atoi(lines[*i + 1]);
        (*i)++;
    } else if (my_strcmp(lines[*i], "##end\n") == 0) {
        s->end_room = my_atoi(lines[*i + 1]);
        (*i)++;
    }
}

static void init_matrix(S_t *s)
{
    s->tab = malloc(sizeof(int *) * 100);
    for (int j = 0; j < 100; j ++) {
        s->tab[j] = malloc(sizeof(int) * 100);
        for (int k = 0; k < 100; k++)
            s->tab[j][k] = 0;
    }
}

int parsing_file(S_t *s, char **lines)
{
    int i = 0;

    s->nb_robots = my_atoi(lines[i]);
    i++;
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

static void init_struct(pars_t *pars, S_t *s)
{
    s->front = -1;
    s->rear = -1;
    s->start_room = 0;
    s->end_room = 0;
    s->tunnel = 0;
    s->room = 0;
    s->start = 0;
    s->end = 0;
    s->current_line = 0;
    pars->start = 0;
    pars->end = 0;
    pars->error = 0;
    pars->err_nb_robot = 0;
    pars->empty_file = 0;
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
    if (lines[0] == NULL) {
        pars->empty_file++;
        return 0;
    }
    for (int i = 0; lines[0][i] != '\n'; i++) {
        if (lines[0][i] > '9')
            pars->err_nb_robot++;
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
    return 0;
}

int main(int argc, char **argv)
{
    S_t s;
    pars_t pars;
    char **lines = read_file_to_array();

    init_struct(&pars, &s);
    parsing_error(&pars, lines);
    if (pars.start != 1 || pars.end != 1)
        pars.error++;
    if (pars.empty_file != 0)
        return 84;
    parsing_file(&s, lines);
    display_file(&s, &pars, lines);
    if (pars.error + pars.err_nb_robot != 0)
        return 84;
    return 0;
}
