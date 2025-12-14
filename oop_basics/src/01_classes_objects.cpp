
#include<iostream>
#include<string>

class Car {
    public:

    std::string brand;
    std::string model;
    int year;
    bool isRunning;


    void printDetails(){
        std::cout<<"Car: " << brand<< " "<<model << " (" <<year << ") "<<std::endl;
    }

    void start(){
        isRunning = true;
        std::cout<< "The "<< model << "has started." << std::endl;
    }

    void stop(){
        isRunning = false;
        std::cout<< "The "<< model << "has stopped." << std::endl;
    }
};

int main(){
Car mycar;

mycar.brand = "Toyota";
mycar.model = "Corolla";
mycar.year = 2022;
mycar.isRunning = false;

mycar.printDetails();
mycar.start();
mycar.stop();


Car yourcar;
yourcar.brand = "Honda";
yourcar.model = "Civic";
yourcar.year = 2021;
yourcar.isRunning = false;

yourcar.printDetails();
yourcar.start();
yourcar.stop();

return 0;

}