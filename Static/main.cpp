#include <iostream>

using namespace std;

class A {
private:
    static int count;
public:
    A() {
        count++;
    }

    ~A() {
        count--;
    }

    static int countClassObjects() {
        return count;
    }
};

// Инициализация статической переменной count в классе A
int A::count = 0;

void f() {
    static int n = 0;
    cout << "Function f called " << ++n << " times." << endl;
}

int main(int argc, char *argv[])
{
    cout << "Testing static variable in function..." << endl;
    f();
    f();
    f();
    cout << endl << "Testing static members of the class A..." << endl;
    cout << "First, we have " << A::countClassObjects() <<
        " objects in memory." << endl;

    A a, *b;
    cout << endl << "Declared one object and one pointer to an object. "
                    "Now have " << A::countClassObjects() <<
        " objects in memory." <<endl;

    b = new A;
    cout << endl << "Allocated memory for an object using \"new\" operator. "
            "Now have " << A::countClassObjects() << " objects." << endl;
    {
        cout << endl << "Entering a nested scope. Still have " <<
            A::countClassObjects() << " objects." << endl;
        A c, *d;
        cout << endl << "Declared another object and one more pointer "
                        "to an object. Now have " <<
            A::countClassObjects() << " objects in memory." << endl;

        d = new A;
        cout << endl << "Allocated memory for one more object using \"new\" "
                        "operator. Now have " << A::countClassObjects() <<
            " objects." << endl;
    }
    cout << endl << "Leaving the scope. All objects declared inside are gone. "
            "But not objects created using \"new\"! Now have " <<
        A::countClassObjects() << " objects in memory." << endl;

    delete b;

    cout << endl << "Freed memory of one object created using \"new\" "
                    "operator. Now only " << A::countClassObjects() <<
        " objects left in memory." << endl << endl <<
        "The first one will also be destroyed, when program leave "
        "\"main\" function, where it have been declared. The second "
        "one has been created using \"new\" inside a nested scope, "
        "so we should had to \"delete\" it there. But now we've lost "
        "it's pointer and so we would have had a memory leak, if "
        "the program isn't over." << endl;

    return 0;
}
