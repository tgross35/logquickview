#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1000
// #define DEFAULT_NUM_ARRAYS 100
#define DEFAULT_BLOCK_SIZE 10
#define ARRAY_BLOCK_SIZE 100

typedef struct Line {
    long     linenumber;    // Keep track of the line number
    char**   linedata;      // Line data, sorted. Array of strings
    char*    fullline;      // String of the full line
} Line;

typedef struct ProcessOptions {
    char*   line_deliminator;       // How we should separate lines
    char**  field_deliminators;     // Array telling us how to split it
    int     fdc;                    // How many field deliminators
} ProcessOptions;

// void processData(char*);
Line** processInput(FILE* fp, size_t, int*, ProcessOptions*);

int main(int argc, char** argv) {
    // Setup how we should split
    po = ProcessOptions;
    po.line_deliminator = "\n";
    fd = [" ", " ", " "];
    po.field_deliminators = &fd;
    po.fdc = 3;

    char* input_data;
    int linecount;

    printf("Enter your data: ");
    input_data = processInputToStructs(stdin, DEFAULT_BLOCK_SIZE, &linecount, &po);
    printf("%s\n", input_data);
    // processData(input_data);

    free(input_data);
    return 0;
}

// char* processInput(FILE* fp, size_t size) {
//     //The size is extended by the input with the value of the provisional
//     char *str;
//     int ch;
//     size_t len = 0;
//     str = realloc(NULL, sizeof(char)*size);//size is start size
//     if(!str)return str;
//     while(EOF!=(ch=fgetc(fp))){
//         str[len++]=ch;
//         if(len==size){
//             str = realloc(str, sizeof(char)*(size+=16));
//             if(!str)return str;
//         }
//     }
//     str[len++]='\0';
//
//     return realloc(str, sizeof(char)*len);
// }

Line**  processInputToStructs(FILE* fp, size_t size, int* structcount, ProcessOptions* po) {
    // lineArray is an array (pointer) of pointers
    Line** lineArray = malloc(ARRAY_BLOCK_SIZE * sizeof(Line *));
    // Go through and make room for the arrays. Set line_array[i] equal to this ptr
    for (int i=0; i<ARRAY_BLOCK_SIZE; ++i) lineArray[i] = malloc(sizeof(Line));

    char tmpLine[MAX_LINE_SIZE]

    int structIndex=0, blockIndex=0;
    while (EOF != fgetc(fp)) {
        // If we hit our block size, we need to allocate more memory
        if (blockIndex == ARRAY_BLOCK_SIZE-1) {
            printf("Not yet implemented!");
            // Line **lineArray = malloc(ARRAY_BLOCK_SIZE * sizeof(Line *));
            // for (int i=0; i<ARRAY_BLOCK_SIZE; ++i) line_array[i] = malloc(sizeof(Line));
            blockIndex = 0;
        }

        // This is our line struct that we are working with. Also increment the index
        lStc = lineArray[structIndex++];

        // Read one line to the struct's fullline member
        fscanf(fp, po->line_deliminator, lStc->fullline);

        lStc->linenumber =
    }

    *structcount = structIndex;
    return lineArray;
}
