#include <iostream>
#include <string>

int main()
{
    // creation
    std::string greeting = "Hii";

    // concatenation and appending
    std::string message = greeting + " welcome to c++ programming";
    message += " enjoy coding!!";
    std::cout << "message: " << message << std::endl;

    // getting length/size
    std::cout << "length of messsage: " << message.length() << std::endl;

    // accessing individual characters
    char first_char = message[0];
    char fifth_char = message.at(4);
    std::cout << "first character: " << first_char << std::endl;
    std::cout << "fifth character: " << fifth_char << std::endl;

    std::string text = "c++ is a powerful language";

    // get a portion of string (substring)  substr(start position, length)
    std::string sub = text.substr(9, 8); // "powerful"
    std::cout << "substring: " << sub << std::endl;

    // erase characters   erase(start position, length)
    text.erase(9, 9); // romove powerful
    std::cout << "after erase: " << text << std::endl;

    // insert characters  insert(position, string)
    text.insert(9, "versatile ");
    std::cout << "after insert: " << text << std::endl;

    std::string sentence = "i am programming for fun";

    // find a substring  find(substring)
    size_t pos = sentence.find("programming");
    if (pos != std::string::npos)
    { // npos means not found
        std::cout << "'programming' found at position: " << pos << std::endl;
    }
    else
    {
        std::cout << "'programming' not found" << std::endl;
    }

    // find a character
    size_t first_o = sentence.find('o');
    size_t last_o = sentence.rfind('o'); // reverse find
    std::cout << "first 'o' at position: " << first_o << std::endl;
    std::cout << "last 'o' at position: " << last_o << std::endl;

    std::string str;
    std::cout << "initial size of sre: " << str.size() << ", capacity: " << str.capacity() << std::endl;

    // adding chaarcter one by one and watch the size and capacity growth
    for (int i = 0; i < 30; ++i)
    {
        str.push_back('a');
        std::cout << "size: " << str.size() << ", capacity: " << str.capacity() << std::endl;
    }

    std::string num_str = "12345";
    int number = std::stoi(num_str); // string to integer
    number += 10;
    std::cout << "number after addition: " << number << std::endl;

    int val = 987;
    std::string val_str = std::to_string(val); // integer to string
    val_str += " is a number";
    std::cout << "int " << val << " as a string: " << val_str << std::endl;
}