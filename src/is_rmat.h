#ifndef IS_RMAT_H
#define IS_RMAT_H

#include<is_rmulti.h>
#include<is_func.h>

/**
 @file  is_rmat.h
 @brief 多倍長精度実数型rmultiの行列に関する関数の宣言
 */


/*
 * constructions and destruction
 */
rmulti **rmat_allocate(int LDA, int n);
rmulti **rmat_allocate_prec(int LDA, int n, int prec);
rmulti **rmat_allocate_clone(int LDB, int n, rmulti **B);
rmulti **rmat_free(int LDA, int n, rmulti **A);
int rmat_round(int m, int n, rmulti **A, int LDA, int prec);
int rmat_clone(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);   // B=A
int rmat_clone_t(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA); // B=A'
void rmat_clone_index(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, const int *I);
void rmat_swap(int m, int n, rmulti **A, int LDA, rmulti **B, int LDB);   // A<->B

/*
 * member variables
 */
void rmat_get_prec(int m, int n, int *P, int LDP, rmulti **A, int LDA);
int rmat_get_prec_max(int m, int n, rmulti **A, int LDA);
void rmat_get_exp(int m, int n, int *P, int LDP, rmulti **A, int LDA);
int rmat_get_exp_max(int m, int n, rmulti **A, int LDA);
int rmat_is_number(int m, int n, rmulti **A, int LDA);
int rmat_has_nan(int m, int n, rmulti **A, int LDA);

/*
 * I/O
 */
void rmat_print(int m, int n, rmulti **A, int LDA, const char *name, const char *f, int digits);
void rmat_save(int m, int n, rmulti **A, int LDA, int digits, char* fmt, ...);
void rmat_load(int m, int n, rmulti **A, int LDA, char* fmt, ...);
void rmat_bin_save(int m, int n, rmulti **A, int LDA, char* fmt, ...);
rmulti **rmat_bin_load(int *m, int *n, char* fmt, ...);

/*
 * setting
 */
void rmat_set_nan(int m, int n, rmulti **A, int LDA);
void rmat_set_s(int m, int n, rmulti **B, int LDB, char **A, int LDA);
int rmat_set_d(int m, int n, rmulti **B, int LDB, const double *A, int LDA);
int rmat_set_z(int m, int n, rmulti **B, int LDB, const dcomplex *A, int LDA);
int rmat_set_all_d(int m, int n, rmulti **A, int LDA, double a);
int rmat_set_zeros(int m, int n, rmulti **A, int LDA);
int rmat_set_ones(int m, int n, rmulti **A, int LDA);
int rmat_set_eye(int m, int n, rmulti **A, int LDA);
void rmat_set_rand(int m, int n, rmulti **A, int LDA, double a, double b);
int rmat_set_diag_r(int m, int n, rmulti **A, int LDA, rmulti *a, int offset);
int rmat_set_diag_d(int m, int n, rmulti **A, int LDA, double a, int offset);

/*
 * casting
 */
void rmat_get_d(int m, int n, double *B, int LDB, rmulti **A, int LDA);
void rmat_get_z(int m, int n, dcomplex *B, int LDB, rmulti **A, int LDA);


/*
 * rearange elements
 */
void rmat_cols_swap(int m, int n, rmulti **A, int LDA, int k, int l);
void rmat_cols_swap_index(int m, int n, rmulti **A, int LDA, const int *I);
void rmat_rows_swap(int m, int n, rmulti **A, int LDA, int k, int l);

/*
 * operations with auto precision mode
 */
int rmat_copy(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);                                 // B=A
int rmat_copy_t(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);                               // B=A'
void rmat_copy_col_index(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, const int *I);        // B(:,j)=A(:,I(j))
int rmat_copy_index(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, int *I, int *J);           // B=A(I,J)
int rmat_index_copy(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, int *I, int *J);           // B(I,J)=A
int rmat_neg(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);                                  // B=-A
int rmat_abs(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);                                  // B=abs(A)
int rmat_add(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB);             // C=A+B
int rmat_add_r(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti *b);                     // C=A+b
int rmat_sub(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB);             // C=A-B
int rmat_sub_r1(int m, int n, rmulti **C, int LDC, rmulti *a, rmulti **B, int LDB);                    // C=a-B
int rmat_sub_r2(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti *b);                    // C=A-b
int rmat_mul(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB);             // C=A.*B
int rmat_mul_r(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti *b);                     // C=A*b
int rmat_mul_d(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, double b);                      // C=A*b
int rmat_prod(int l, int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB);     // C=A*B
int rmat_add_prod(int l, int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB); // C+=A*B
int rmat_sub_prod(int l, int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB); // C-=A*B
int rmat_rank1op(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, rmulti *a, rmulti **x, rmulti **y); // B=A+a*x*y'
int rmat_diag_copy_rvec(int m, int n, rmulti **A, int LDA, rmulti **a);                                // A=diag(a)
int rmat_diag_copy_r(int m, int n, rmulti **A, int LDA, rmulti *a);                                    // A=diag(a)
int rmat_diag_copy_d(int m, int n, rmulti **A, int LDA, double a);                                     // A=diag(a)
int rmat_diag_add_rvec(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, rmulti **a);            // B=A+diag(a)
int rmat_diag_add_r(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, rmulti *a);                // B=A+diag(a)
int rmat_diag_sub_rvec(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, rmulti **a);            // B=A-diag(a)
int rmat_diag_sub_r(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA, rmulti *a);                // B=A-diag(a)
int rvec_sum_rmat(int m, int n, rmulti **B, rmulti **A, int LDA);
                          // B=sum(A);
int rvec_max_rmat(int m, int n, rmulti **B, rmulti **A, int LDA);                                      // B=max(A)
int rvec_min_rmat(int m, int n, rmulti **B, rmulti **A, int LDA);                                      // B=min(A)
int rmat_max_abs(rmulti *value, int m, int n, rmulti **A, int LDA);                                    // value=max(abs(x))
int rmat_min_abs(rmulti *value, int m, int n, rmulti **A, int LDA);                                    // value=min(abs(x))
int rmat_cols_max_abs_sub(rmulti **x, int m, int n, rmulti **A, int LDA, rmulti **B, int LDB); // x(j)=max(abs(A(:,j)-B(:,j)))
int rmat_cols_max_abs_sub_rvec(rmulti **y, int m, int n, rmulti **A, int LDA, rmulti **x); // y(j)=max(abs(A(:,j)-x))

/*
 * oparations
 */
int rmat_div(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti **B, int LDB); // C=A./B
int rmat_div_r1(int m, int n, rmulti **C, int LDC, rmulti *a, rmulti **B, int LDB);        // C=a./B
int rmat_div_r2(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, rmulti *b);        // C=A./b
int rmat_div_d(int m, int n, rmulti **C, int LDC, rmulti **A, int LDA, double b);
int rmat_inv(int n, rmulti **B, int LDB, rmulti **A, int LDA);                             // B=inv(A)
int rmat_power(int n, rmulti **B, int LDB, rmulti **A, int LDA, int p);                    // B=A^p
int rmat_cols_normalize(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);
int rmat_cols_normalize_sgn(int m, int n, rmulti **B, int LDB, rmulti **A, int LDA);

/*
 * compare
 */
int rmat_cmp(int m, int n, rmulti **A, int LDA, int k, int l, rmulti **B, int LDB);

/*
 * mapping
 */
int rmat_func_list2(int m, int n, rmulti **A, int LDA, func_t *f, int l, rmulti **x); // A=F(x)

#endif
