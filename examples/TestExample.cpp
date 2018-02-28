#include <Arduino.h>

#include "../src/TestHelper.h"      // Fix these before you run
#include "../src/TestHelper.cpp"

// You can change this using a preprocessor flag to redirect where test output goes
// #define __TEST_HELPER_DEST__    Serial



// The method to test
int square(int val) {
    return val*val;
}




/**
 * Though not required, include guards help you disable certain tests without
 * needing to comment out large blocks of code
 * 
 */
#define RUN_THIS_TEST

#ifdef RUN_THIS_TEST

void test1() {
    TestHelper test("square()", "basic fixed value test");

    int test_values[] = {0, 1, 2, 3, 4};
    for(int val : test_values) {

        const int EXPECTED = val * val;
        const int ACTUAL = square(val);

        // Expected value goes first, test result will be the same but message will print backwards
        test.printResult(EXPECTED, ACTUAL);

        // test.testResult(EXPECTED, ACTUAL); // Returns boolean test result without printing a message
    }

    test.printResult(); // Print the result for test1()
}

#else   // Dummy method in case we don't want to run this test
void test1() { }
#endif





void setup() {
    // You still need to begin 
    Serial.begin(115200);
    delay(1000);
    test1();

    TestHelper::end();  // Print a final test report
}

void loop() {
    delay(1);
}
