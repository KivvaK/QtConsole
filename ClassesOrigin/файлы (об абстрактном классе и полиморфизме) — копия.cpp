#include <locale>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

class IOStream {
public:
    virtual void putValue(int x) = 0;
    virtual int getValue() = 0;
};

class BinaryFile : public IOStream {
private:
    fstream f;
    char* fname;

public:
    BinaryFile(const char* filename, ios_base::openmode mode) {
        fname = new char[strlen(filename) + 1];
        strcpy(fname, filename);

        open(mode);
    }
    ~BinaryFile() {
        f.close();
        delete[] fname;
    }

    void open(ios_base::openmode mode) {
        f.open(fname, ios::binary | mode);
        assert(f && "Не удалось открыть файл");
    }

    void close() {
        f.close();
    }

    virtual void putValue(int x) override {
        f.write((char*)&x, sizeof(x));
    }

    virtual int getValue() override {
        int x;
        f.read((char*)&x, sizeof(x));

        return x;
    }
};

class TextFile : public IOStream {
private:
    fstream f;
    char* fname;

public:
    TextFile(const char* filename, ios_base::openmode mode) {
        fname = new char[strlen(filename) + 1];
        strcpy(fname, filename);

        open(mode);
    }
    ~TextFile() {
        f.close();
        delete[] fname;
    }

    void open(ios_base::openmode mode) {
        f.open(fname, mode);
        assert(f && "Не удалось открыть файл");
    }

    void close() {
        f.close();
    }

    virtual void putValue(int x) override {
        f << x << " ";
    }

    virtual int getValue() override {
        int x;
        f >> x;

        return x;
    }
};

class ConsoleIO : public IOStream {
public:
    ConsoleIO() {
    }

    virtual void putValue(int x) override {
        cout << x << " ";
    }

    virtual int getValue() override {
        int x;
        cin >> x;

        return x;
    }
};

void outputArray(IOStream& s, const int* a, int n) {
    for (int i = 0; i < n; i++)
        s.putValue(a[i]);
}

void inputArray(IOStream& s, int* a, int n) {
    for (int i = 0; i < n; i++)
        a[i] = s.getValue();
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    const int N = 256;
    char fname[N];
    wcout << L"Введите имя бинарного файла:" << endl;
    cin.getline(fname, N);

    BinaryFile bin(fname, ios::out);

    wcout << L"Введите имя текстового файла:" << endl;
    cin.getline(fname, N);

    TextFile text(fname, ios::out);

    int n;
    wcout << L"Введите длину массива: ";
    cin >> n;
    int* a = new int[n];

    ConsoleIO cons;
    wcout << L"Введите элементы массива:" << endl;
    inputArray(cons, a, n);
    outputArray(bin, a, n);
    bin.close();
    outputArray(text, a, n);
    text.close();
    wcout << L"Массив записан в файлы" << endl << endl;

    int* b = new int[n];
    int* c = new int[n];

    bin.open(ios::in);
    inputArray(bin, b, n);

    text.open(ios::in);
    inputArray(text, c, n);
    wcout << L"Массив, прочитанный из бинарного файла:" << endl;
    outputArray(cons, b, n);
    wcout << endl;

    wcout << L"Массив, прочитанный из текстового файла:" << endl;
    outputArray(cons, c, n);
    wcout << endl;

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
