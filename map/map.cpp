#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;

int main()
{

    // map<KeyType, ValueType> map_name;
    map<string, int> age_map;

    cout << "map creation done: size = " << age_map.size() << endl;

    // several method to insertion
    // M1...using insert() with pair
    age_map.insert(std::pair<string, int>("nagesh", 22));

    // M2....using insert() with make_pair()
    age_map.insert(std::make_pair("aman", 21));

    // M3...using insert() with curly braces
    age_map.insert({"sobik", 20});

    // M4...using operator[]
    age_map["pramatosh"] = 25;

    // accessing value
    cout << "age of aman: " << age_map["aman"] << endl;        // not efficient because it may create a new entry if key not found
    cout << "age of nagesh: " << age_map.at("nagesh") << endl; // efficient

    // using .at() with try-catch block
    try
    {
        cout << "age of unknown: " << age_map.at("unknown") << endl;
    }
    catch (const std::out_of_range &e)
    {
        cout << "key 'unknown' not found in age_map." << endl;
    }

    // removing element
    size_t element_removed = age_map.erase("nagesh");
    if (element_removed > 0)
    {
        cout << "successfully removed nagesh from age_map" << endl;
    }
    else
    {
        cout << "nagesh not found in age_map" << endl;
    }

    // iterating with range-based loop
    for (const auto &pair : age_map)
    {
        cout << pair.first << " : " << pair.second << endl;
    }
    // iterating using structured binding
    for (const auto &[name, age] : age_map)
    {
        cout << name << " => " << age << endl;
    }
    // iterating using classic iterator
    for (auto it = age_map.begin(); it != age_map.end(); ++it)
    {
        cout << it->first << " --> " << it->second << endl;
    }

    // searching using .find()
    auto it_sobik = age_map.find("sobik");
    if (it_sobik != age_map.end())
    {
        cout << "found sobik in age_map, age = " << it_sobik->second << endl;
    }
    else
    {
        cout << "sobik not found in age_map" << endl;
    }

    // searching using .count()
    if (age_map.count("pramatosh"))
    {
        cout << "pramatosh found in age_map" << endl;
    }
    else
    {
        cout << "pramatosh not found in age_map" << endl;
    }

    // //searching using .contains() - C++20 feature, not available in C++17
    // if(age_map.contains("aman"))
    // {
    //     cout << "aman found in age_map" << endl;
    // }
    // else
    // {
    //     cout << "aman not found in age_map" << endl;
    // }

    return 0;
}