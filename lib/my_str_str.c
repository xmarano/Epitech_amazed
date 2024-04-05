/*
** EPITECH PROJECT, 2023
** B-CPE-200-MAR-2-1-robotfactory-selim.bouasker
** File description:
** my_str_str.c
*/

#include "../src/my.h"

int inner_loop(char *source, char *search, int i)
{
    int j;

    for (j = 0; search[j] != '\0'; j++) {
        if (source[i + j] != search[j])
            break;
    }
    return j;
}

char *my_strstr(char *source, char *search)
{
    int i;
    int j;

    for (i = 0; source[i] != '\0'; i++) {
        j = inner_loop(source, search, i);
        if (search[j] == '\0')
            return &source[i];
    }
    return NULL;
}
