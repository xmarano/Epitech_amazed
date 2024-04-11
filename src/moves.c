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
        printf("\nQueue is Full!!");
    else {
        if(s->front == -1)
            s->front = 0;
        s->rear++;
        s->queue[s->rear] = data;
    }
}

int dequeue(S_t *s)
{
    if(s->front == -1 || s->front > s->rear) {
        printf("\nQueue is Empty!!");
        return -1;
    } else {
        int data = s->queue[s->front];
        s->front++;
        if(s->front > s->rear)
            s->front = s->rear = -1;
        return data;
    }
}

void printPath(int parent[], int start, int target)
{
    if(start == target) {
        printf("%d ", start);
    } else if(parent[target] == -1) {
        printf("No path from %d to %d", start, target);
    } else {
        printPath(parent, start, parent[target]);
        printf("%d ", target);
    }
}

void BFS(S_t *s)
{
    int *visited = malloc(sizeof(int) * s->nb_rooms);
    int *parent = malloc(sizeof(int) * s->nb_rooms);
    int currentVertex;

    s->queue = malloc(sizeof(int) * s->nb_rooms);
    for(int i = 0; i < s->nb_rooms; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    enqueue(s, s->start_room);
    visited[s->start_room] = 1;
    while(s->front != -1) {
        currentVertex = dequeue(s);
        if(currentVertex == s->end_room) {
            printPath(parent, s->start_room, s->end_room);
            return;
        }
        for(int i = 0; i < s->nb_rooms; i++) {
            if(s->tab[currentVertex][i] == 1 && visited[i] == 0) {
                enqueue(s, i);
                visited[i] = 1;
                parent[i] = currentVertex;
            }
        }
    }
    free(s->queue);
    free(visited);
    free(parent);
}
