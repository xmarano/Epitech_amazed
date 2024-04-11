/*
** EPITECH PROJECT, 2023
** B-CPE-200-MAR-2-1-amazed-tom.clerc
** File description:
** moves.c
*/
#include "amazed.h"
#include "my.h"

static void enqueue(S_t *s, int data)
{
    if (s->rear == s->nb_rooms - 1)
        printf("\nQueue is Full!!");
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
        printf("\nQueue is Empty!!");
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


void print_path(int parent[], int start, int target, int robot, int level[])
{
    static int line = 0;

    if (start == target) {
        if (start != 0) {
            printf("P%d-%d ", robot, start);
            if (level[start] == line) {
                printf("\n");
                line++;
            }
        }
    } else if (parent[target] == -1) {
        printf("No path from %d to %d", start, target);
    } else {
        print_path(parent, start, parent[target], robot, level);
        if (target != 0) {
            printf("P%d-%d ", robot, target);
            if (level[target] == line) {
                printf("\n");
                line++;
            }
        }
    }
}

void init_bfs(S_t *s, int *visited, int *parent, int *level)
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

void process_bfs(S_t *s, int *visited, int *parent, int robot, int *level)
{
    int currentVertex;

    while (s->front != -1) {
        currentVertex = dequeue(s);
        if (currentVertex == s->end_room) {
            print_path(parent, s->start_room, s->end_room, robot, level);
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
    int *level = malloc(sizeof(int) * s->nb_rooms);

    for (int robot = 1; robot <= s->nb_robots; robot++) {
        init_bfs(s, visited, parent, level);
        process_bfs(s, visited, parent, robot, level);
        printf("\n");
    }
    free_algo(s, visited, parent);
    free(level);
}
