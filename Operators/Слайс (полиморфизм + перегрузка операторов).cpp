#include <iostream>
#include <cmath>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>

using namespace std;

class VectorSlice;

class Vector {
private:
    double* buf;
    int n;

protected:
    // Конструктор по-умолчанию, который ничего не делает
    // чтобы программе было, что автоматически вызвать
    // перед конструктором дочернего класса
    Vector() {
        buf = nullptr;
        n = 0;
    }

public:
    Vector(int size) {
        prepare(size);
        memset(buf, 0, sizeof(double) * dim());
    }

    Vector(const double* buf, int size) {
        fill(buf, size);
    }

    Vector(const Vector& v) {
        prepare(v.dim());
        for (int i = 0; i < dim(); i++)
            (*this)[i] = v[i];
    }

    ~Vector() {
        if (buf != nullptr)
            delete[] buf;
    }

    virtual int dim() const {     // Размерность вектора
        return n;
    }

    virtual const double& operator[](int i) const {
        return this->buf[i];
    }

    virtual double& operator[](int i) {
        return this->buf[i];
    }

    double length() const {
        return sqrt((*this) * (*this));
    }

    Vector operator+(const Vector& v) const {
        assert(dim() == v.dim());

        Vector res(*this);
        for (int i = 0; i < dim(); i++)
            res[i] += v[i];

        return res;
    }

    Vector operator-(const Vector& v) const {
        assert(dim() == v.dim());

        Vector res(*this);
        for (int i = 0; i < dim(); i++)
            res[i] -= v[i];

        return res;
    }

    double operator*(const Vector& v) const {
        assert(dim() == v.dim());

        double res = 0.;
        for (int i = 0; i < dim(); i++)
            res += (*this)[i] * v[i];

        return res;
    }

    bool operator!=(const Vector& v) const {
        assert(dim() == v.dim());
        return !(*this == v);
    }

    bool operator==(const Vector& v) const {
        assert(dim() == v.dim());
        bool equal = true;
        for (int i = 0; i < n && equal; i++)
            equal = equal && (*this)[i] == v[i];

        return equal;
    }

    Vector& operator=(const Vector& v) {
        assert(dim() == v.dim());
        for (int i = 0; i < dim(); i++)
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
        for (int i = 0; i < dim(); i++)
            ++((*this)[i]);
        return *this;
    }

    Vector operator++(int) {  // Постфиксный оператор инкремента
        Vector v(*this);
        ++*this;
        return v;
    }

    Vector& operator--() {  // Префиксный оператор декремента
        for (int i = 0; i < dim(); i++)
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

class VectorSlice : public Vector {
private:
    Vector* v;
    int start, end;
public:
    VectorSlice(Vector* v, int start, int end) {
        assert(start >= 0 && end < v->dim());

        this->v = v;
        this->start = start;
        this->end = end;
    }

    virtual int dim() const override {
        return end - start + 1;
    }

    virtual const double& operator[](int i) const override {
        assert(i >= 0 && i < dim());
        return (*v)[start + i];
    }

    virtual double& operator[](int i) override {
        assert(i >= 0 && i < dim());
        return (*v)[start + i];
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

    int n = 10;
    Vector a(n);
    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000 / 100.;

    cout << "a = " << a << endl;

    // Внимание: если "слайсы" вектора будут перекрываться,
    // то изменение элементов одного может привести к изменению
    // элементов другого.
    int ss1 = 2, se1 = 5, ss2 = 6, se2 = 9;
    VectorSlice s1(&a, ss1, se1), s2(&a, ss2, se2);

    // Теперь и "cout <<", и все операции
    // работают для слайсов так же, как для обычного вектора.
    cout << "a[" << ss1 << ":" << se1 << "] = " << s1 << endl;
    cout << "a[" << ss2 << ":" << se2 << "] = " << s2 << endl;

    Vector c = s1 + s2;
    cout << "a[" << ss1 << ":" << se1 << "] + "
    "a[" << ss2 << ":" << se2 << "] = " << c << endl;
    c = s1 - s2;
    cout << "a[" << ss1 << ":" << se1 << "] - "
    "a[" << ss2 << ":" << se2 << "] = " << c << endl;
    double d = s1 * s2;
    cout << "a[" << ss1 << ":" << se1 << "] * "
    "a[" << ss2 << ":" << se2 << "] = " << d << endl;

    --s1;
    cout << "--a[" << ss1 << ":" << se1 << "] = " << s1 << endl;
    // После изменения слайса изменилась часть вектора a
    cout << endl << "(after slice decrement)" << endl;
    cout << "a = " << a << endl;

    // "Слайс" "слайса"
    int ss3 = 1, se3 = 2;
    VectorSlice s3(&s1, ss3, se3);
    cout << "a[" << ss1 << ":" << se1 << "]["
         << ss3 << ":" << se3 << "] = " << s3 << endl;

    return 0;
}
