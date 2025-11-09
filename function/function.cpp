#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h> //for getting fixed-width like uint32_t

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
  function anatomy is:
      [return_type] [function_name] ([parameter_list]) {
     // ... body (the code that does the work) ...
     return [value]; // (Only if return_type is not void)
 }

*/

// this add function has a return type add of int and takes two int parameters
int add(int a, int b)
{
    return a + b;
}

// void return type === no return value, its only job is to perform an action (printing something)

void printMessage(string message)
{

    cout << message << endl;
}

// parameter passing
// pass by value (default) -- makes a copy of the argument
void passByValue(int num, string text)
{
    num = 100;
    text = "changed in function";
    cout << "Inside passByValue: num = " << num << ", text = " << text << endl;
}

// pass by reference  -- uses & to pass the reference (address) of the argument
//  changes made to the parameter will affect the original argument,no copy is made

void passByReference(int &num, string &text)
{
    num = 200;
    text = "changed in function by reference";
    cout << "Inside passByReference: num = " << num << ", text = " << text << endl;
}

// function overloading -- same function name with different parameter list --compiler differentiates based on parameters
void process(int num)
{
    cout << "processing int: " << num << endl;
}

void process(const string &text)
{ // this is also ccalled passing by const reference -- avoids copy and original is not changed.. only readable
    cout << "processing string: " << text << endl;
}

void process(int num, const string &text)
{
    cout << "processing int and string: " << num << ", " << text << endl;
}

// static functions -- static keyword makes the function local to the file (translation unit)
//  static functions cannot be accessed from other files i mean from other .cpp files
// used only in this file

static void internalHelper()
{
    cout << "This is a static internal helper function." << endl;
}

// a typical srtuct representing sensor data
struct SensorData
{
    uint32_t timestamp;
    double value;
    uint8_t ststus_flags;
};

int main()
{

    int sum = add(10, 10);
    cout << "result of add(10,10) is: " << sum << endl;

    printMessage("Hello from printMessage function!"); // calling printMessage function

    // parameter passing
    int myValue = 10;
    string myString = "original text";

    cout << "Before passByValue: myValue = " << myValue << ", myString = " << myString << endl;

    // pass by value == original will not be changed
    passByValue(myValue, myString);
    cout << "After passByValue: myValue = " << myValue << ", myString = " << myString << endl;

    // pass by refenrence == original will be changed
    passByReference(myValue, myString);
    cout << "After passByReference: myValue = " << myValue << ", myString = " << myString << endl;

    cout << " Function Overloading Examples: " << endl;
    process(42);
    process("Hello, World!");
    process(100, "Test String");

    cout << "Calling static internal helper function: " << endl;
    internalHelper(); // it can only be call from this file only

    cout << " lambda function example: " << endl;
    // lambda function -- anonymous function defined inline
    vector<int> numbers = {1, 2, 3, 4, 5, 6};
    cout << "Original numbers: [1 2 3 4 5 6] " << endl;

    auto it = std::find_if(numbers.begin(), numbers.end(), [](int num)
                           { return num > 3; });
    if (it != numbers.end())
    {
        cout << "First number greater than 3 is: " << *it << endl;
    }
    else
    {
        cout << "No number greater than 3 found." << endl;
    }
}