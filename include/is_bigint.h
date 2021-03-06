#ifndef IS_BIGINT_H
#define IS_BIGINT_H

#include<is_rmulti.h>
#include<is_cmulti.h>

#define BIGINT_DEFAULT_PREC 64

typedef struct { rmulti *num,*den; } bigint_struct;
typedef bigint_struct bigint;

#define BIGINT_NUM(X) (X)->num
#define BIGINT_DEN(X) (X)->den

// allocate and free
bigint *bigint_allocate(void);
bigint *bigint_allocate_int(int num, int den);
bigint *bigint_allocate_str(const char *num, const char *den);
bigint *bigint_allocate_script(const char *str);
bigint *bigint_allocate_clone(bigint *x);
bigint *bigint_free(bigint *x);
void bigint_check(bigint *x);
int bigint_gcd(rmulti *gcd, rmulti *m0, rmulti *n0);

// cast
// x=(bigint)value
int rset_bi(rmulti *x, bigint *value);

// init
void bigint_set_nan(bigint *x);
void bigint_set_inf(bigint *x);
void bigint_set_zero(bigint *x);
void bigint_set_one(bigint *x);
void bigint_set_int(bigint *x, int num, int den);
void bigint_set_str(bigint *x, const char *num, const char *den);
void bigint_set_script(bigint *x, const char *str);

// operations
void bigint_copy(bigint *y, bigint *x);           // y=x
void bigint_swap(bigint *x, bigint *y);           // x<->y
void bigint_neg(bigint *z, bigint *x);            // z=-x
void bigint_mul(bigint *z, bigint *x, bigint *y); // z=x*y
void bigint_div(bigint *z, bigint *x, bigint *y); // z=x/y
void bigint_inv(bigint *z, bigint *x);            // z=1/x
void bigint_add(bigint *z, bigint *x, bigint *y); // z=x+y
void bigint_sub(bigint *z, bigint *x, bigint *y); // z=x-y
void bigint_pow_n(bigint *z, bigint *x, int p);   // z=x^p
int bigint_cmp(bigint *x, bigint *y);             // x<=>y
int bigint_is_integer(bigint *x);
int bigint_is_nan(bigint *x);
int bigint_is_inf(bigint *x);
int bigint_is_zero(bigint *x);
int bigint_is_one(bigint *x);
int bigint_is_neg_one(bigint *x);
int bigint_sgn(bigint *x);
int bigint_get_si(bigint *x);
int bigint_get_rmulti(rmulti *z, bigint *x);
int bigint_get_cmulti(cmulti *z, bigint *x);
void bigint_print(bigint *x);

#endif
