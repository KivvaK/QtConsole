#include <locale>
#include <iostream>
#include <cmath>

using namespace std;

class Vector {
private:
    float x, y, z;
    float length;
public:
    Vector(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        updateLength();
    }
    Vector() : Vector(0.f, 0.f, 0.f) { }

    float getLength() {
        return length;
    }

    float X() {
        return x;
    }

    float Y() {
        return y;
    }

    float Z() {
        return z;
    }

    void setX(float x) {
        this->x = x;
        updateLength();
    }

    void setY(float y) {
        this->y = y;
        updateLength();
    }

    void setZ(float z) {
        this->z = z;
        updateLength();
    }

    Vector add(const Vector& v) {
        Vector res(x + v.x, y + v.y, z + v.z);
        return res;
    }

private:
    void updateLength() {
        length = sqrt(x * x + y * y + z * z);
    }
};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    wcout << L"Введите координаты вектора a: ";
    float x, y, z;
    cin >> x >> y >> z;
    Vector A(x, y, z);

    wcout << L"Введите координаты вектора b: ";
    cin >> x >> y >> z;
    Vector B(x, y, z), C = A.add(B);

    wcout << L"a + b = (" << C.X() << ", " << C.Y() << ", " << C.Z() << ")" << endl;
    wcout << L"|a + b| = " << C.getLength() << endl;

    C.setX(C.X() * 2);
    wcout << L"Увеличим координату x вектора (a + b) в два раза: " << endl <<
             L"(" << C.X() << ", " << C.Y() << ", " << C.Z() << ")" << endl <<
             L"|a + b| = " << C.getLength() << endl;

    return 0;
}
