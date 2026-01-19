#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define u32 uint32_t
#define f32 float
#define SIZE 1024

typedef struct {
    u32 rows, cols;
    f32* data;
} Matrix;

// ~2.116s
f32 sum_mat_col_row(
    const Matrix* mat
){
    f32 sum = 0.0f;

    for(
        u32 col = 0;
            col < mat->cols;
            col++
    ){
        for(
            u32 row = 0;
                row < mat->rows;
                row++
        ){

            sum += mat->data[col + row * mat->cols];
        }
    }

    return sum;
}

// ~0.77s
f32 sum_mat_row_col(
    const Matrix* mat
){
    f32 sum = 0.0f;

    for(
        u32 row = 0;
            row < mat->rows;
            row++
    ){
        for(
            u32 col = 0;
                col < mat->cols;
                col++
        ){

            sum += mat->data[col + row * mat->cols];
        }
    }

    return sum;
}

int main(){

    Matrix example = {SIZE, SIZE};
    example.data = (f32*)malloc(SIZE * SIZE * sizeof(f32));

    for(
        u32 i = 0;
            i < SIZE * SIZE;
            i++
    ){
        example.data[i] = (f32)rand() / (f32)RAND_MAX;
    }

    f32 total_sum = 0;
    for(
        u32 i = 0;
            i < 1000;
            i++
    ){
        total_sum += sum_mat_col_row(&example);
    }

    printf("Soma: %f\n", total_sum);

    free(example.data);
    return 0;
}
