#include "../include/mygit.h"

void write_object(const char *sha1_hex, const unsigned char *data, size_t len){
    char dir[256], path[256];

    snprintf(dir, sizeof(dir), "%s/%.2s", OBJECTS_DIR, sha1_hex);
    mkdir(dir, 0700);

    snprintf(path, sizeof(path), "%s/%s", dir, sha1_hex + 2);

    FILE *file = fopen(path, "wb");

    uLongf compressed_len = compressBound(len);
    unsigned char *compressed = malloc(compressed_len);

    compress(compressed, &compressed_len, data, len);

    fwrite(compressed, 1, compressed_len, file);

    fclose(file);
    free(compressed);
}
