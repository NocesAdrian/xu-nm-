#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>

// Struct to store fetched file lines
typedef struct {
    char **strings;         // Array of strings
    char *chars;            // Array of chars
    int *integers;          // Array of integers

    size_t string_line_count;      // Number of lines
    size_t char_line_count;      // Number of lines
    size_t integer_line_count;      // Number of lines
    
    size_t string_capacity;        // capacity
    size_t char_capacity;        // capacity
    size_t integer_capacity;        // capacity
} FileInfoBuffer;

// user Usable Functions
int fetch_stringf(const char *, FileInfoBuffer *, size_t);         // (filename, FileInfo, bytes per line)
int print_stringf(FileInfoBuffer *);                               // (FileInfo)  

int free_allf(FileInfoBuffer *FileInfoBuffer);                    // free all
int free_stringsf(FileInfoBuffer *);                             // (FileInfo)
int free_charsf(FileInfoBuffer *);                               // (FileInfo)
int free_integersf(FileInfoBuffer *);                            // (FileInfo)

// source owned function
int init_stringf(FileInfoBuffer *);                             // (FileInfo)
int init_charf(FileInfoBuffer *);                             // (FileInfo)
int init_integerf(FileInfoBuffer *);                             // (FileInfo)

#endif // FILEIO_H
