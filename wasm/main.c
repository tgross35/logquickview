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

int main(int argc, char** argv) {
    // Setup how we should split
    ProcessOptions po;
    // po.line_deliminator = "\n";
    char* fd[] = {".", ".", " "};

    po.field_deliminators = fd;
    po.fdc = 3;
    // po.fdc = 0;

    printf("First: %s\n",fd[0]);
    printf("Second: %s\n",po.field_deliminators[0]);

    int linecount;

    FILE* fp = fopen(argv[1], "r");
    // fp = stdin;

    printf("Enter your data: \n");
    Line** lineStruct = processInputToStructs(fp, DEFAULT_BLOCK_SIZE, &linecount, &po);
    // Print full lines
    for (int i=0; i<linecount; ++i) printf("%ld: %s", lineStruct[i]->linenumber, lineStruct[i]->fullline);
    // Now print split lines
    for(int i=0; i<linecount; ++i) {        // Loop through line structs
        for (int j=0; j<po.fdc; ++j) {      // Loop through fields
            printf("%s:", lineStruct[i]->splitLine[j]);
        }
        printf("\n");
    }

    free(lineStruct);
    return 0;
}

Line**  processInputToStructs(FILE* fp, const size_t size, int* structcount, const ProcessOptions* po) {
    // lineArray is an array (pointer) of pointers
    Line** lineArray = malloc(ARRAY_BLOCK_SIZE * sizeof(Line *));
    // Go through and make room for the arrays. Set line_array[i] equal to this ptr
    for (int i=0; i<ARRAY_BLOCK_SIZE; ++i) {
        lineArray[i] = malloc(sizeof(Line));
        printf("Size: %lu", sizeof(Line));
        // // We need to make room for the array it holds too
        // char** ptr = malloc(sizeof(char[MAX_LINE_SIZE]) * MAX_NUM_FIELDS);
        // lineArray[i]->splitLine = ptr;
        // void* p1 = lineArray[i]->splitLine;
        // void* p2 = (lineArray[i]->splitLine)+sizeof(char[MAX_LINE_SIZE]);
        // void* p3 = lineArray[i]->splitLine[1];

        // printf("");
        
    }

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

        printf("%i\n", po->fdc);

        // If we never split, just make splitLine same as the full line
        if (po->fdc == 0) {
            lStc->splitLine[0] = malloc(sizeof(lStc->fullline));
            strcpy(lStc->splitLine[0], lStc->fullline);
        }
        else { // Otherwise we can run strtok at least once
            // We want to work with tmpstring since strtok will split whatever it touches
            char tmpString[MAX_LINE_SIZE];
            strcpy(tmpString, lStc->fullline);
            printf("Third: %s %s\n", tmpString, po->field_deliminators[0]);
            // First strtok iteration
            lStc->splitLine[0] = strtok(tmpString,po->field_deliminators[0]);
            printf("Made it!");
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