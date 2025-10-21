#include <iostream>
#include <vector> //the header for std::vector

#include <string>
#include <algorithm>
#include <numeric>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// a helper function to print vector's content
void print_vector(const vector<int> &vec)
{
    for (const int &num : vec)
    {
        cout << num << " ";
    }
    cout << "(size: " << vec.size() << ")" << endl;
}

int main()
{

    vector<int> scores;

    // adding elemnet to the end of vector
    scores.push_back(10);
    scores.push_back(87);
    scores.push_back(92);

    cout << "the vector contains " << scores.size() << " elements" << endl;

    // accessing elements using indexing
    for (size_t i = 0; i < scores.size(); ++i)
    {
        cout << "Element at index " << i << " : " << scores[i] << endl;
    }

    // change elments
    scores[1] = 89;

    cout << "the second element is now: " << scores[1] << endl;

    // using .at() slower but safer -- it checks if the index is valid
    cout << "the first element is: " << scores.at(0) << endl;

    // below would crash the program because index 10 is out of bounds
    //.at() is useful to avoid such issues
    cout << "Element at index 10: " << scores[10] << endl; // may throw a random number
    try
    {
        scores.at(10); // this will throw an out_of_range exception
    }
    catch (const std::out_of_range &e)
    {
        cout << "error: " << e.what() << endl;
    }

    vector<string> names = {"nagesh", "kumar", "pandey"};

    // range-based for loop --best for most cases
    for (const string &name : names)
    {
        cout << "hello, " << name << endl;
    }
    // index based loop
    for (size_t i = 0; i < names.size(); ++i)
    {
        cout << "hii, " << names[i] << endl;
    }

    vector<int> numbers = {10, 20, 30, 40, 50};

    // we use int& (a non const reference) to be  able to change the values
    for (int &num : numbers)
    {
        num = num * 2;
    }
    // printing to see the changes using const for read only access
    for (const int &num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    // remove the last element
    numbers.pop_back();
    cout << "after pop_back): ";
    print_vector(numbers);

    //.erase() needs an iterator pointing to the element to be removed
    // so used numbers.begin() + index to get the iterator at specific index
    numbers.erase(numbers.begin() + 1);
    cout << "after erase at index 1: ";
    print_vector(numbers);

    numbers.insert(numbers.begin() + 1, 25);
    cout << "after insert 25 at index 1: ";
    print_vector(numbers);

    // // remove all elemnts from vector
    // numbers.clear();
    // cout << "after clear(): ";
    // print_vector(numbers);

    vector<int> vec;
    cout << "Initial -> size: " << vec.size() << ", capacity: " << vec.capacity() << endl;

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
        cout << "Pushed " << i << " -> size: " << vec.size() << ", capacity: " << vec.capacity() << endl;
    }

    std::vector<int> vec2;
    vec2.reserve(1000);
    cout << "After reserve(1000) -> size: " << vec2.size() << ", capacity: " << vec2.capacity() << endl;

    for (int i = 0; i < 1000; ++i)
    {
        vec2.push_back(i);
    }
    cout << "After 1000 push_backs -> size: " << vec2.size() << ", capacity: " << vec2.capacity() << endl;
    // sort the vector
    sort(numbers.begin(), numbers.end());
    cout << "Sorted numbers: ";
    print_vector(numbers);
    print_vector(numbers);

    // find an elemnt
    int value_to_find = 99;
    auto it = std::find(numbers.begin(), numbers.end(), value_to_find);
    if (it != numbers.end())
    {
        cout << "Found " << value_to_find << " in the vector." << endl;
    }
    else
    {
        cout << value_to_find << " not found in the vector." << endl;
    }

    // sum all element
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum of all elements: " << sum << endl;

    return 0;
}