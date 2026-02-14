#ifndef MYGIT_H
#define MYGIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <zlib.h>
#include <time.h>

#define GIT_DIR ".git"
#define OBJECTS_DIR ".git/objects"
#define REFS_DIR ".git/refs/heads"
#define INDEX_FILE ".git/index"

void init_repo();
void add_file(const char *filename);
void commit_changes(const char *message);
void status();
void revert();
void log_history();
void remove_file(const char *filename);

void hash_object(const char *type, const unsigned char *data, size_t len, char *sha1_hex);
void write_object(const char *sha1_hex, const unsigned char *data, size_t len);

#endif
