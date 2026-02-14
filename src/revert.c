#include "../include/mygit.h"

void revert(){
    FILE *ref = fopen(".git/refs/heads/master", "r");
    if (!ref) {
        printf("No commits found\n");
        return;
    }

    char commit_sha[41];
    if (fscanf(ref, "%40s", commit_sha) != 1) {
        printf("Invalid HEAD reference\n");
        fclose(ref);
        return;
    }
    fclose(ref);

    char path[256];
    sprintf(path, "%s/%.2s/%s", OBJECTS_DIR, commit_sha, commit_sha + 2);

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

    if (uncompress(decompressed, &decompressed_len, compressed, len) != Z_OK) {
        printf("Failed to decompress commit\n");
        free(compressed);
        free(decompressed);
        return;
    }

    free(compressed);

    char *content_start = strchr((char *)decompressed, '\0');
    if (!content_start) {
        printf("Invalid commit format\n");
        free(decompressed);
        return;
    }
    content_start++;  // move past null byte

    char *tree_line = strstr(content_start, "tree ");
    if (!tree_line) {
        printf("tree line not found in commit\n");
        free(decompressed);
        return;
    }

    if (!tree_line) {
        printf("Invalid commit format\n");
        free(decompressed);
        return;
    }

    char tree_sha[41];
    sscanf(tree_line, "tree %40s", tree_sha);

    free(decompressed);

    sprintf(path, "%s/%.2s/%s", OBJECTS_DIR, tree_sha, tree_sha + 2);

    file = fopen(path, "rb");
    if (!file) {
        printf("Tree object not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    len = ftell(file);
    rewind(file);

    compressed = malloc(len);
    fread(compressed, 1, len, file);
    fclose(file);

    decompressed_len = 65536;
    decompressed = malloc(decompressed_len);

    if (uncompress(decompressed, &decompressed_len, compressed, len) != Z_OK) {
        printf("Failed to decompress tree\n");
        free(compressed);
        free(decompressed);
        return;
    }

    free(compressed);

    content_start = strchr((char *)decompressed, '\0');
    if (!content_start) {
        printf("Invalid tree format\n");
        free(decompressed);
        return;
    }

    content_start++;

    char sha[41], filename[256];
    char *line = strtok(content_start, "\n");

    while (line) {

        if (sscanf(line, "%40s %255s", sha, filename) == 2) {

            sprintf(path, "%s/%.2s/%s", OBJECTS_DIR, sha, sha + 2);

            FILE *blob = fopen(path, "rb");
            if (!blob) {
                line = strtok(NULL, "\n");
                continue;
            }

            fseek(blob, 0, SEEK_END);
            len = ftell(blob);
            rewind(blob);

            unsigned char *blob_compressed = malloc(len);
            fread(blob_compressed, 1, len, blob);
            fclose(blob);

            unsigned long blob_decompressed_len = 65536;
            unsigned char *blob_decompressed = malloc(blob_decompressed_len);

            if (uncompress(blob_decompressed, &blob_decompressed_len,
                           blob_compressed, len) == Z_OK) {

                char *file_content = strchr((char *)blob_decompressed, '\0');
                if (file_content) {
                    file_content++;

                    FILE *out = fopen(filename, "wb");
                    if (out) {
                        fwrite(file_content, 1,
                               blob_decompressed_len - (file_content - (char *)blob_decompressed),
                               out);
                        fclose(out);
                    }
                }
            }

            free(blob_compressed);
            free(blob_decompressed);
        }

        line = strtok(NULL, "\n");
    }

    free(decompressed);

    printf("Reverted to last commit\n");
}
