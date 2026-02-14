#include "../include/mygit.h"

void log_history() {

    FILE *ref = fopen(".git/refs/heads/master", "r");
    if (!ref) {
        printf("No commits found\n");
        return;
    }

    char commit_sha[41];

    if (fscanf(ref, "%40s", commit_sha) != 1) {
        printf("No commits yet\n");
        fclose(ref);
        return;
    }

    fclose(ref);

    while (strlen(commit_sha) > 0) {

        printf("commit %s\n", commit_sha);

        char path[256];
        sprintf(path, "%s/%.2s/%s",
                OBJECTS_DIR,
                commit_sha,
                commit_sha + 2);

        FILE *file = fopen(path, "rb");
        if (!file) {
            printf("Commit object not found\n");
            return;
        }

        fseek(file, 0, SEEK_END);
        long len = ftell(file);
        rewind(file);

        unsigned char *compressed = malloc(len);
        fread(compressed, 1, len, file);
        fclose(file);

        unsigned long decompressed_len = 65536;
        unsigned char *decompressed = malloc(decompressed_len);

        if (uncompress(decompressed,
                       &decompressed_len,
                       compressed,
                       len) != Z_OK) {

            printf("Decompression failed\n");
            free(compressed);
            free(decompressed);
            return;
        }

        free(compressed);

        char *content = strchr((char *)decompressed, '\0');
        if (!content) {
            free(decompressed);
            return;
        }

        content++;  

        printf("%s\n", content);

        char *parent_line = strstr(content, "parent ");

        if (parent_line) 
            sscanf(parent_line, "parent %40s", commit_sha);
        else 
            commit_sha[0] = '\0';  

        free(decompressed);
    }
}
