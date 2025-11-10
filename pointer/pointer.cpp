#include <iostream>
#include <stdint.h> // for fixed-width integer types

using std::cout;
using std::endl;

void demo_the_basics()
{
    int my_age = 30;

    cout << "the alue in my age variable is: " << my_age << endl;

    //&my_age  gives the address of my_age variable
    cout << "the address of my_age variable is: " << &my_age << endl;

    // the * symbol is used to declare a pointer variable that tell compiler that this variable will store an address of a specific type
    int *p_age;
    // use & to assign the address of my_age to the pointer
    p_age = &my_age;

    cout << "the value stored in p_age pointer is (address of my_age): " << p_age << endl;
    cout << "this matches the address of my_age variable: " << &my_age << endl;
}

void demo_dereferencing()
{
    int my_number = 42;
    int *p_number = &my_number;

    // dereferencing the pointer to get the value at the address it points to
    // it tells compiler to access the value stored at the address held by the pointer

    int value_from_pointer = *p_number;
    cout << "value obtained by dereferencing p_number pointer: " << value_from_pointer << endl;
    // we can also use this to chnage the value of the original variable via the pointer
    *p_number = 99;
    cout << "after changing value via pointer, my_number is now: " << my_number << endl;
}

// pass by value example
void double_by_value(int num)
{
    num = num * 2;
    cout << "inside double_by_value, num is: " << num << endl;
}

// pass by pointer example
void double_by_pointer(int *p_num)
{
    *p_num = (*p_num) * 2;
    cout << "inside double_by_pointer, value at p_num is: " << *p_num << endl;
}

void demo_function()
{
    cout << "pointer in function demo:" << endl;

    int val_1 = 10;
    cout << "original val_1: " << val_1 << endl;
    double_by_value(val_1); // we pass a copy
    cout << "after double_by_value, val_1 is still: " << val_1 << endl;

    int val_2 = 10;
    cout << "original val_2: " << val_2 << endl;
    double_by_pointer(&val_2); // we pass the address
    cout << "after double_by_pointer, val_2 is now: " << val_2 << endl;
}
int main()
{
    demo_the_basics();
    cout << "-----------------------" << endl;
    demo_dereferencing();
    demo_function();
    
}