/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR1 */
void runTestsPR1(int* totalTest, int* passedTest);

/* Test the serialization of materials */
void testSerialization(int* totalTest, int* passedTest);

/* Test the copy and comparison of materials */
void testCpycmp(int* totalTest, int* passedTest);

/* Test the material data persistence */
void testPersistence(int* totalTest, int* passedTest);

/* Test the material search */
void testSearch(int* totalTest, int* passedTest);

/* Test the material statistics */
void testCount(int* totalTest, int* passedTest);

/* Test the material sorting */
void testSort(int* totalTest, int* passedTest);

/* Test the api calls */
void testApi(int* totalTest, int* passedTest);


