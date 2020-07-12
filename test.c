#include "pretty_printer.h"

// Tests
static void testPrintAllStringElementsOfArray();

// Utility Functions
static void printTestHeader(const char* testName);
static void incrementalStringArrayInit(char* stringArray[], const size_t size);
static void cleanupStringArray(char* stringArray[], const size_t size);

// ---

int main() {

    // Run Tests
    testPrintAllStringElementsOfArray();

    return 0;
}

// --- Test Definitions ---

static void testPrintAllStringElementsOfArray() {

    printTestHeader(__func__);

    const size_t SIZE_0  = 0;
    const size_t SIZE_1  = 1;
    const size_t SIZE_3  = 3;
    const size_t SIZE_10 = 10;

    char* stringArray_size0   [SIZE_0];
    char* stringArray_size1   [SIZE_1];
    char* stringArray_size3   [SIZE_3];
    char* stringArray_size10  [SIZE_10];

    // Init
    incrementalStringArrayInit(stringArray_size0, SIZE_0);
    incrementalStringArrayInit(stringArray_size1, SIZE_1);
    incrementalStringArrayInit(stringArray_size3, SIZE_3);
    incrementalStringArrayInit(stringArray_size10, SIZE_10);

    // Print
    printArray(stringArray_size0, SIZE_0, STRING);
    printArray(stringArray_size1, SIZE_1, STRING);
    printArray(stringArray_size3, SIZE_3, STRING);
    printArray(stringArray_size10, SIZE_10, STRING);

    // Cleanup
    cleanupStringArray(stringArray_size0, SIZE_0);
    cleanupStringArray(stringArray_size1, SIZE_1);
    cleanupStringArray(stringArray_size3, SIZE_3);
    cleanupStringArray(stringArray_size10, SIZE_10);
}

// --- Utility ---

static void printTestHeader(const char* testName) {
    printf("--- %s ---\n\n", testName);
}

// Initialize elements of the string array incrementally for easier debugging.
static void incrementalStringArrayInit(char* stringArray[], const size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        stringArray[i] = malloc(sizeof(char*) * MAX_STRING_LENGTH);
        sprintf(stringArray[i], "string #%.2d", i);
    }
}

static void cleanupStringArray(char* stringArray[], const size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        free(stringArray[i]);
    }
}
