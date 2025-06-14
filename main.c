// ----------- headers ----------- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

// ----- Creator Defined headers ----- //
#include "INCLUDE/fileio.h"


// --------- MAIN ---------- //
int main() {
    storage array;

    fetch_stringf("SRC/test.txt", &array);
    print_strinf(&array);
    
    printf("%zu", array.count);
    return 0;
}