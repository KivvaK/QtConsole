#include <locale>
#include <iostream>
#include <cmath>

using namespace std;

class CoordinateEntity {
private:
    float x, y;
public:
    CoordinateEntity(float x, float y) {
        this->x = x;
        this->y = y;
    }
    CoordinateEntity() : CoordinateEntity(0.f, 0.f) { }

    float X() const {
        return x;
    }

    float Y() const {
        return y;
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }
};

class Point : public CoordinateEntity {
};

class Vector : public CoordinateEntity {
private:
    float length;
public:
    Vector(float x, float y) : CoordinateEntity(x, y) {
        updateLength();
    }
    Vector() : Vector(0.f, 0.f) { }

    float getLength() const {
        return length;
    }

    void setX(float x) {
        CoordinateEntity::setX(x);
        updateLength();
    }

    void setY(float y) {
        CoordinateEntity::setY(y);
        updateLength();
    }

    Vector add(const Vector& v) {
        Vector res(X() + v.X(), Y() + v.Y());
        return res;
    }

private:
    void updateLength() {
        float x = X(), y = Y();
        length = sqrt(x * x + y * y);
    }
};

class Ellipse : public CoordinateEntity {
private:
    float a, b;
public:
    Ellipse(float x, float y, float a, float b) :
        CoordinateEntity(x, y)
    {
        this->a = a;
        this->b = b;
    }

    Ellipse(float a, float b) : Ellipse(0.f, 0.f, a, b) { }

    float A() const {
        return a;
    }

    float B() const {
        return b;
    }

    void setA(float a) {
        this->a = a;
    }

    void setB(float b) {
        this->b = b;
    }
};

class Circle : public Ellipse {
public:
    Circle(float x, float y, float r) :
        Ellipse(x, y, r, r) {}

    Circle(float r) :
        Circle(0.f, 0.f, r) {}

    float R() const {
        return A();
    }

    void setR(float r) {
        Ellipse::setA(r);
        Ellipse::setB(r);
    }

    void setA(float a) {
        setR(a);
    }

    void setB(float b) {
        setR(b);
    }
};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    wcout << L"Введите координаты центра окружности: ";
    float x, y;
    cin >> x >> y;
    wcout << L"Введите радиус окружности: ";
    float r;
    cin >> r;

    Circle C(x, y, r);
    wcout << L"Окружность с центром в (" << C.X() << ", " << C.Y() << ")" << endl;
    wcout << L"и радиусом " << r << endl;
    wcout << L"Полуоси: " << C.A() << L" и " << C.B() << endl;

    wcout << L"Введите новый радиус окружности: ";
    cin >> r;
    C.setR(r);
    wcout << L"Полуоси после изменения радиуса: " << C.A() << L" и " << C.B() << endl;

    return 0;
}
