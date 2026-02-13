#include "../include/ccgit.h"

void commit_changes(const char *message){
    FILE *index = fopen(INDEX_FILE, "r");
    if (!index){
        printf("Nothing to commit\n");
        return;
    }

    char tree_content[8192] = "";
    char line[512];

    while (fgets(line, sizeof(line), index)) 
        strcat(tree_content, line);
    

    fclose(index);

    char tree_sha[41];
    hash_object("tree", (unsigned char *)tree_content, strlen(tree_content), tree_sha);

    char commit_content[8192];
    time_t now = time(NULL);

    sprintf(commit_content,
        "tree %s\n"
        "author You <you@example.com> %ld\n"
        "committer You <you@example.com> %ld\n\n"
        "%s\n",
        tree_sha, now, now, message);

    char commit_sha[41];
    hash_object("commit", (unsigned char *)commit_content, strlen(commit_content), commit_sha);

    FILE *ref = fopen(".git/refs/heads/master", "w");
    fprintf(ref, "%s\n", commit_sha);
    fclose(ref);

    printf("Committed: %s\n", commit_sha);

    FILE *clear = fopen(INDEX_FILE, "w");
    fclose(clear);
}
