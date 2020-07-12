#include "pretty_printer.h"

static void initStringArray(char* strArray[], size_t size, char* initVal) {
    int i = 0;
    char testString[MAX_STRING_LENGTH];

    for(i = 0; i < size; ++i) {
        sprintf(testString, "hello %d", i);
        strArray[i] = testString;
        printf("testString = \"%s\"\nstrArray[%d] = \"%s\"\naddr = %p\n\n", testString, i, strArray[i], &strArray[i]);
    }
}

static void printStringArray(char* strArray[], size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        printf("%d = %s\n", i, strArray[i]);
    }
}

int main() {
    
    #define SIZE_3 3

    char* stringArray_size3[SIZE_3];

    //initialize string array elements (same as initStringArray() just pulled out for debugging purposes)
    int i;
    for(i = 0; i < SIZE_3; ++i) {
        char testString[MAX_STRING_LENGTH];
        sprintf(testString, "hello %d", i);
        stringArray_size3[i] = testString;
        printf("testString = \"%s\"\nstrArray[%d] = \"%s\"\naddr = %p\n\n", testString, i, stringArray_size3[i], &stringArray_size3[i]);
    }

    //Debug print
    printf (
        "%p = %s\n%p = %s\n%p = %s\n%p = %s\n", 
        &stringArray_size3, *stringArray_size3,
        &stringArray_size3[0], stringArray_size3[0],
        &stringArray_size3[1], stringArray_size3[1],
        &stringArray_size3[2], stringArray_size3[2]
    );

    return 0;
}
