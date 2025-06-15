#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>

// Struct to store fetched file lines
typedef struct {
    char **elements; // Array of strings
    size_t count;       // Number of lines
    size_t capacity;
} StringStorage;

// user Usable Functions
int fetch_stringf(const char *, StringStorage *, size_t);
int print_elements(StringStorage *);
int free_array(StringStorage *);

// source owned function
int init_storage(StringStorage *);

// Global variable holding the file contents
extern StringStorage array;

#endif // FILEIO_H
