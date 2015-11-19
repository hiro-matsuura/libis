#ifndef IS_CMAT3_H
#define IS_CMAT3_H

#include<is_cmulti.h>
#include<is_func.h>

/**
 @file  is_cmat.h
 @brief 多倍長精度実数型cmultiの3次元配列に関する関数の宣言
 */

/*
 * constructions and destruction
 */
cmulti **cmat3_allocate(int LDA1, int LDA2, int l);
cmulti **cmat3_free(int LDA1, int LDA2, int l, cmulti **A);

/*
 * member variables
 */

/*
 * I/O
 */
void cmat3_print(int m, int n, int l, cmulti **A, int LDA1, int LDA2, const char *name, const char *f, int digits);
/*
 * setting
 */
int cmat3_set_all_z(int m, int n, int l, cmulti **A, int LDA1, int LDA2, dcomplex a);
int cmat3_set_all_dd(int m, int n, int l, cmulti **A, int LDA1, int LDA2, double a_r, double a_i);
int cmat3_set_all_d(int m, int n, int l, cmulti **A, int LDA1, int LDA2, double a);
int cmat3_set_zeros(int m, int n, int l, cmulti **A, int LDA1, int LDA2);
int cmat3_set_ones(int m, int n, int l, cmulti **A, int LDA1, int LDA2);
void cmat3_set_rand(int m, int n, int l, cmulti **A, int LDA1, int LDA2, double a, double b);


/*
 * casting
 */

/*
 * rearange elements
 */

/*
 * operations with auto precision mode
 */
// B=A
int cmat3_copy(int m, int n, int l, cmulti **B, int LDB1, int LDB2, cmulti **A, int LDA1, int LDA2);
// B=-A
int cmat3_neg(int m, int n, int l, cmulti **B, int LDB1, int LDB2, cmulti **A, int LDA1, int LDA2);
// C=A+B
int cmat3_add(int m, int n, int l, cmulti **C, int LDC1, int LDC2, cmulti **A, int LDA1, int LDA2, cmulti **B, int LDB1, int LDB2);
// C=A+b
int cmat3_add_c(int m, int n, int l, cmulti **C, int LDC1, int LDC2, cmulti **A, int LDA1, int LDA2, cmulti *b);

/*
 * oparations
 */

/*
 * compare
 */

/*
 * mapping
 */


#endif
