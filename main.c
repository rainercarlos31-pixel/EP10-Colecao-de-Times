
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"
#include "teamlist.h"

int main(void) {
    FILE *file;
    TeamList *tl;
    Team *t;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *comma;
    char *name;
    int id;
    int i;
    int extra_spaces;
    int j;
    unsigned char *p;

    file = fopen("teams.csv", "r");

    if (file == NULL) {
        printf("Erro ao abrir teams.csv\n");
        return 1;
    }

    tl = tl_create();

    if (tl == NULL) {
        fclose(file);
        return 1;
    }

    while ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\r\n")] = '\0';

        comma = strchr(line, ',');

        if (comma == NULL) {
            continue;
        }

        *comma = '\0';

        id = atoi(line);
        name = comma + 1;

        t = team_create(id, name);

        if (t == NULL) {
            free(line);
            fclose(file);
            tl_free(tl);
            return 1;
        }

        tl_append(tl, t);
    }

    free(line);
    fclose(file);

    printf("%-3s %-15s %3s %3s %3s %3s %3s %3s %3s\n",
           "ID", "Time", "V", "E", "D",
           "GM", "GS", "S", "PG");

    for (i = 0; i < tl_size(tl); i++) {
        t = tl_get(tl, i);

        extra_spaces = 0;
        p = (unsigned char *) team_name(t);

        while (*p != '\0') {
            if ((*p & 0xC0) == 0x80) {
                extra_spaces++;
            }

            p++;
        }

        printf("%-3d %-15s", team_id(t), team_name(t));

        for (j = 0; j < extra_spaces; j++) {
            printf(" ");
        }

        printf(" %3d %3d %3d %3d %3d %3d %3d\n",
               team_wins(t),
               team_draws(t),
               team_losses(t),
               team_goals_scored(t),
               team_goals_conceded(t),
               team_goals_scored(t) - team_goals_conceded(t),
               3 * team_wins(t) + team_draws(t));
    }

    tl_free(tl);

    return 0;
}
