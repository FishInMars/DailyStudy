/*
 * trans.c - 矩阵转置B=A^T
 *每个转置函数都必须具有以下形式的原型：
 *void trans（int M，int N，int a[N][M]，int B[M][N]）；
 *通过计算，块大小为32字节的1KB直接映射缓存上的未命中数来计算转置函数。
 */
#include <stdio.h>
#include "cachelab.h"
int is_transpose(int M, int N, int A[N][M], int B[M][N]);
char transpose_submit_desc[] = "Transpose submission"; //请不要修改“Transpose_submission”

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{

    //                          请在此处添加代码
    //*************************************Begin********************************************************
    if (M == 32)
    {
        int i, j, k;
        int v1, v2, v3, v4, v5, v6, v7, v8;
        for (i = 0; i < 32; i += 8)
            for (j = 0; j < 32; j += 8)
                for (k = i; k < (i + 8); ++k)
                {
                    v1 = A[k][j];
                    v2 = A[k][j + 1];
                    v3 = A[k][j + 2];
                    v4 = A[k][j + 3];
                    v5 = A[k][j + 4];
                    v6 = A[k][j + 5];
                    v7 = A[k][j + 6];
                    v8 = A[k][j + 7];
                    B[j][k] = v1;
                    B[j + 1][k] = v2;
                    B[j + 2][k] = v3;
                    B[j + 3][k] = v4;
                    B[j + 4][k] = v5;
                    B[j + 5][k] = v6;
                    B[j + 6][k] = v7;
                    B[j + 7][k] = v8;
                }
    }
    else if (M == 64)
    {
        int i, j, k, l;
        int v1, v2, v3, v4, v5, v6, v7, v8;
        for (i = 0; i < N; i += 8)
            for (j = 0; j < M; j += 8)
            {
                for (k = i; k < i + 4; ++k)
                {
                    v1 = A[k][j];
                    v2 = A[k][j + 1];
                    v3 = A[k][j + 2];
                    v4 = A[k][j + 3];
                    v5 = A[k][j + 4];
                    v6 = A[k][j + 5];
                    v7 = A[k][j + 6];
                    v8 = A[k][j + 7];

                    B[j][k] = v1;
                    B[j + 1][k] = v2;
                    B[j + 2][k] = v3;
                    B[j + 3][k] = v4;
                    B[j][k + 4] = v5;
                    B[j + 1][k + 4] = v6;
                    B[j + 2][k + 4] = v7;
                    B[j + 3][k + 4] = v8;
                }
                for (l = j; l < j + 4; ++l)
                {
                    v1 = A[i + 4][l];
                    v2 = A[i + 5][l];
                    v3 = A[i + 6][l];
                    v4 = A[i + 7][l];
                    v5 = B[l][i + 4];
                    v6 = B[l][i + 5];
                    v7 = B[l][i + 6];
                    v8 = B[l][i + 7];

                    B[l][i + 4] = v1;
                    B[l][i + 5] = v2;
                    B[l][i + 6] = v3;
                    B[l][i + 7] = v4;
                    B[l + 4][i] = v5;
                    B[l + 4][i + 1] = v6;
                    B[l + 4][i + 2] = v7;
                    B[l + 4][i + 3] = v8;
                }
                for (k = i + 4; k < i + 8; ++k)
                {
                    v1 = A[k][j + 4];
                    v2 = A[k][j + 5];
                    v3 = A[k][j + 6];
                    v4 = A[k][j + 7];
                    B[j + 4][k] = v1;
                    B[j + 5][k] = v2;
                    B[j + 6][k] = v3;
                    B[j + 7][k] = v4;
                }
            }
    }
    else if (M == 61)
    {
        int i, j, k, l;
        int v1;
        for(i = 0; i < 61; i += 17) {
            for(j = 0; j < 67; j += 17) {
                for (k = j; k < j + 17 && k < 67; ++k) {
                    for(l = i; l < i + 17 && l < 61; ++l) {
                        v1 = A[k][l];
                        B[l][k]=v1;
                    }
                }
            }
        }
    }

    //**************************************End**********************************************************
}

/*
 * 我们在下面定义了一个简单的方法来帮助您开始，您可以根据下面的例子把上面值置补充完整。
 */

/*
 * 简单的基线转置功能，未针对缓存进行优化。
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions-此函数向驱动程序注册转置函数。
 *在运行时，驱动程序将评估每个注册的函数并总结它们的性能。这是一种试验不同转置策略的简便方法。
 */
void registerFunctions()
{
    /* 注册解决方案函数  */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* 注册任何附加转置函数 */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - 函数检查B是否是A的转置。在从转置函数返回之前，可以通过调用它来检查转置的正确性。
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
