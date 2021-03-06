#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdarg.h>
#include"is_macros.h"
#include"is_dcomplex.h"
#include"is_rmulti.h"
#include"is_cmulti.h"
#include"is_irmulti.h"
#include"is_icmulti.h"
#include"is_irmat3.h"
#include"is_icmat3.h"
#include"is_icmat.h"

/**
 @file  icmat.c
 @brief 多倍長精度複素数型cmultiの行列に関する関数の定義
 @details cmulti型の関数に関する定義は@link cmulti.c@endlinkを参照のこと.
          cmulti型のベクトルの関数に関する定義は@link cvec.c@endlinkを参照のこと.
 */

/////////////////////////////////////////////////////

/** @name cmulti型の行列の初期化に関する関数 */
/** @{ */


/** @} */

/////////////////////////////////////////////////////

/** @name cmulti型の行列のメンバ変数に関する関数 */
/** @{ */

/** @} */

////////////////////////////////////////////////////////////////////////

/** @name cmulti型の行列の入出力に関する関数 */
/** @{ */


/** @} */

/////////////////////////////////////////////////////////

/** @name cmulti型の行列の値の設定に関する関数 */
/** @{ */

/**
 @brief cmulti型の3次元配列の値のコピー [B0,B1]=[A0,A1]
*/
int icmat3_copy(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=iccopy(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

//追加

/**
 @brief cmulti型の3次元配列の値のコピー [B0,B1]=[A0,A1]
*/
int icmat3_copy_irmat3(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, rmulti **A0, rmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=iccopy_r(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

/**
 @brief cmulti型の3次元配列の値のコピー [C0,C1]=[A0,A1]+[B0,B1]i
*/
int icmat3_copy_irmat3_irmat3(int m, int n, int l, cmulti **C0, cmulti **C1, int LDC1, int LDC2, rmulti **A0, rmulti **A1, int LDA1, int LDA2, rmulti **B0, rmulti **B1, int LDB1, int LDB2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=iccopy_rr(MAT3(C0,i,j,k,LDC1,LDC2),MAT3(C1,i,j,k,LDC1,LDC2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2),MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2));
      }
    }
  }
  return e;
}


/**
 @brief cmulti型の3次元配列の値のコピー [C0,C1]=[a0,a1]+[B0,B1]i
*/
int icmat3_copy_ir_irmat3(int m, int n, int l, cmulti **C0, cmulti **C1, int LDC1, int LDC2, rmulti *a0, rmulti *a1, rmulti **B0, rmulti **B1, int LDB1, int LDB2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=iccopy_rr(MAT3(C0,i,j,k,LDC1,LDC2),MAT3(C1,i,j,k,LDC1,LDC2),a0,a1,MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2));
      }
    }
  }
  return e;
}


/**
 @brief cmulti型の3次元配列の値のコピー [C0,C1]=[A0,A1]+[b0,b1]i
*/
int icmat3_copy_irmat3_ir(int m, int n, int l, cmulti **C0, cmulti **C1, int LDC1, int LDC2, rmulti **A0, rmulti **A1, int LDA1, int LDA2, rmulti *b0, rmulti *b1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=iccopy_rr(MAT3(C0,i,j,k,LDC1,LDC2),MAT3(C1,i,j,k,LDC1,LDC2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2),b0,b1);
      }
    }
  }
  return e;
}

//ここまで

/**
 @brief cmulti型の3次元配列の値を倍精度実数から設定 [B0,B1]=cmulti(A).
*/
int icmat3_set_z(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, dcomplex *A, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icset_z(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

//追加

/**
 @brief cmulti型の3次元配列の値を倍精度実数から設定 C=cmulti(A,B).
*/
int icmat3_set_zz(int m, int n, int l, cmulti **C0, cmulti **C1, int LDC1, int LDC2, dcomplex *A, int LDA1, int LDA2, dcomplex *B, int LDB1, int LDB2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icset_zz(MAT3(C0,i,j,k,LDC1,LDC2),MAT3(C1,i,j,k,LDC1,LDC2),MAT3(A,i,j,k,LDA1,LDA2),MAT3(B,i,j,k,LDB1,LDB2));
      }
    }
  }
  return e;
}

//ここまで

