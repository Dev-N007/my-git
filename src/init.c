#include "../include/ccgit.h"

void init_repo(){
    if (access(GIT_DIR, F_OK) == 0){
        printf("Repository already exists\n");
        return;
    }

    mkdir(GIT_DIR, 0700);
    mkdir(OBJECTS_DIR, 0700);
    mkdir(".git/refs", 0700);
    mkdir(REFS_DIR, 0700);

    FILE *head = fopen(".git/HEAD", "w");
    fprintf(head, "ref: refs/heads/master\n");
    fclose(head);

    FILE *master = fopen(".git/refs/heads/master", "w");
    fclose(master);

    FILE *index = fopen(INDEX_FILE, "w");
    fclose(index);

    printf("Initialized empty repository\n");
}
