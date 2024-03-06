#include <iostream>

// Подключение собственных библиотек
// (убедитесь, что .h и .cpp файлы библиотек
// прописаны в CMakeLists.txt)
#include "list.h"
#include "matrix.h"

using namespace std;

const int N = 100;
struct Person {
    char name[N];
    int age;
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "{" << p.name << ", " << p.age << "}";
    return os;
}

int main(int argc, char *argv[])
{
    // ВНИМАНИЕ! Для корректного запуска в Qt, поддерживающего
    // ввод с клавиатуры, необходимо нажать слева на панели
    // "Проекты"->"Запустить" и установить галочку
    // "запускать в терминале".

    // Пример на список структур
    // Для примера список в библиотеке убран
    // в пространство имён ListLib (см. list.h)
    ListLib::List<Person> lst;
    lst.add({ "Vasyliy", 35 });
    lst.add({ "Ivan", 24 });
    lst.add({ "Diana", 27 });
    cout << lst << endl;

    while (!lst.isempty()) {
        lst.remove(lst.Len() - 1);
        cout << lst << endl;
    }

    // Использование матрицы из созданной библиотеки
    // Для примера матрица в библиотеке убрана
    // в пространство имён MyMath (см. matrix.h)

    cout << "Input matrix's rows and columns count: ";
    int n, m;
    cin >> n >> m;

    MyMath::Matrix A(n, m);
    cout << "Input matrix elements:" << endl;
    cin >> A;
    cout << endl << "Your matrix A is:" << endl << A;
    cout << "Input multiplier: ";
    double a;
    cin >> a;
    MyMath::Matrix B = a * A;
    cout << endl << a << " * A = " << endl << B;

    return 0;
}
