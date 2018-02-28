# ESPTestHelper

Provides class `TestHelper`, a simple unit testing helper class written for the Arduino framework. Designed on ESP8266.

## Key Features
* **Printing of Test Results / Headers** - 
	A header is printed at construction with information about the type of test being run. Printing of expected and actual values is automated at the time of comparison. Produces a cleanly standardized unit test log. Output can be redirected from `Serial` to another source.


* **Comparison of Expected and Actual Values** - 
	Template functions make comparing values of different types easy. Comparisons are done using the `==` operator except where this is not possible. Expected and actual values are printed upon comparison. If expected and actual values do not agree, the counter for failed tests is incremented.

* **Test Counter** - 
	Counters track the tests run and failed over the course of a `TestHelper` object instance, as well as statically over the life of the program. As a result, the log will contain information about how many tests were failed in total, as well as how many tests were failed for a particular feature being tested.





## API

Documentation taken from `TestHelper.h`.

By default, output will be sent to `Serial`. 

Use `#define __TEST_HELPER_DEST__    DEST` to direct output to a different source.


```c++
/**
 * @brief Constructor
 * 
 * @param method_name   A descriptive name of the method being tested
 * 
 * @param description   A description of the type of test being run
 * 
 * post: Header with method_name and description is printed, test counters are incremented
 */
TestHelper(const char* method_name, const char* description);
```



```c++
/**
 * @brief Gets the number of tests failed by this TestHelper instance
 * 
 * @return Number of times printResult() or testResult() returned false from this object
 */
unsigned long getNumTestsFailed() const;
```

```c++
/**
 * @brief Gets the number of tests run by this TestHelper instance
 * 
 * @return Number of times printResult() or testResult() was called by this object
 */
unsigned long getNumTestsRun() const;
```

```c++
/**
 * @brief Gets whether a test has failed over the course of this TestHelper instance
 * 
 * @return getNumTestsFailed() == 0
 * 
 */
bool noneFailedThisTest() const;
```

```c++
/**
 * @brief Gets the total number of tests failed over the couse of the program
 * 
 * 
 * @return Sum of tests failed by every TestHelper object
 */
static unsigned long getTotalTestsFailed();
```

```c++
/**
 * @brief Gets the total number of tests run over the couse of the program
 * 
 * 
 * @return Sum of tests run by every TestHelper object
 */
static unsigned long getTotalTestsRun();
```

```c++
/**
 * @brief Gets whether every test has passed for this program run
 * 
 * @return true if numTestsFailed == 0 for every TestHelper created this program run
 * 
 */
static bool allTestsPassed();
```

```c++
/**
 * @brief Compares expected and actual values using == for generic types
 * 
 * pre: expected and actual can be compared using ==
 * @param expected  The expected value
 * @param actual    The actual value
 * 
 * post:    getNumTestsRun()++, getTotalTestsRun()++,
 *          if(expected != actual) getNumTestsFailed()++, getTotalTestsFailed()++
 * 
 * @return expected == actual
 */
template<typename T, typename U>
bool testResult(T expected, U actual);
```

```c++
/**
 * @brief Compares expected and actual values within an allowable error
 * 
 * pre: expected and actual can be compared using ==
 * @param expected  The expected value
 * @param actual    The actual value
 * @param delta     The allowable difference betwee expected and actual
 * 
 * post:    getNumTestsRun()++, getTotalTestsRun()++,
 *          if(test failed) getNumTestsFailed()++, getTotalTestsFailed()++
 * 
 * @return abs(expected - actual) <= delta
 */
template<typename T, typename U>
bool testResultRange(T expected, U actual, double delta);
```

```c++

/**
 * @brief Compares expected and actual cstrings
 * 
 * pre: expected and actual can be compared using ==
 * @param expected  The expected value as a cstring
 * @param actual    The actual value as a cstring
 * 
 * post:    getNumTestsRun()++, getTotalTestsRun()++,
 *          if(expected != actual) getNumTestsFailed()++, getTotalTestsFailed()++
 * 
 * @return expected == actual
 */
bool testResult(const char* expected, const char* actual);
```

```c++
/**
 * @brief Compares expected and actual values using == for generic types
 * 
 * pre: expected and actual can be compared using ==
 * @param expected  The expected value
 * @param actual    The actual value
 * 
 * post:    getNumTestsRun()++, getTotalTestsRun()++,
 *          if(expected != actual) getNumTestsFailed()++, getTotalTestsFailed()++
 * 
 * @return expected == actual
 */
bool testResult(std::string expected, std::string actual); 
```

```c++
/**
 * @brief Calls testResult() and prints expected/actual values
 * 
 * @details     Values are printed by assigning them to an Arduino string. 
 *              ostringstream would be preferred
 * 
 * @param expected  The expeced value
 * @param actual    The actual value
 * 
 * post: expected and actual values printed
 * 
 * @return testResult(expected, actual);
 */
template<typename T, typename U>
bool printResult(T expected, U actual);
```

```c++
/**
 * @brief Calls testResultRange() and prints expected/actual and delta values
 * 
 * @details     Values are printed by assigning them to an Arduino string. 
 *              ostringstream would be preferred
 * 
 * @note	Expected values will be printed as doubles, ie "100.00"
 * 
 * @param expected  The expeced value
 * @param actual    The actual value
 * @param delta     The allowed error of actual, delta >= 0
 * 
 * post: print "(expected - delta) <= val <= (expected + delta)" and actual value
 * 
 * @return testResultRange(expected, actual, delta);
 */
template<typename T, typename U>
bool printResultRange(T expected, U actual, double delta);
```

```c++
/**
 * @brief 	Prints information about the number of tests run / failed over the
 * 			lifetime of this object
 * 
 * post: Message printed with tests run / failed and an error message if one or more tests failed
 * 
 * @return	true if all tests run by this object passed at the time of the call, false otherwise
 */
bool printResult();
```

```c++
/**
 * @brief 	Prints information about the number of tests run / failed for the course of the program.
 * 			This information is tracked statically across TestHelper object instances
 * 
 * post: 	Message printed with tests run / failed for the entire program and an error message 
 * 			if one or more tests failed
 * 
 * @return	true if all tests run by this object passed at the time of the call, false otherwise
 */
static bool end();
```
	



