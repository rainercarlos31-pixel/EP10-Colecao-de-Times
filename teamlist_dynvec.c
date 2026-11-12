#include <stdlib.h>
#include "teamlist.h"

struct teamlist {
    Team **teams;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL) {
        return NULL;
    }

    tl->size = 0;
    tl->capacity = 2;
    tl->teams = malloc(tl->capacity * sizeof(Team *));

    if (tl->teams == NULL) {
        free(tl);
        return NULL;
    }

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    Team **temp;

    if (tl == NULL || t == NULL) {
        return;
    }

    if (tl->size == tl->capacity) {
        tl->capacity *= 2;

        temp = realloc(tl->teams,
                       tl->capacity * sizeof(Team *));

        if (temp == NULL) {
            tl->capacity /= 2;
            return;
        }

        tl->teams = temp;
    }

    tl->teams[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    if (tl == NULL) {
        return 0;
    }

    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (tl == NULL || i < 0 || i >= tl->size) {
        return NULL;
    }

    return tl->teams[i];
}

void tl_free(TeamList *tl) {
    int i;

    if (tl == NULL) {
        return;
    }

    for (i = 0; i < tl->size; i++) {
        team_free(tl->teams[i]);
    }

    free(tl->teams);
    free(tl);
}