#include "../include/mygit.h"

void remove_file(const char *filename) {
    if (remove(filename) != 0) 
        printf("File not found or cannot remove\n");

    FILE *index = fopen(INDEX_FILE, "r");
    if (!index) {
        printf("Index not found\n");
        return;
    }

    FILE *temp = fopen(".git/index.tmp", "w");
    if (!temp) {
        fclose(index);
        return;
    }

    char sha[41], name[256];

    while (fscanf(index, "%40s %255s", sha, name) == 2) 
        if (strcmp(name, filename) != 0)
            fprintf(temp, "%s %s\n", sha, name);

    fclose(index);
    fclose(temp);

    remove(INDEX_FILE);
    rename(".git/index.tmp", INDEX_FILE);

    printf("Removed %s\n", filename);
}
