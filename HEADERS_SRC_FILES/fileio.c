#include "../HEADERS/fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// ----- RULES ------- //
// 1. must declare the struct "StringStorage array;" on main()

// ------ USABLE FUNCTIONS FOR USER ------- //
// fetch_stringf()
// free_array()
// print_elements()


// --------------------- INTIALIZED STARTER DATA/MEMORY ---------------------- //

// initialize array of strings
int init_stringf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer) return 1;

    FileInfoBuffer->string_capacity = 128; // capacity

    FileInfoBuffer->strings = (char **)malloc(FileInfoBuffer->string_capacity * sizeof(char *)); // initialize array of strings
    if(!FileInfoBuffer->strings) { perror("failed allocation"); free_stringsf(FileInfoBuffer); return 1; }

    FileInfoBuffer->string_line_count = 0;

    return 0;
}

// initialized array of chars
int init_charf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer) return 1;

    FileInfoBuffer->char_capacity = 128; // capacity

    FileInfoBuffer->chars = (char *)malloc(FileInfoBuffer->char_capacity * sizeof(char)); // initialized array of chars
    if(!FileInfoBuffer->chars) { perror("failed allocation"); free_charsf(FileInfoBuffer); return 1; }

    FileInfoBuffer->char_line_count = 0;

    return 0;
}

// initialized array of int
int init_integerf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer) return 1;

    FileInfoBuffer->integer_capacity = 128; // capacity

    FileInfoBuffer->integers = (int *)malloc(FileInfoBuffer->integer_capacity * sizeof(int)); // initialized array of int
    if(!FileInfoBuffer->integers) { perror("failed allocation"); free_integersf(FileInfoBuffer);  return 1; }

    FileInfoBuffer->integer_line_count = 0;

    return 0;
}

// ----------------------------------------- FETCH --------------------------------------- //

// fetch file strings into an array, Returns 0 on success, 1 on failure
int fetch_stringf(const char *filename, FileInfoBuffer *FileInfoBuffer, size_t bufferSize) {

    FILE *fp = fopen(filename, "r");
    if(!fp) return 1;

    init_stringf(FileInfoBuffer);

    char buffer[bufferSize];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // --------- expand if capacity maximum is reached --------- //
        if (FileInfoBuffer->string_line_count >= FileInfoBuffer->string_capacity) {
            size_t new_capacity = FileInfoBuffer->string_capacity * 2;
            char **tmp = (char **)realloc(FileInfoBuffer->strings, new_capacity * sizeof(char *));
            // ------ error handling reallocation ---------- //
            if (!tmp) {
                perror("error reallocation");
                free_stringsf(FileInfoBuffer);
                fclose(fp);
                return 1;
            }
            FileInfoBuffer->strings = tmp;
            FileInfoBuffer->string_capacity = new_capacity;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        FileInfoBuffer->strings[FileInfoBuffer->string_line_count] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        // error handling
        if (!FileInfoBuffer->strings[FileInfoBuffer->string_line_count]) {
            perror("error allocation");
            free_stringsf(FileInfoBuffer);
            fclose(fp);
            return 1;
        }
        strcpy(FileInfoBuffer->strings[FileInfoBuffer->string_line_count], buffer);
        FileInfoBuffer->string_line_count++;
    }

    // shrink the memory according only to the count of elements exist on array, boom frees and save ram so much
    char **shrink = realloc(FileInfoBuffer->strings, FileInfoBuffer->string_line_count * sizeof(char *));
    // error handlind Returns 1 on failure
    if (!shrink) {
        perror("error shrinking");
        free_stringsf(FileInfoBuffer);
        fclose(fp);
        return 1;
    }
    FileInfoBuffer->strings = shrink;

    fclose(fp);
    return 0;
}


// ------------------------------- LOG --------------------------------- //

// prints array strings, Returns 0 on success, 1 on failure
int print_stringf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer || !FileInfoBuffer->strings) { fprintf(stderr, "invalid array to print.\n"); return 1; }
    for (size_t i = 0; i < FileInfoBuffer->string_line_count; i++) {
        puts(FileInfoBuffer->strings[i]);
    }

    return 0;
}

// -------------------------- FREE MEMORY ---------------------------- //

// free all, Returns 0 on success, 1 on failure
int free_allf(FileInfoBuffer *FileInfoBuffer) {
    free_stringsf(FileInfoBuffer);
    free_charsf(FileInfoBuffer);
    free_integersf(FileInfoBuffer);

    return  0;
}

// free strings, Returns 0 on success, 1 on failure
int free_stringsf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer || !FileInfoBuffer->strings) return 1;
    for (size_t i = 0; i < FileInfoBuffer->string_line_count; i++) { 
        free(FileInfoBuffer->strings[i]);
    }
    free(FileInfoBuffer->strings);
    FileInfoBuffer->strings = NULL;
    FileInfoBuffer->string_line_count = 0;

    return 0;
}

// free chars, Returns 0 on success, 1 on failure
int free_charsf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer || !FileInfoBuffer->chars) return 1;
    free(FileInfoBuffer->chars);
    FileInfoBuffer->chars = NULL;
    FileInfoBuffer->char_line_count = 0;
    return 0;
}

// free integers, Returns 0 on success, 1 on failure
int free_integersf(FileInfoBuffer *FileInfoBuffer) {
    if (!FileInfoBuffer || !FileInfoBuffer->integers) return 1;
    free(FileInfoBuffer->integers);
    FileInfoBuffer->integers = NULL;
    FileInfoBuffer->integer_line_count = 0;

    return 0;
}