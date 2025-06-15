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

// fetch file strings into an array, Returns 0 on success, 1 on failure
int fetch_stringf(const char *filename, StringStorage *array, size_t bufferSize) {

    FILE *fp = fopen(filename, "r");
    if(!fp) return 1;

    init_storage(array);

    char buffer[bufferSize];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // --------- expand if capacity maximum is reached --------- //
        if (array->count >= array->capacity) {
            size_t new_capacity = array->capacity * 2;
            char **tmp = (char **)realloc(array->elements, array->capacity * sizeof(char *));
            // ------ error handling reallocation ---------- //
            if (!tmp) {
                perror("error reallocation");
                free_array(array);
                fclose(fp);
                return 1;
            }
            array->elements = tmp;
            array->capacity = new_capacity;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        array->elements[array->count] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        // error handling
        if (!array->elements[array->count]) {
            perror("error allocation");
            free_array(array);
            fclose(fp);
            return 1;
        }
        strcpy(array->elements[array->count], buffer);
        array->count++;
    }

    // shrink the memory according only to the count of elements exist on array, boom frees and save ram so much
    char **shrink = realloc(array->elements, array->count * sizeof(char *));
    // error handlind Returns 1 on failure
    if (!shrink) {
        perror("error shrinking");
        free_array(array);
        fclose(fp);
        return 1;
    }
    array->elements = shrink;

    fclose(fp);
    return 0;
}

// prints array strings, Returns 0 on success, 1 on failure
int print_elements(StringStorage *array) {
    if (!array || !array->elements) { fprintf(stderr, "invalid array to print.\n"); return 1; }
    for (size_t i = 0; i < array->count; i++) {
        puts(array->elements[i]);
    }

    return 0;
}

// initialized starter value
int init_storage(StringStorage *array) {
    if (!array) return 1;
    array->capacity = 128;
    array->elements = (char **)malloc(array->capacity * sizeof(char *));
    if(!array->elements) { perror("failed allocation"); return 1; }
    array->count = 0;

    return 0;
}

// free array, Returns 0 on success, 1 on failure
int free_array(StringStorage *array) {
    if (!array || !array->elements) return 1;
    for (size_t i = 0; i < array->count; i++) free(array->elements[i]);
    free(array->elements);
    array->elements = NULL;
    array->count = 0;

    return 0;
}


