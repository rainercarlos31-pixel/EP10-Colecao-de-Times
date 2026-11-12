#include <stdlib.h>
#include "teamlist.h"

typedef struct node {
    Team *team;
    struct node *next;
    struct node *prev;
} Node;

struct teamlist {
    Node *first;
    Node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL) {
        return NULL;
    }

    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    Node *new_node;

    if (tl == NULL || t == NULL) {
        return;
    }

    new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return;
    }

    new_node->team = t;
    new_node->next = NULL;
    new_node->prev = tl->last;

    if (tl->last == NULL) {
        tl->first = new_node;
    } else {
        tl->last->next = new_node;
    }

    tl->last = new_node;
    tl->size++;
}

int tl_size(TeamList *tl) {
    if (tl == NULL) {
        return 0;
    }

    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    Node *current;
    int j;

    if (tl == NULL || i < 0 || i >= tl->size) {
        return NULL;
    }

    current = tl->first;

    for (j = 0; j < i; j++) {
        current = current->next;
    }

    return current->team;
}

void tl_free(TeamList *tl) {
    Node *current;
    Node *next;

    if (tl == NULL) {
        return;
    }

    current = tl->first;

    while (current != NULL) {
        next = current->next;

        team_free(current->team);
        free(current);

        current = next;
    }

    free(tl);
}