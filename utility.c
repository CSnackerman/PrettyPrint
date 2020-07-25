#include "utility.h"

void printTestHeader(const char* testName) {

    int length = strlen(testName);
    char extendedName[length + 6];
    char printBar[length + 6];

    sprintf(extendedName, " | %s |", testName);

    strcpy(printBar, " ");

    int i;
    for(i = 0; i < length + 4; ++i) {
        strcat(printBar, "-");
    }

    printf("%s\n%s\n%s\n\n", printBar, extendedName, printBar);
}

void incrementalStringArrayInit(char* stringArray[], const size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        stringArray[i] = malloc(sizeof(char*) * MAX_STRING_LENGTH);
        sprintf(stringArray[i], "string #%.2d", i);
    }
}

void incrementalIntArrayInit(int** intArray, const size_t size) {

    if(*intArray == NULL) {
        *intArray = malloc(sizeof(int) * size);
    }
    
    int i;
    for(i = 0; i < size; ++i) {
        (*intArray)[i] = i;
    }
}

void incrementalFloatArrayInit(float** floatArray, const size_t size) {
    if(*floatArray == NULL) {
        *floatArray = malloc(sizeof(float) * size);
    }

    int i;
    for(i = 0; i < size; ++i) {
        (*floatArray)[i] = (float)i;
    }
}

void randomStringArrayInit(char* stringArray[], const size_t size) {
    char randChar;
    int i, j, length;
    for(i = 0; i < size; ++i) {
        
        // Randomly generate a string length
        length = randRange(2, MAX_STRING_LENGTH);

        // Allocate the string
        stringArray[i] = malloc(sizeof(char*) * length);

        // Fill the string
        for(j = 0; j < length - 1; ++j) {

            // Assign non-whitespace character
            randChar = (char)randRange(33, 126);
            stringArray[i][j] = randChar;
        }

        // Null terminate the string
        stringArray[i][length -1] = '\0';
    }
}

void cleanupStringArray(char* stringArray[], const size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        free(stringArray[i]);
    }
}

void cleanupArray(void* array, const size_t size, DataType type) {

    switch(type) {

        case STRING:
            if(size == 0) {
                printf("[ERROR] size of string array required for cleanup\n");
                return;
            }

            cleanupStringArray((char**)array, size);
        return;

        case INTEGER:
            free((int*)array);
        return;

        case FLOAT:
            free((float*)array);
        return;

        default:
            printf("[ERROR] cannot free array of invalid type\n");
            return;
    }
}

int randRange(int lower, int upper) {
    
    // Guard
    if(lower > upper) {
        printf("[ERROR] cannot generate a number between negative range\n");
        return 255;
    }

    int range = upper - lower;

    return rand() % (range + 1) + lower;
}

void printStringArray(char* stringArray[], const size_t size) {

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

void printIntegerArray(int* intArray, const size_t size) {
    
    int i;
    for(i = 0; i < size; ++i) {
        printf("%d\n", intArray[i]);
    }

    printf("\n");
}

void printFloatArray(float* floatArray, const size_t size, const unsigned precision) {

    char formatString[6];
    sprintf(formatString, "%%.%df\n", precision);

    int i;
    for(i = 0; i < size; ++i) {
        printf(formatString, floatArray[i]);
    }

    printf("\n");
}

void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned columnCount) {

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

void printNumericArrayAsColumns(void* dataArray, DataType type, const size_t size, unsigned columnCount) {

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

int getColumnWidth(void* dataArray, const size_t size, DataType type) {

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

int getLongestStringElementLength(char* stringArray[], const size_t size) {

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

int getStringLengthOfLargestInt(int* intArray, const size_t size) {
    
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

int getStringLengthOfLargestFloat(float* floatArray, const size_t size) {

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


