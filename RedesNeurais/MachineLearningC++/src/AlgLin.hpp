#pragma once

/* Para utilizarmos as seguintes funcionalidades:
 * - std::memset
 * - std::memcpy
 */
#include <cstring>

// Utilizaremos std::vector para não ter que lidar com alocações
#include <vector>

// Para adicionarmos um controle sofisticado dos dados e do tamanho.
#include <cstdint>

// Não utilizaremos ctime e srand(time(NULL)) pois não será necessário
// Uma vez que não utilizaremos os valores aleatórios de fato.
#include <cstdlib>

class Matrix {
public:
    // ----------------------------------------------
    // Atributos Inerentes À Sua Existência
    uint32_t rows, cols;
    std::vector<float> data;

    // ----------------------------------------------
    // Métodos Inerentes À Sua Existência

    Matrix(
        const uint32_t& rows,
        const uint32_t& cols
    ) :
        rows(rows),
        cols(cols)
    { data.reserve(static_cast<uint64_t>(this->rows * this->cols)); }

    ~Matrix(){}

    Matrix& operator=(const Matrix& other) {
        this->rows = other.rows;
        this->cols = other.cols;
        this->data = other.data;
        return *this;
    }

    void clear() {
        this->rows = 0;
        this->cols = 0;
        this->data.clear();
    }


    // ----------------------------------------------





};
