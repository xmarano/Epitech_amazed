/*
** EPITECH PROJECT, 2023
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** moves.c
*/
#include "amazed.h"
#include "my.h"

void enqueue(S_t *s, int data)
{
    if (s->rear == s->nb_rooms - 1)
        my_printf("\nQueue is Full!!");
    else {
        if (s->front == -1)
            s->front = 0;
        s->rear++;
        s->queue[s->rear] = data;
    }
}

int dequeue(S_t *s)
{
    int data;

    if (s->front == -1 || s->front > s->rear) {
        my_printf("\nQueue is Empty!!");
        return -1;
    } else {
        data = s->queue[s->front];
        s->front++;
        if (s->front > s->rear)
            s->rear = -1;
            s->front = s->rear;
        return data;
    }
}

void print_path(int parent[], int start, int target)
{
    if (start == target) {
        my_printf("%d ", start);
    } else if (parent[target] == -1) {
        my_printf("No path from %d to %d", start, target);
    } else {
        print_path(parent, start, parent[target]);
        my_printf("%d ", target);
    }
}

void init_bfs(S_t *s, int *visited, int *parent)
{
    s->queue = malloc(sizeof(int) * s->nb_rooms);
    for (int i = 0; i < s->nb_rooms; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    enqueue(s, s->start_room);
    visited[s->start_room] = 1;
}

static void verif_bfs(S_t *s, int currentVertex, int *visited, int *parent)
{
    for (int i = 0; i < s->nb_rooms; i++) {
        if (s->tab[currentVertex][i] == 1 && visited[i] == 0) {
            enqueue(s, i);
            visited[i] = 1;
            parent[i] = currentVertex;
        }
    }
}

static void process_bfs(S_t *s, int *visited, int *parent)
{
    int currentVertex;

    while (s->front != -1) {
        currentVertex = dequeue(s);
        if (currentVertex == s->end_room) {
            print_path(parent, s->start_room, s->end_room);
            return;
        }
        verif_bfs(s, currentVertex, visited, parent);
    }
}

static void free_algo(S_t *s, int *visited, int *parent)
{
    free(s->queue);
    free(visited);
    free(parent);
}

void bfs(S_t *s)
{
    int *visited = malloc(sizeof(int) * s->nb_rooms);
    int *parent = malloc(sizeof(int) * s->nb_rooms);

    init_bfs(s, visited, parent);
    process_bfs(s, visited, parent);
    free_algo(s, visited, parent);
}
