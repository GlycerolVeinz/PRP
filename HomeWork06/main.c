#include <stdio.h>
#include <stdlib.h>

#define ERR_ENTRY 100
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

void err_msg()
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    exit(ERR_ENTRY);
}

void read_matrix(int rows, int colls, int matrix[rows][colls])
{
    // read numbers 4 matrix
    int detect_row = 0;
    int detect_coll = 0;
    char detect;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colls; j++)
        {
            // if can't read then err
            if ((scanf("%d", &matrix[i][j])) != 1)
            {
                err_msg();
            }

            // prepare for coll & row checks
            detect = getchar();
            switch (detect)
            {
                case ' ':
                    detect_coll++;
                    break;

                case '\n':
                    detect_row++;
                    break;
            }
        }

        //check coll in every row, nullify after use
        if (detect_coll != (colls - 1))
        {
            err_msg();
        }
        detect_coll = 0;
    }

    // if num of rows or colls is different then size then err
    if (detect_row != rows)
    {
        err_msg();
    }
}

void compare_size(char fce, int i_row, int i_coll, int ii_row, int ii_coll)
{
    // looks if the operation between matrices is possible
    switch (fce)
    {
        // multiplication
        case '*':
            if (i_coll != ii_row)
            {
                err_msg();
            }
            break;

        // addition
        case '+':
            if ((i_row != ii_row) || (i_coll != ii_coll))
            {
                err_msg();
            }
            break;

        // deduction
        case '-':
            if ((i_row != ii_row) || (i_coll != ii_coll))
            {
                err_msg();
            }
            break;
    }
}

void print_matrix(int rows, int colls, int matrix[rows][colls])
{
    // first print size
    printf("%d %d\n", rows, colls);
    // then print every int
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colls; j++)
        {
            j == 0 ? printf("%d", matrix[i][j]) : printf(" %d", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculate_matrix(char fce, int i_row, int i_coll, int ii_row, int ii_coll, int i_matrix[i_row][i_coll], int ii_matrix[ii_row][ii_coll])
{
    compare_size(fce, i_row, i_coll, ii_row, ii_coll);

    // crate new matrix in case of multiplication
    int dot_matrix[i_row][ii_coll];
    for (int i = 0; i < i_row; i++)
    {
        for (int j = 0; j < ii_coll; j++)
        {
            dot_matrix[i][j] = 0;
        }
    }
            
    switch (fce)
    {
        // add
        case '+':
            // add ints on same positions
            for (int i = 0; i < i_row; i++)
            {
                for (int j = 0; j < i_coll; j++)
                {
                    i_matrix[i][j] += ii_matrix[i][j];
                }
            }

            print_matrix(i_row, i_coll, i_matrix);
            break;

        // subtract
        case '-':
            // sub ints on same positions
            for (int i = 0; i < i_row; i++)
            {
                for (int j = 0; j < i_coll; j++)
                {
                    i_matrix[i][j] -= ii_matrix[i][j];
                }
            }

            print_matrix(i_row, i_coll, i_matrix);
            break;
        
        // multiply
        case '*':
            // pseudocode taken from https://www.researchgate.net/figure/Pseudocode-for-matrix-multiplication_fig3_258926922
            for (int i = 0; i < i_row; i++)
            {
                for (int j = 0; j < ii_coll; j++)
                {
                    for (int k = 0; k < i_coll; k++)
                    {
                        dot_matrix[i][j] += i_matrix[i][k] * ii_matrix[k][j];
                    }        
                }   
            }
            
            print_matrix(i_row, ii_coll, dot_matrix);
            break;       
    }
}

int main(int argc, char const *argv[])
{
    // initialize variables for 1st matrix
    int I_row = 0;
    int I_coll = 0;   
    // read size of matrix, err if can't do so
    if (scanf("%d %d", &I_row, &I_coll) != 2)
    {
        err_msg();
    }

    int I_matrix[I_row][I_coll];
    read_matrix(I_row, I_coll, I_matrix);

    // look what to do /w matrices
    char operand = getchar();

    // initialize variables for 2nd matrix
    int II_row = 0;
    int II_coll = 0;
    // read size of matrix, err if can't do so
    if (scanf("%d %d", &II_row, &II_coll) != 2)
    {
        err_msg();
    }

    int II_matrix[II_row][II_coll];
    read_matrix(II_row, II_coll, II_matrix);

    calculate_matrix(operand, I_row, I_coll, II_row, II_coll, I_matrix, II_matrix);

    exit(SUCCESS);
}
