#include <iostream>
#include <cmath>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>

using namespace std;

class Vector {
private:
    double* buf;
    int n;
public:
    Vector(int size) {
        prepare(size);
        memset(buf, 0, sizeof(double) * n);
    }

    Vector(const double* buf, int size) {
        fill(buf, size);
    }

    Vector(const Vector& v) {
        fill(v.buf, v.n);
    }

    ~Vector() {
        delete[] buf;
    }

    int dim() const {     // Размерность вектора
        return n;
    }

    double length() const {
        return sqrt((*this) * (*this));
    }

    Vector operator+(const Vector& v) const {
        assert(n == v.n);

        Vector res(*this);
        for (int i = 0; i < n; i++)
            res[i] += v[i];

        return res;
    }

    Vector operator-(const Vector& v) const {
        assert(n == v.n);

        Vector res(*this);
        for (int i = 0; i < n; i++)
            res[i] -= v[i];

        return res;
    }

    double operator*(const Vector& v) const {
        assert(n == v.n);

        double res = 0.;
        for (int i = 0; i < n; i++)
            res += (*this)[i] * v[i];

        return res;
    }

    const double& operator[](int i) const {
        return this->buf[i];
    }

    double& operator[](int i) {
        return this->buf[i];
    }

    bool operator!=(const Vector& v) const {
        assert(n == v.n);
        return !(*this == v);
    }

    bool operator==(const Vector& v) const {
        assert(n == v.n);
        bool equal = true;
        for (int i = 0; i < n && equal; i++)
            equal = equal && (*this)[i] == v[i];

        return equal;
    }

    Vector& operator=(const Vector& v) {
        assert(n == v.n);
        for (int i = 0; i < n; i++)
            (*this)[i] = v[i];

        return *this;
    }

    Vector operator-() const {    // Унарный минус
        Vector res(*this);
        for (int i = 0; i < res.n; i++)
            res[i] = -res[i];
        return res;
    }

    Vector& operator++() {  // Префиксный оператор инкремента
        for (int i = 0; i < n; i++)
            ++((*this)[i]);
        return *this;
    }

    Vector operator++(int) {  // Постфиксный оператор инкремента
        Vector v(*this);
        ++*this;
        return v;
    }

    Vector& operator--() {  // Префиксный оператор декремента
        for (int i = 0; i < n; i++)
            --((*this)[i]);
        return *this;
    }

    Vector operator--(int) {  // Постфиксный оператор декремента
        Vector v(*this);
        --*this;
        return v;
    }

private:
    void prepare(int size) {
        n = size;
        this->buf = new double[n];
    }

    void fill(const double* buf, int size) {
        prepare(size);
        memcpy(this->buf, buf, sizeof(double) * size);
    }
};

// Перегрузка оператора << для вывода в консоль/текстовый файл
// левый операнд - ostream& os, правый операнд - const Vector& v
ostream& operator<<(ostream& os, const Vector& v) {
    os << "(";
    int i;
    for (i = 0; i < v.dim() - 1; i++)
        os << v[i] << ", ";
    os << v[i] << ")";

    return os;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int n = 7;
    Vector a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000 / 100.;
        b[i] = rand() % 1000 / 100.;
    }

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    Vector c = a + b;
    cout << "a + b = " << c << endl;
    c = a - b;
    cout << "a - b = " << c << endl;
    cout << "|a - b| = " << c.length() << endl;

    double d = a * b;
    cout << "a * b = " << d << endl;
    a--;
    cout << "a-- = " << a << endl;

    return 0;
}
