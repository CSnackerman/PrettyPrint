#include "pretty_printer.h"

// --- Utility Prototypes ---
static void printStringArray(char* stringArray[], const size_t size);
static void printIntegerArray(int* intArray, const size_t size);
static void printFloatArray(float* floatArray, const size_t size, const unsigned precision);

static void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned columnCount);
static void printNumericArrayAsColumns(void* dataArray, DataType type, const size_t size, unsigned columnCount);

static int getColumnWidth(void* dataArray, const size_t size, DataType type);
static int getLongestStringElementLength(char* stringArray[], const size_t size);
static int getStringLengthOfLargestInt(int* intArray, const size_t size);
static int getStringLengthOfLargestFloat(float* floatArray, const size_t size);

// --- API Function Definitions ---

void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned numColumns) {

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
            printNumericArrayAsColumns((int*)dataArray, INTEGER, arraySize, numColumns);
            break;

        case FLOAT:
            printNumericArrayAsColumns((float*)dataArray, FLOAT, arraySize, numColumns);
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

static void printFloatArray(float* floatArray, const size_t size, const unsigned precision) {

    char formatString[6];
    sprintf(formatString, "%%.%df\n", precision);

    int i;
    for(i = 0; i < size; ++i) {
        printf(formatString, floatArray[i]);
    }

    printf("\n");
}

static void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned columnCount) {

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
    int numFillChars = 0;
    char tempString[MAX_STRING_LENGTH + COLUMN_SPACER];

    int columnWidth = getColumnWidth(stringArray, size, STRING);

    int i, j;
    for(i = 0; i < size; ++i) {
        currentStringLength = strlen(stringArray[i]);

        // Get number of fill-characters
        numFillChars = columnWidth - currentStringLength;

        // Copy array string element to temp
        strcpy(tempString, stringArray[i]);

        // Concatenate fill characters to normalize string width
        for(j = 0; j < numFillChars; ++j) {
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

static void printNumericArrayAsColumns(void* dataArray, DataType type, const size_t size, unsigned columnCount) {

    // Set the typename
    char typeName[8];
    switch(type) {

        case INTEGER: 
            sprintf(typeName, "%s", "integer"); 
            break;

        case FLOAT:
            sprintf(typeName, "%s", "float");
            break;
    }

    // Guards
    if(dataArray == NULL) {
        printf("[ERROR] cannot print null %s array\n", typeName);
    }

    if(size < 0) {
        printf("[ERROR] cannot print %s array with size %ld\n", typeName, size);
        return;
    }

    if(size == 0) {
        printf("empty %s array\n", typeName);
        return;
    }

    // ---

    // Assign default column count
    if(columnCount == 0 || columnCount > MAX_COLUMNS) {
        columnCount = DEFAULT_COLUMNS;
    }


    // Get the column width
    int columnWidth = 0;
    switch(type) {

        case INTEGER:
            columnWidth = getColumnWidth((int*)dataArray, size, INTEGER);
            break;

        case FLOAT:
            columnWidth = getColumnWidth((float*)dataArray, size, FLOAT);
            break;
    }

    // Set the array pointers
    int* intArrayPtr = NULL;
    float* floatArrayPtr = NULL;

    switch(type) {

        case INTEGER:
            intArrayPtr = dataArray;
            break;

        case FLOAT:
            floatArrayPtr = dataArray;
            break;
    }

    // Create float format string
    char floatFormat[8] = "";
    if(type == FLOAT) {
        sprintf(floatFormat, "%%.%df", FLOAT_PRECISION);
    }
    
    // Iterate the array
    int currentStringLength = 0;
    int numFillChars = 0;
    char tempString[MAX_STRING_LENGTH + COLUMN_SPACER] = "";
    int i, j;
    for(i = 0; i < size; ++i) {

        // Get length of string representation of current int
        switch(type) {

            case INTEGER:
                sprintf(tempString, "%d", intArrayPtr[i]);
                break;

            case FLOAT:
                sprintf(tempString, floatFormat, floatArrayPtr[i]);
                break;
        }

        currentStringLength = strlen(tempString);

        // Get number of fill-characters
        numFillChars = columnWidth - currentStringLength;

        // Concatenate fill characters to normalize string width
        for(j = 0; j < numFillChars; ++j) {
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

static int getColumnWidth(void* dataArray, const size_t size, DataType type) {

    int width = 0;
    
    switch(type) {

        case STRING:
            width = getLongestStringElementLength((char**)dataArray, size);
            break;

        case INTEGER:
            width = getStringLengthOfLargestInt((int*)dataArray, size);
            break;

        case FLOAT:
            width = getStringLengthOfLargestFloat((float*)dataArray, size);
            break;
    }

    return width + COLUMN_SPACER;
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

static int getStringLengthOfLargestInt(int* intArray, const size_t size) {
    
    // Find largest value in the array
    int i, largest = 0;
    for(i = 0; i < size; ++i) {

        if(intArray[i] > largest) {
            largest = intArray[i];
        }
    }

    // Get string representation of largest value.
    char buffer[16] = "";
    sprintf(buffer, "%d", largest);
    
    return strlen(buffer);
}

static int getStringLengthOfLargestFloat(float* floatArray, const size_t size) {

    // Find largest value in the array
    int i; 
    float largest = 0;
    for(i = 0; i < size; ++i) {

        if(floatArray[i] > largest) {
            largest = floatArray[i];
        }
    }

    // Create format string
    char format[8];
    sprintf(format, "%%.%df", FLOAT_PRECISION);

    // Get string representation of largest value.
    char buffer[16] = "";
    sprintf(buffer, format, largest);
    
    return strlen(buffer);
}


