// ----------- headers ----------- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

// ----- Creator Defined headers ----- //
#include "HEADERS/fileio.h"


// --------- MAIN ---------- //
int main() {

    FileInfoBuffer StringBuffer;
    fetch_stringf("DATA/src/test.txt", &StringBuffer, 1500);
    print_stringf(&StringBuffer);
    free_stringsf(&StringBuffer);
    
    return 0;
}