/**
 @brief cmulti型の3次元配列の値を倍精度実数から設定 [B0,B1]=cmulti(A).
*/
int icmat3_set_d(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, double *A, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icset_d(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

/** @} */




////////////////////////////////////////////////////////////////////////

/** @name その他 */
/** @{ */


/**
 @brief 区間の中心 [m-r,m+r]=[A0,A1]
*/
int icmat3_mid(int m, int n, int l, cmulti **mid, int LD1mid, int LD2mid, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmid(MAT3(mid,i,j,k,LD1mid,LD2mid),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

/**
 @brief 区間の半径 [m-r,m+r]=[A0,A1]
*/
int icmat3_rad(int m, int n, int l, cmulti **rad, int LD1rad, int LD2rad, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icrad(MAT3(rad,i,j,k,LD1rad,LD2rad),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

/**
 @brief 区間の中心と半径 [m-r,m+r]=[A0,A1]
*/
int icmat3_mr(int m, int n, int l, cmulti **mid, int LD1mid, int LD2mid, cmulti **rad, int LD1rad, int LD2rad, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmr(MAT3(mid,i,j,k,LD1mid,LD2mid),MAT3(rad,i,j,k,LD1rad,LD2rad),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

//追加

/**
 @brief icmulti型の3次元配列の共役 B=conj(A)
*/
int icmat3_conj(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icconj(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

//ここまで

//編集済み
/**
 @brief icmulti型の3次元配列の符号反転 B=-A.
*/
int icmat3_neg(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icneg(MAT3(B0,i,j,k,LDB1,LDB2),MAT3(B1,i,j,k,LDB1,LDB2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}
//ここまで

/**
 @brief 足し算 [Z0,Z1]=[X0,X1]+[Y0,Y1]
*/
int icmat3_add(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icadd(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 足し算 [Z0,Z1]=[X0,X1]+[Y0,Y1]
*/
int icmat3_add_rmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icadd_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

//編集済み
/**
@brief 足し算 [Z0,Z1]=[X0,X1]+[y0,y1]
*/
int icmat3_add_r(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti *Y0, rmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icadd_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
@brief 足し算 [Z0,Z1]=[X0,X1]+[y0,y1]
*/
int icmat3_add_c(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icadd(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}
/**
@brief 足し算 [Z0,Z1]=[X0,X1]+[y0,y1]
*/
int irmat3_add_c(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icadd_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),Y0,Y1,MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2));
      }
    }
  }
  return e;
}
/**
 @brief 引き算 [Z0,Z1]=[X0,X1]-[Y0,Y1]
*/
int icmat3_sub(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}
//編集済み

/**
@brief 引き算 [Z0,Z1]=[x0,x1]-[Y0,Y1]
*/
int icmat3_sub_c1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti *X0, cmulti *X1, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}
/**
@brief 引き算 [Z0,Z1]=[X0,X1]-[y0,y1]
*/
int icmat3_sub_c2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
@brief 引き算 [Z0,Z1]=[x0,x1]-[Y0,Y1]
*/
int icmat3_sub_r1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti *X0, rmulti *X1, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=irsub_c(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
@brief 引き算 [Z0,Z1]=[X0,X1]-[y0,y1]
*/
int icmat3_sub_r2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti *Y0, rmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
@brief 引き算 [Z0,Z1]=[x0,x1]-[Y0,Y1]
*/
int irmat3_sub_c1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti *X0, cmulti *X1, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
@brief 引き算 [Z0,Z1]=[X0,X1]-[y0,y1]
*/
int irmat3_sub_c2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=irsub_c(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
 @brief 引き算 [Z0,Z1]=[X0,X1]-[Y0,Y1]
*/
int icmat3_sub_rmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icsub_r(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}
/**
 @brief 引き算 [Z0,Z1]=[X0,X1]-[Y0,Y1]
*/
int irmat3_sub_cmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=irsub_c(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}


/**
@brief 掛け算 [Z0,Z1]=[X0,X1]*[Y0,Y1]
*/
int icmat3_mul(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmul(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}


/**
@brief 掛け算 [Z0,Z1]=[X0,X1]*[Y0,Y1]
*/
int icmat3_mul_rmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmul_r2(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
@brief 掛け算 [Z0,Z1]=[X0,X1]*[y0,y1]
*/
int icmat3_mul_c(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmul(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
@brief 掛け算 [Z0,Z1]=[X0,X1]*[y0,y1]
*/
int icmat3_mul_r(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti *Y0, rmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmul_r2(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}


/**
@brief 掛け算 [Z0,Z1]=[X0,X1]*[y0,y1]
*/
int irmat3_mul_c(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icmul_r1(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}


/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[Y0,Y1]
*/
int icmat3_div(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[Y0,Y1]
*/
int icmat3_div_rmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r2(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[Y0,Y1]
*/
int irmat3_div_cmat3(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r1(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[x0,x1]./[Y0,Y1]
*/
int icmat3_div_c1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti *X0, cmulti *X1, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[y0,y1]
*/
int icmat3_div_c2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[x0,x1]./[Y0,Y1]
*/
int icmat3_div_r1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti *X0, rmulti *X1, cmulti **Y0, cmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r1(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}


/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[y0,y1]
*/
int icmat3_div_r2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti **X0, cmulti **X1, int LDX1, int LDX2, rmulti *Y0, rmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r2(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[x0,x1]./[Y0,Y1]
*/
int irmat3_div_c1(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, cmulti *X0, cmulti *X1, rmulti **Y0, rmulti **Y1, int LDY1, int LDY2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r2(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),X0,X1,MAT3(Y0,i,j,k,LDY1,LDY2),MAT3(Y1,i,j,k,LDY1,LDY2));
      }
    }
  }
  return e;
}

/**
 @brief 割り算 [Z0,Z1]=[X0,X1]./[y0,y1]
*/
int irmat3_div_c2(int m, int n, int l, cmulti **Z0, cmulti **Z1, int LDZ1, int LDZ2, rmulti **X0, rmulti **X1, int LDX1, int LDX2, cmulti *Y0, cmulti *Y1)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icdiv_r1(MAT3(Z0,i,j,k,LDZ1,LDZ2),MAT3(Z1,i,j,k,LDZ1,LDZ2),MAT3(X0,i,j,k,LDX1,LDX2),MAT3(X1,i,j,k,LDX1,LDX2),Y0,Y1);
      }
    }
  }
  return e;
}

//ここまで
/** @} */



////////////////////////////////////////////////////////////////////////
//追加
/** @name cmulti型の3次元配列の数学関数に関する関数 */
/** @{ */

/**
 @brief icmulti型の3次元配列の絶対値 C=abs(A).
*/
int icmat3_abs(int m, int n, int l, rmulti **C0, rmulti **C1, int LDC1, int LDC2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int i,j,k,e=0;
  for(k=0; k<l; k++){
    for(j=0; j<n; j++){
      for(i=0; i<m; i++){
	e+=icabs(MAT3(C0,i,j,k,LDC1,LDC2),MAT3(C1,i,j,k,LDC1,LDC2),MAT3(A0,i,j,k,LDA1,LDA2),MAT3(A1,i,j,k,LDA1,LDA2));
      }
    }
  }
  return e;
}

/**
 @brief icmulti型の3次元配列の和 B=sum(A).
*/
int icmat3_sum(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti**A1, int LDA1, int LDA2)
{
  int k,e=0;
  for(k=0; k<l; k++){
    e+=icvec_sum_icmat(m,n,&MAT3(B0,0,0,k,LDB1,LDB2),&MAT3(B1,0,0,k,LDB1,LDB2),&MAT3(A0,0,0,k,LDA1,LDA2),&MAT3(A1,0,0,k,LDA1,LDA2),LDA1);
  }
  return e;
}

/**
 @brief icmulti型の3次元配列の最大値 [B0,B1]=[max(A0),max(A1)].
*/
int icmat3_max(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int k,e=0;
  for(k=0; k<l; k++){
    e+=icvec_max_icmat(m,n,&MAT3(B1,0,0,k,LDB1,LDB2),&MAT3(B0,0,0,k,LDB1,LDB2),&MAT3(A0,0,0,k,LDA1,LDA2),&MAT3(A1,0,0,k,LDA1,LDA2),LDA1);
  }
  return e;
}

/**
 @brief icmulti型の3次元配列の最大値 [B0,B1]=[A0,max(A1)].
*/
int icmat3_umax(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int k,e=0;
  for(k=0; k<l; k++){
    e+=icvec_umax_icmat(m,n,&MAT3(B1,0,0,k,LDB1,LDB2),&MAT3(B0,0,0,k,LDB1,LDB2),&MAT3(A0,0,0,k,LDA1,LDA2),&MAT3(A1,0,0,k,LDA1,LDA2),LDA1);
  }
  return e;
}

/**
 @brief icmulti型の3次元配列の最小値 [B0,B1]=[min(A0),min(A1)].
*/
int icmat3_min(int m, int n, int l, cmulti **B0, cmulti **B1, int LDB1, int LDB2, cmulti **A0, cmulti **A1, int LDA1, int LDA2)
{
  int k,e=0;
  for(k=0; k<l; k++){
    e+=icvec_min_icmat(m,n,&MAT3(B1,0,0,k,LDB1,LDB2),&MAT3(B0,0,0,k,LDB1,LDB2),&MAT3(A0,0,0,k,LDA1,LDA2),&MAT3(A1,0,0,k,LDA1,LDA2),LDA1);
  }
  return e;
}


//ここまで

//EOF
