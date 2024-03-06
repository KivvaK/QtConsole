// В этом файле - реализация функций, объявленных в matrix.h

#include <iostream>

#include "matrix.h" // Обязательно

namespace MyMath {
    Matrix Matrix::operator*(double a) const {
        Matrix R(*this);
        for (int i = 0; i < R.rows; i++)
            for (int j = 0; j < R.cols; j++)
                R.buf[i][j] *= a;
        return R;
    }

    void Matrix::prepare(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        buf = new double*[rows];
        buf[0] = new double[rows * cols];
        for (int i = 1; i < this->rows; i++)
            buf[i] = buf[0] + i * cols;
    }

    Matrix operator*(double a, const Matrix& M) {
        // Воспользуемся перегрузкой умножения на число справа
        return M * a;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& M) {
        for (int i = 0; i < M.rows; i++) {
            for (int j = 0; j < M.cols; j++)
                os << M.buf[i][j] << '\t';
            os << std::endl;
        }

        return os;
    }

    std::istream& operator>>(std::istream& is, Matrix& M) {
        for (int i = 0; i < M.rows; i++)
            for (int j = 0; j < M.cols; j++)
                is >> M.buf[i][j];

        return is;
    }
}
