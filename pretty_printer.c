#include "pretty_printer.h"

// --- Utility Prototypes ---
static void printStringArray(char* stringArray[], const size_t size);
static void printIntegerArray(int* intArray, const size_t size);
static void printFloatArray(float* floatArray, const size_t size, const unsigned int precision);

static void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned int columnCount);

static int getLongestStringElementLength(char* stringArray[], const size_t size);

// --- API Function Definitions ---

void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned int numColumns) {

    // Guard
    if(dataArray == NULL) {
        printf("[ERROR] cannot print null data array as columns\n");
        return;
    }

    if(numColumns > MAX_COLUMNS) {
        printf("[ERROR] cannot print data array as %d columns", numColumns);
        return;
    }

    // Assign default number of columns
    if(numColumns == 0) {
        numColumns = DEFAULT_COLUMNS;
    }

    switch(type) {

        case STRING:
            printStringArrayAsColumns((char**)dataArray, arraySize, numColumns);
            break;
        
        case INTEGER:
            printf("integer\n");
            break;

        case FLOAT:
            printf("float\n");
            break;

        default:
            printf("[ERROR] Cannot pretty-print invalid type as columns\n");
            return;
    }
}

void printArray(void* dataArray, size_t arraySize, DataType type) {

    //Guard statements
    if(dataArray == NULL) {
        return;
    }

    if(arraySize == 0) {
        printf("empty array\n");
        return;
    }

    switch(type) {

        case STRING:
            printStringArray( (char**)dataArray, arraySize );
            break;
        
        case INTEGER:
            printIntegerArray( (int*)dataArray, arraySize );
            break;

        case FLOAT:
            printFloatArray( (float*)dataArray, arraySize, FLOAT_PRECISION );
            break;

        default:
            printf("[ERROR] cannot pretty-print invalid type as columns\n");
            return;
    }
}

// --- Utility Definitions ---

static void printStringArray(char* stringArray[], const size_t size) {

    // Guards
    if(stringArray == NULL) {
        printf("[ERROR] cannot print null string array\n");
        return;
    }

    if(size < 0) {
        printf("[ERROR] cannot print string array with size %ld\n", size);
        return;
    }

    if(size == 0) {
        printf("empty string array\n");
        return;
    }

    // ---

    int i;
    for(i = 0; i < size; ++i) {
        printf("%s\n", stringArray[i]);
    }

    printf("\n");

}

static void printIntegerArray(int* intArray, const size_t size) {
    
    int i;
    for(i = 0; i < size; ++i) {
        printf("%d\n", intArray[i]);
    }

    printf("\n");
}

static void printFloatArray(float* floatArray, const size_t size, const unsigned int precision) {

    char formatString[6];
    sprintf(formatString, "%%.%df\n", precision);

    int i;
    for(i = 0; i < size; ++i) {
        printf(formatString, floatArray[i]);
    }

    printf("\n");
}

static void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned int columnCount) {

    // Guards
    if(stringArray == NULL) {
        printf("[ERROR] cannot print null string array\n");
        return;
    }

    if(size < 0) {
        printf("[ERROR] cannot print string array with size %ld\n", size);
        return;
    }

    if(size == 0) {
        printf("empty string array\n");
        return;
    }

    // ---

    // Assign default column count
    if(columnCount == 0 || columnCount > MAX_COLUMNS) {
        columnCount = DEFAULT_COLUMNS;
    }

    int currentStringLength = 0;
    int fillChars = 0;
    char tempString[MAX_STRING_LENGTH + COLUMN_SPACER];

    int columnWidth = getLongestStringElementLength(stringArray, size) + COLUMN_SPACER;

    int i, j;
    for(i = 0; i < size; ++i) {
        currentStringLength = strlen(stringArray[i]);

        // Get number of fill-characters
        fillChars = columnWidth - currentStringLength;

        // Copy array string element to temp
        strcpy(tempString, stringArray[i]);

        // Concatenate fill characters to normalize string width
        for(j = 0; j < fillChars + COLUMN_SPACER; ++j) {
            strcat(tempString, FILL_CHAR);
        }

        // Conditional newlines
        if (    
            i != 0 
            && i % columnCount == 0
            && columnCount != 1 
        ){ 
            printf("\n"); 
        }

        if(columnCount == 1) {
            printf("\n");
        }

        // Print temp
        printf("%s", tempString);
    }

    printf("\n\n");
}

static int getLongestStringElementLength(char* stringArray[], const size_t size) {

    int longest = 0;
    int i, currentLength;
    for(i = 0; i < size; ++i) {
        currentLength = strlen(stringArray[i]);

        if(currentLength > longest) {
            longest = currentLength;
        }

        // Terminate the search if max length is found
        if(longest == MAX_STRING_LENGTH) {
            return longest;
        }
    }

    return longest;
}