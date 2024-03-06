#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class Matrix {
private:
    double** buf;
    int rows, cols;
public:
    Matrix(int rows, int cols) {
        prepare(rows, cols);
        memset(buf[0], 0, sizeof(double) * rows * cols);
    }

    Matrix(const Matrix& M) {
        prepare(M.rows, M.cols);
        fill(M.buf[0], M.rows, M.cols);
    }

    ~Matrix() {
        delete[] buf[0];
        delete[] buf;
    }

    int rowCount() const {
        return rows;
    }

    int columnCount() const {
        return cols;
    }

    // Возвращает i-ю строку
    // (а в ней уже можно будет получить j-й элемент)
    double* operator[](int i) {
        return buf[i];
    }

    // Возвращает i-ю строку, если матрица const
    // (а в строке уже можно будет получить j-й элемент)
    const double* operator[](int i) const {
        return buf[i];
    }

    // Перегрузка умножения матрицы на число СПРАВА
    Matrix operator*(double a) const {
        Matrix R(*this);
        for (int i = 0; i < R.rows; i++)
            for (int j = 0; j < R.cols; j++)
                R.buf[i][j] *= a;
        return R;
    }

    // Объявление внешних функций дружественными
    friend Matrix operator*(double a, const Matrix& M);
    friend ostream& operator<<(ostream& os, const Matrix& M);
    friend istream& operator>>(istream& is, Matrix& M);

private:
    void prepare(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        buf = new double*[rows];
        buf[0] = new double[rows * cols];
        for (int i = 1; i < this->rows; i++)
            buf[i] = buf[0] + i * cols;
    }

    void fill(const double* buf, int rows, int cols) {
        memcpy(this->buf[0], buf, sizeof(double) * rows * cols);
    }
};

// Обратите внимание, в классе Matrix функции, идущие ниже,
// объявлены как "дружественные" => они имеют доступ
// к private-членам класса Matrix: buf, rows и cols.

/// Перегрузка оператора умножения матрицы на число СЛЕВА
Matrix operator*(double a, const Matrix& M) {
    // Воспользуемся перегрузкой умножения на число справа
    return M * a;
}

/// Перегрузка оператора << для вывода матрицы в поток вывода
ostream& operator<<(ostream& os, const Matrix& M) {
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++)
            os << M.buf[i][j] << '\t';
        os << endl;
    }

    return os;
}

/// Перегрузка оператора >> для чтения матрицы из потока ввода
istream& operator>>(istream& is, Matrix& M) {
    for (int i = 0; i < M.rows; i++)
        for (int j = 0; j < M.cols; j++)
            is >> M.buf[i][j];

    return is;
}

int main(int argc, char *argv[])
{
    // ВНИМАНИЕ! Для корректного запуска в Qt, поддерживающего
    // ввод с клавиатуры, необходимо нажать слева на панели
    // "Проекты"->"Запустить" и установить галочку
    // "запускать в терминале".

    cout << "Input matrix's rows and columns count: ";
    int n, m;
    cin >> n >> m;

    Matrix A(n, m);
    cout << "Input matrix elements:" << endl;
    cin >> A;
    cout << endl << "Your matrix A is:" << endl << A;
    cout << "Input multiplier: ";
    double a;
    cin >> a;
    Matrix B = a * A;
    cout << endl << a << " * A = " << endl << B;

    return 0;
}
