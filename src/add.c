#include "../include/ccgit.h"

void add_file(const char *filename){
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(len);
    fread(buffer, 1, len, file);
    fclose(file);

    char sha1_hex[41];
    hash_object("blob", buffer, len, sha1_hex);

    FILE *index = fopen(INDEX_FILE, "a");
    fprintf(index, "%s %s\n", sha1_hex, filename);
    fclose(index);

    free(buffer);

    printf("Added %s\n", filename);
}
