#include "pretty_printer.h"

// Constant sizes
static const size_t SIZE_0  = 0;
static const size_t SIZE_1  = 1;
static const size_t SIZE_3  = 3;
static const size_t SIZE_10 = 10;

// Tests
static void testPrintStringArrayElements();
static void testPrintIntegerArrayElements();
static void testPrintFloatArrayElements();

// Utility Functions
static void printTestHeader(const char* testName);

static void incrementalStringArrayInit(char* stringArray[], const size_t size);
static void incrementalIntArrayInit(int** intArray, const size_t size);
static void incrementalFloatArrayInit(float** floatArray, const size_t size);

static void cleanupStringArray(char* stringArray[], const size_t size);
static void cleanupArray(void* array, const size_t size, DataType type);

// ---

int main() {

    // Run Tests
    testPrintStringArrayElements();
    testPrintIntegerArrayElements();
    testPrintFloatArrayElements();

    return 0;
}

// --- Test Definitions ---

static void testPrintStringArrayElements() {

    printTestHeader(__func__);

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

static void testPrintIntegerArrayElements() {

    printTestHeader(__func__);

    // Stack arrays
    int stack_intArray_size0  [SIZE_0];
    int stack_intArray_size1  [SIZE_1];
    int stack_intArray_size3  [SIZE_3];
    int stack_intArray_size10 [SIZE_10];

    // Heap arrays
    int* heap_intArray_size0 = NULL;
    int* heap_intArray_size1 = NULL;
    int* heap_intArray_size3 = NULL;
    int* heap_intArray_size10 = NULL;

    // Stack allocated arrays have special pointer declarations
    int* stackArrayPtr0[] = { stack_intArray_size0 };
    int* stackArrayPtr1[] = { stack_intArray_size1 };
    int* stackArrayPtr3[] = { stack_intArray_size3 };
    int* stackArrayPtr10[] = { stack_intArray_size10 };
    
    // Init stack arrays
    incrementalIntArrayInit ( stackArrayPtr0, SIZE_0 );
    incrementalIntArrayInit ( stackArrayPtr1, SIZE_1 );
    incrementalIntArrayInit ( stackArrayPtr3, SIZE_3 );
    incrementalIntArrayInit ( stackArrayPtr10, SIZE_10 );
    
    // Init heap arrays
    incrementalIntArrayInit ( & heap_intArray_size0, SIZE_0 );
    incrementalIntArrayInit ( & heap_intArray_size1, SIZE_1 );
    incrementalIntArrayInit ( & heap_intArray_size3, SIZE_3 );
    incrementalIntArrayInit ( & heap_intArray_size10, SIZE_10 );

    // Print stack arrays
    printf("Stack Arrays:\n");
    printArray ( stack_intArray_size0, SIZE_0, INTEGER );
    printArray ( stack_intArray_size1, SIZE_1, INTEGER );
    printArray ( stack_intArray_size3, SIZE_3, INTEGER );
    printArray ( stack_intArray_size10, SIZE_10, INTEGER );

    // Print heap arrays
    printf("Heap Arrays:\n");
    printArray ( heap_intArray_size0, SIZE_0, INTEGER );
    printArray ( heap_intArray_size1, SIZE_1, INTEGER );
    printArray ( heap_intArray_size3, SIZE_3, INTEGER );
    printArray ( heap_intArray_size10, SIZE_10, INTEGER );

    // Cleanup heap arrays
    cleanupArray ( heap_intArray_size0, 0, INTEGER );
    cleanupArray ( heap_intArray_size1, 0, INTEGER );
    cleanupArray ( heap_intArray_size3, 0, INTEGER );
    cleanupArray ( heap_intArray_size10, 0, INTEGER );
}

static void testPrintFloatArrayElements() {

    printTestHeader(__func__);

    // Stack arrays
    float stack_floatArray_size0  [SIZE_0];
    float stack_floatArray_size1  [SIZE_1];
    float stack_floatArray_size3  [SIZE_3];
    float stack_floatArray_size10 [SIZE_10];

    // Heap arrays
    float* heap_floatArray_size0 = NULL;
    float* heap_floatArray_size1 = NULL;
    float* heap_floatArray_size3 = NULL;
    float* heap_floatArray_size10 = NULL;

    // Stack allocated arrays have special pointer declarations
    float* stackArrayPtr0[] = { stack_floatArray_size0 };
    float* stackArrayPtr1[] = { stack_floatArray_size1 };
    float* stackArrayPtr3[] = { stack_floatArray_size3 };
    float* stackArrayPtr10[] = { stack_floatArray_size10 };

    // Init stack arrays
    incrementalFloatArrayInit ( stackArrayPtr0, SIZE_0 );
    incrementalFloatArrayInit ( stackArrayPtr1, SIZE_1 );
    incrementalFloatArrayInit ( stackArrayPtr3, SIZE_3 );
    incrementalFloatArrayInit ( stackArrayPtr10, SIZE_10 );
    
    // Init heap arrays
    incrementalFloatArrayInit ( & heap_floatArray_size0, SIZE_0 );
    incrementalFloatArrayInit ( & heap_floatArray_size1, SIZE_1 );
    incrementalFloatArrayInit ( & heap_floatArray_size3, SIZE_3 );
    incrementalFloatArrayInit ( & heap_floatArray_size10, SIZE_10 );

    // Print stack arrays
    printf("Stack Arrays:\n");
    printArray ( stack_floatArray_size0, SIZE_0, FLOAT );
    printArray ( stack_floatArray_size1, SIZE_1, FLOAT );
    printArray ( stack_floatArray_size3, SIZE_3, FLOAT );
    printArray ( stack_floatArray_size10, SIZE_10, FLOAT );

    // Print heap arrays
    printf("Heap Arrays:\n");
    printArray ( heap_floatArray_size0, SIZE_0, FLOAT );
    printArray ( heap_floatArray_size1, SIZE_1, FLOAT );
    printArray ( heap_floatArray_size3, SIZE_3, FLOAT );
    printArray ( heap_floatArray_size10, SIZE_10, FLOAT );

    // Cleanup heap arrays
    cleanupArray ( heap_floatArray_size0, 0, FLOAT );
    cleanupArray ( heap_floatArray_size1, 0, FLOAT );
    cleanupArray ( heap_floatArray_size3, 0, FLOAT );
    cleanupArray ( heap_floatArray_size10, 0, FLOAT );
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

static void incrementalIntArrayInit(int** intArray, const size_t size) {

    if(*intArray == NULL) {
        *intArray = malloc(sizeof(int) * size);
    }
    
    int i;
    for(i = 0; i < size; ++i) {
        (*intArray)[i] = i;
    }
}

static void incrementalFloatArrayInit(float** floatArray, const size_t size) {
    if(*floatArray == NULL) {
        *floatArray = malloc(sizeof(float) * size);
    }

    int i;
    for(i = 0; i < size; ++i) {
        (*floatArray)[i] = (float)i;
    }
}


static void cleanupStringArray(char* stringArray[], const size_t size) {
    int i;
    for(i = 0; i < size; ++i) {
        free(stringArray[i]);
    }
}

static void cleanupArray(void* array, const size_t size, DataType type) {

    switch(type) {

        case STRING:
            cleanupStringArray((char**)array, size);
        return;

        case INTEGER:
            free((int*)array);
        return;

        case FLOAT:
            free((float*)array);
        return;

        default:
            printf("cannot free array of invalid type\n");
            return;
    }
}
