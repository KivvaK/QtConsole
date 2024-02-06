#include <locale>
#include <iostream>
#include <cstring>

using namespace std;

class Animal {
private:
    char* name;
public:
    Animal(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    ~Animal() {
        delete[] name;
    }

    const char* Name() const {
        return name;
    }

    void say() const {
        wcout << name << L" говорит: ";
        voice();
    }

private:
    virtual void voice() const {
        wcout << L"странный звук...";
    }
};

class Cat : public Animal {
public:
    Cat(const char* name) : Animal(name) {}
private:
    virtual void voice() const override {
        wcout << L"мяу";
    }
};

class Dog : public Animal {
public:
    Dog(const char* name) : Animal(name) {}
private:
    virtual void voice() const override {
        wcout << L"гав";
    }
};

class Chupakabra : public Animal {
public:
    Chupakabra(const char* name) : Animal(name) {}
};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    const int N = 4;
    Animal* zoo[N];
    zoo[0] = new Animal("Vasya");
    zoo[1] = new Cat("Barsik");
    zoo[2] = new Dog("Mukhtar");
    zoo[3] = new Chupakabra("Joe");

    for (int i = 0; i < N; i++) {
        zoo[i]->say();
        wcout << endl;
    }

    for (int i = 0; i < N; i++)
        delete zoo[i];
    return 0;
}
