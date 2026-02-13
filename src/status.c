#include "../include/ccgit.h"
#include <dirent.h>

void status(){
    FILE *index = fopen(INDEX_FILE, "r");
    if (!index){
        printf("No index found\n");
        return;
    }

    printf("Changes to be committed:\n");

    char sha[41], filename[256];

    while (fscanf(index, "%s %s", sha, filename) == 2){

        FILE *f = fopen(filename, "rb");

        if (!f){
            printf("  deleted: %s\n", filename);
            continue;
        }

        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        rewind(f);

        unsigned char *buffer = malloc(len);
        fread(buffer, 1, len, f);
        fclose(f);

        char new_sha[41];
        hash_object("blob", buffer, len, new_sha);

        if (strcmp(new_sha, sha) != 0)
            printf("  modified: %s\n", filename);

        free(buffer);
    }

    fclose(index);

    printf("\nUntracked files:\n");

    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL){

        if (entry->d_type != DT_REG)
            continue;

        if (strcmp(entry->d_name, "ccgit") == 0)
            continue;

        FILE *check = fopen(INDEX_FILE, "r");
        int found = 0;

        while (fscanf(check, "%s %s", sha, filename) == 2)
            if (strcmp(filename, entry->d_name) == 0)
                found = 1;

        fclose(check);

        if (!found)
            printf("  %s\n", entry->d_name);
    }

    closedir(dir);
}
