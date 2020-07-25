#include "pretty_printer.h"

// Constant sizes
static const size_t SIZE_0  = 0;
static const size_t SIZE_1  = 1;
static const size_t SIZE_3  = 3;
static const size_t SIZE_10 = 10;
static const size_t SIZE_25 = 25;

// Tests
static void testRandRange();

static void testRandomStringArrayInit();

static void testPrintStringArrayElements();
static void testPrintIntegerArrayElements();
static void testPrintFloatArrayElements();

static void testPrintStringArrayElementsAsColumns();
static void testPrintIntegerArrayElementsAsColumns();
static void testPrintFloatArrayElementsAsColumns();

// --- Test Driver ---

int main() {

    // Seed the rand
    srand(time(NULL));

    // Utility Tests
    testRandRange();
    testRandomStringArrayInit();

    // Normal Print Tests
    testPrintStringArrayElements();
    testPrintIntegerArrayElements();
    testPrintFloatArrayElements();

    // Column Print Tests
    testPrintStringArrayElementsAsColumns();
    testPrintIntegerArrayElementsAsColumns();
    testPrintFloatArrayElementsAsColumns();

    return 0;
}

// --- Test Definitions ---

static void testRandRange() {

    printTestHeader(__func__);

    int lower, upper, range, generated;

    // Set the range
    lower = 2;
    upper = 10;
    range = upper - lower;

    printf("lower=%d, upper=%d\n{ ", lower, upper);

    // Print the set of all possible generated numbers four times (to ensure)
    int i;
    for(i = 0; i < upper * 4; ++i) {
        generated = i % (range + 1) + lower;

        if(i == upper * 4 - 1) {
            printf("%d", generated);
            break;
        }

        printf("%d, ", generated);
    }

    printf(" }\n\n");

    // ---

    // Set the range
    lower = 0;
    upper = 1;
    range = upper - lower;

    printf("lower=%d, upper=%d\n{ ", lower, upper);

    // Print the set of all possible generated numbers four times (to ensure)
    for(i = 0; i < upper * 4; ++i) {
        generated = i % (range + 1) + lower;

        if(i == upper * 4 - 1) {
            printf("%d", generated);
            break;
        }

        printf("%d, ", generated);
    }

    printf(" }\n\n");

    // ---

    // Set the range
    lower = 0;
    upper = 3;
    range = upper - lower;

    printf("lower=%d, upper=%d\n{ ", lower, upper);

    // Print the set of all possible generated numbers four times (to ensure)
    for(i = 0; i < upper * 4; ++i) {
        generated = i % (range + 1) + lower;

        if(i == upper * 4 - 1) {
            printf("%d", generated);
            break;
        }

        printf("%d, ", generated);
    }

    printf(" }\n\n");

}

static void testRandomStringArrayInit() {

    printTestHeader(__func__);

    char* stringArray_size25   [SIZE_25];

    randomStringArrayInit(stringArray_size25, SIZE_25);

    printArray(stringArray_size25, SIZE_25, STRING);
}

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

static void testPrintStringArrayElementsAsColumns() {

    printTestHeader(__func__);
    
    // String arrays
    char* incrementalStringArray_size25   [SIZE_25];

    // Init
    incrementalStringArrayInit(incrementalStringArray_size25, SIZE_25);

    // Print
    printf("Default (%d) Columns:\n", DEFAULT_COLUMNS);
    printColumns(incrementalStringArray_size25, SIZE_25, STRING, 0);

    int numColumns = 1;
    printf("%d Column(s):\n", numColumns);
    printColumns(incrementalStringArray_size25, SIZE_25, STRING, numColumns);

    numColumns = 2;
    printf("%d Column(s):\n", numColumns);
    printColumns(incrementalStringArray_size25, SIZE_25, STRING, numColumns);

    numColumns = 3;
    printf("%d Column(s):\n", numColumns);
    printColumns(incrementalStringArray_size25, SIZE_25, STRING, numColumns);

    numColumns = 4;
    printf("%d Column(s):\n", numColumns);
    printColumns(incrementalStringArray_size25, SIZE_25, STRING, numColumns);

    // Cleanup
    cleanupArray(incrementalStringArray_size25, SIZE_25, STRING);
}

static void testPrintIntegerArrayElementsAsColumns() {
    
    printTestHeader(__func__);

    // Init Stack arrays
    int stack_intArray_size25[SIZE_25];
    int* stackArrayPtr25[] = { stack_intArray_size25 };

    incrementalIntArrayInit(stackArrayPtr25, SIZE_25);

    // Init Heap arrays
    int* heap_intArray_size25 = malloc(SIZE_25);

    incrementalIntArrayInit(&heap_intArray_size25, SIZE_25);

    // Print
    printf("Stack Arrays:\n");
    printf("Default (%d) Columns:\n", DEFAULT_COLUMNS);
    printColumns(stack_intArray_size25, SIZE_25, INTEGER, DEFAULT_COLUMNS);

    printf("Heap Arrays:\n");
    printf("Default (%d) Columns:\n", DEFAULT_COLUMNS);
    printColumns(heap_intArray_size25, SIZE_25, INTEGER, DEFAULT_COLUMNS);

    // Cleanup
    cleanupArray(heap_intArray_size25, SIZE_25, INTEGER);
}

static void testPrintFloatArrayElementsAsColumns() {
    
    printTestHeader(__func__);

    // Init Stack arrays
    float stack_floatArray_size25[SIZE_25];
    float* stackArrayPtr25[] = { stack_floatArray_size25 };

    incrementalFloatArrayInit(stackArrayPtr25, SIZE_25);

    // Init Heap arrays
    float* heap_floatArray_size25 = malloc(SIZE_25);

    incrementalFloatArrayInit(&heap_floatArray_size25, SIZE_25);

    // Print
    printf("Stack Arrays:\n");
    printf("Default (%d) Columns:\n", DEFAULT_COLUMNS);
    printColumns(stack_floatArray_size25, SIZE_25, FLOAT, DEFAULT_COLUMNS);

    printf("Heap Arrays:\n");
    printf("Default (%d) Columns:\n", DEFAULT_COLUMNS);
    printColumns(heap_floatArray_size25, SIZE_25, FLOAT, DEFAULT_COLUMNS);

    // Cleanup
    cleanupArray(heap_floatArray_size25, SIZE_25, FLOAT);
}