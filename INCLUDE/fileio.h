#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>

// Struct to store fetched file lines
typedef struct {
    char **elements; // Array of strings
    size_t count;       // Number of lines
    size_t capacity;
} storage;

// Function: fetch strings from a file into 'array'
int fetch_stringf(const char *, storage *);
int print_strinf(storage *);
int free_storage(storage *);
int init_storage(storage *);
// Global variable holding the file contents
extern storage array;

#endif // FILEIO_H
