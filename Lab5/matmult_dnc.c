#include <stdio.h>

void matrix_multiply(int **c,int **d,int size,int size2,int **new))
{
    if(size == 1)   // Base case
    {   
        new[0][0] = c[0][0] *d[0][0];   
    }
    else    // Recursive divide-and-conquer case
    {
    // The template for performing the submatrix multiplications is as follows
    // Obtain desired submatrices from input matrices c and d
    // Perform necessary matrix additions on the submatrices
    // Ultimately, perform the matrix multiplication on the submatrices in the following manner:
    // multiplyStrassen(temp1,temp2,size/2,size,s1);

    // ...
    }
}