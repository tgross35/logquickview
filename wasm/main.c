#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1000
// #define DEFAULT_NUM_ARRAYS 100
#define DEFAULT_BLOCK_SIZE 10
#define ARRAY_BLOCK_SIZE 100
#define MAX_DELIM_SIZE 10
#define MAX_NUM_FIELDS 20
#define SPLITOFFSET sizeof(char[MAX_LINE_SIZE])

typedef struct Line {
    long     linenumber;    // Keep track of the line number
    char*    splitLine[MAX_NUM_FIELDS];      // Line data, sorted. Array of ptrs to string
    char     fullline[MAX_LINE_SIZE];      // String of the full line
} Line;

typedef struct ProcessOptions {
    // char*   line_deliminator;       // How we should separate lines
    char**  field_deliminators;     // Array telling us how to split it
    int     fdc;                    // How many field deliminators
} ProcessOptions;

// void processData(char*);
Line** processInputToStructs(FILE* fp, const size_t, int*, const ProcessOptions*);
char* strtokm(char *str, const char *delim);

#ifdef __EMSCRIPTEN__
char* main(char* filename) {)
#else
int main(int argc, char** argv) {
#endif
    // Setup how we should split
    ProcessOptions po;
    // po.line_deliminator = "\n";
    char* fd[] = {" ", " ", " ", " "};

    po.field_deliminators = fd;
    po.fdc = 4;

    int linecount;

    #ifdef __EMSCRIPTEN__
    FILE* fp = fopen(filename, "r");
    #else
    FILE* fp = fopen(argv[1], "r");
    #endif

    // fp = stdin;

    printf("Enter your data: \n");
    Line** lineStruct = processInputToStructs(fp, DEFAULT_BLOCK_SIZE, &linecount, &po);

    char* outStr = malloc(sizeof(char[MAX_LINE_SIZE * ARRAY_BLOCK_SIZE]));

    // Print full lines
    for (int i=0; i<linecount; ++i) {
        printf("%ld: %s", lineStruct[i]->linenumber, lineStruct[i]->fullline);
    }
    // Now print split lines
    for(int i=0; i<linecount; ++i) {        // Loop through line structs
        strcat(outStr, "<tr><td class='line-number'>");

        int lineNumber = i+1;
        int length = snprintf(NULL, 0, "%d", lineNumber);
        char* p = malloc(length + 1);
        snprintf(p, length + 1, "%d", lineNumber);
        strcat(outStr, p);
        free(p);
        strcat(outStr, "</td>");

        for (int j=0; j<po.fdc; ++j) {      // Loop through fields
            strcat(outStr, "<td>");
            strcat(outStr,lineStruct[i]->splitLine[j]);
            strcat(outStr, "</td>");
            printf("%s", lineStruct[i]->splitLine[j]);
        }
        strcat(outStr, "</tr>");
        printf("\n");
    }

    free(lineStruct);

    printf("Final:\n %s", outStr);

    #ifdef __EMSCRIPTEN__
    return outStr;
    #else
    return 0;
    #endif
}

Line**  processInputToStructs(FILE* fp, const size_t size, int* structcount, const ProcessOptions* po) {
    // lineArray is an array (pointer) of pointers
    Line** lineArray = malloc(ARRAY_BLOCK_SIZE * sizeof(Line *));
    // Go through and make room for the arrays. Set line_array[i] equal to this ptr
    for (int i=0; i<ARRAY_BLOCK_SIZE; ++i) {
        lineArray[i] = malloc(sizeof(Line));
    }

    Line* item0 = lineArray[0];
    Line* item1 = lineArray[1];
    Line* item2 = lineArray[2];
    Line* item3 = lineArray[3];

    // char tmpString[MAX_LINE_SIZE];
    int structIndex=0, blockIndex=0;
    Line* lStc = lineArray[structIndex];    // Get the first item from the list
    while (fgets(lStc->fullline, MAX_LINE_SIZE, fp)) {
        // If we hit our block size, we need to allocate more memory
        if (blockIndex == ARRAY_BLOCK_SIZE-1) {
            printf("Not yet implemented!");
            // Line **lineArray = malloc(ARRAY_BLOCK_SIZE * sizeof(Line *));
            // for (int i=0; i<ARRAY_BLOCK_SIZE; ++i) line_array[i] = malloc(sizeof(Line));
            blockIndex = 0;
        }

        // Setup our splitline; make the first element equal to the full line
        lStc->splitLine[0] = malloc(sizeof(lStc->fullline));
        strcpy(lStc->splitLine[0], lStc->fullline);

        // If we have deliminators, we want to go through and split it
        if (po->fdc > 0) {
            // First strtok iteration
            lStc->splitLine[0] = strtok(lStc->splitLine[0],po->field_deliminators[0]);

            // Iterate through delims, split the line. If fdc=1, we never run
            for (int i=1; i<po->fdc; ++i) {
                lStc->splitLine[i] = strtok(NULL, po->field_deliminators[i]);
            }
        }

        
        lStc->linenumber = ++structIndex;       // Structindex+1 will be logical line #
        lStc = lineArray[structIndex];          // For the next run we want the next line

        // lStc->fullline;

    }

    *structcount = structIndex - 1; // The index will be one higher than needed
    return lineArray;
}

char *strtokm(char *str, const char *delim)
{
    static char *tok;
    static char *next;
    char *m;

    if (delim == NULL) return NULL;

    tok = (str) ? str : next;
    if (tok == NULL) return NULL;

    m = strstr(tok, delim);

    if (m) {
        next = m + strlen(delim);
        *m = '\0';
    } else {
        next = NULL;
    }

    return tok;
}