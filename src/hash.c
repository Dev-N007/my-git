#include "../include/ccgit.h"

void hash_object(const char *type, const unsigned char *data, size_t len, char *sha1_hex){
    char header[64];
    sprintf(header, "%s %ld", type, len);

    size_t total_len = strlen(header) + 1 + len;
    unsigned char *store = malloc(total_len);

    memcpy(store, header, strlen(header));
    store[strlen(header)] = '\0';
    memcpy(store + strlen(header) + 1, data, len);

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(store, total_len, hash);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(sha1_hex + (i * 2), "%02x", hash[i]);

    sha1_hex[40] = '\0';

    write_object(sha1_hex, store, total_len);

    free(store);
}
