#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Animal {
public:
    virtual void makeSound() = 0;  
    virtual ~Animal() {}  
};


class Dog : public Animal{
public:
    virtual void makeSound()override {
        cout << "Dog barks: Woof! Woof!" << endl;
    }
};

class Jindo : public Dog{
public:
    virtual void makeSound() final {
        cout << "Dog barks: Woof! Woof!" << endl;
    }
};

class Cat : public Animal{
public:
    virtual void makeSound()  override {
        cout << "Cat meows: Meow! Meow!" << endl;
    }
};


class Cow : public Animal{
public:
    virtual void makeSound() override {
        cout << "Cow moos: Moo! Moo!" << endl;
    }
};


class Zoo {
public:
  
    Animal* createRandomAnimal() {
        int randomChoice = rand() % 3;  
        if (randomChoice == 0) {
            return new Dog();  
        }
        else if (randomChoice == 1) {
            return new Cat(); 
        }
        else {
            return new Cow();  
        }
    }
};

int main() {
    srand(time(nullptr)); 

    Zoo zoo;  

   
    Animal* animal = zoo.createRandomAnimal();  
    animal->makeSound();  

    
    delete animal;

    return 0;
}