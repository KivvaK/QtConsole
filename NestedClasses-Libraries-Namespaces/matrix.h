// Заголовочный файл библиотеки работы с матрицами

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstring>

namespace MyMath {
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
        Matrix operator*(double a) const;   // Реализация вынесена в .cpp

        // Объявление внешних функций дружественными
        friend Matrix operator*(double a, const Matrix& M);
        friend std::ostream& operator<<(std::ostream& os, const Matrix& M);
        friend std::istream& operator>>(std::istream& is, Matrix& M);

    private:
        void prepare(int rows, int cols);   // Реализация вынесена в .cpp

        void fill(const double* buf, int rows, int cols) {
            memcpy(this->buf[0], buf, sizeof(double) * rows * cols);
        }
    };

    /// Перегрузка оператора умножения матрицы на число СЛЕВА
    Matrix operator*(double a, const Matrix& M); // Реализация вынесена в .cpp
    /// Перегрузка оператора << для вывода матрицы в поток вывода
    std::ostream& operator<<(std::ostream& os, const Matrix& M); // Реализация вынесена в .cpp
    /// Перегрузка оператора >> для чтения матрицы из потока ввода
    std::istream& operator>>(std::istream& is, Matrix& M); // Реализация вынесена в .cpp
}

#endif // MATRIX_H
