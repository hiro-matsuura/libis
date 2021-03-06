//新規作成中
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"is_macros.h"
#include"is_irmulti.h"
#include"is_irvec.h"
#include"is_rmat.h"
#include"is_irmat.h"
#include"is_irsolve.h"
#include"is_rmulti.h"
#include"is_ivec.h"
#include"is_rvec.h"
/**
 @file  irsolve.c
 @brief 多倍長精度実数型rmultiの機械区間演算による線形方程式A*X=Bの解法に関する関数の定義.
 @details irmulti型の関数に関する定義は@link irmulti.c@endlinkを参照のこと.
          irmulti型のベクトルの関数に関する定義は@link irvec.c@endlinkを参照のこと.
          irmulti型の行列の関数に関する定義は@link irmat.c@endlinkを参照のこと.
 */

#define MA0(I,J) (MAT(A0,(I),(J),LDA))
#define MA1(I,J) (MAT(A1,(I),(J),LDA))
#define MB0(I,J) (MAT(B0,(I),(J),LDB))
#define MB1(I,J) (MAT(B1,(I),(J),LDB))
#define MC0(I,J) (MAT(C0,(I),(J),LDC))
#define MC1(I,J) (MAT(C1,(I),(J),LDC))
//マクロ使っていない場所あり
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @name 線形方程式 A*X=B の解法に関する関数 */
/** @{ */

/**
 @brief 線形方程式A*X=Bの解法.
 @param[in]  B サイズ(n,NRHS)の行列B.
 @param[out] B サイズ(n,NRHS)の解の行列X.
 @param[in]  A サイズnの正方行列で係数行列A.
 */
int irsolve(int n, int NRHS, rmulti **B0, rmulti **B1, int LDB, rmulti **A0, rmulti **A1, int LDA, int *info)
{
  int prec0,prec1,prec,e=0;
  rmulti **C0=NULL, **C1=NULL;
  prec0=rmat_get_prec_max(n,NRHS,B0,LDB);
  prec1=rmat_get_prec_max(n,NRHS,B1,LDB);
  prec=MAX2(prec0,prec1);
  C0=rmat_allocate_prec(n,n,prec);
  C1=rmat_allocate_prec(n,n,prec);
  e+=irmat_copy(n,n,C0,n,C1,n,A0,LDA,A1,LDA);
  //e+=irsolve_lu(n,NRHS,B0,B1,LDB,C0,C1,n,info);
  e+=irsolve_gauss_sweeper(n,NRHS,B0,B1,LDB,C0,C1,n,info);
 
  C0=rmat_free(n,n,C0);
  C1=rmat_free(n,n,C1);
  return e;
}
//まだ
/**
 @brief 線形方程式A*X=Bの残差 R=B-A*X
 @param[in]  A サイズ(n,n)の係数行列A.
 @param[in]  B サイズ(n,NRHS)の非同次項の行列B.
 @param[in]  X サイズ(n,NRHS)の解の行列X.
 @param[out] R サイズ(n,NRHS)の残差の行列X.
*/
/*
int rsolve_residual(int n, int NRHS, rmulti **R, int LDR, rmulti **A, int LDA, rmulti **X, int LDX, rmulti **B, int LDB)
{
  int e=0;
  e+=rmat_copy(n,NRHS,R,LDR,B,LDB);              // R=B
  e+=rmat_sub_prod(n,n,NRHS,R,LDR,A,LDA,X,LDX);  // R=R-A*X
  return e;
}
*/
/** @} */

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @name LU分解に関する関数 */
/** @{ */
 
/**
 @brief 線形方程式A*X=BのLU分解による解法.
 @param[in]  B 行列B.サイズは(n,NRHS).
 @param[out] B 解の行列X.サイズは(n,NRHS).
 @param[in]  A 係数行列A.サイズは(n,n).
 @param[out] A 破壊される.
 */
 
int irsolve_lu(int n, int NRHS, rmulti **B0, rmulti **B1, int LDB, rmulti **A0, rmulti **A1, int LDA, int *info)
{
  int ret=0,*p0=NULL,*p1=NULL,e=0;
  // allocate
  p0=ivec_allocate(n);p1=ivec_allocate(n);
  // LU decomposition
  e+=irsolve_lu_decomp(n,A0,A1,LDA,p0,p1,&ret);
  // solve by A=L*U,L*y=b,U*x=y
  if(ret==0){ e+=irsolve_lu_backsubs(n,NRHS,B0,B1,LDB,A0,A1,LDA,p0,p1); }
  // free
  p0=ivec_free(p0);p1=ivec_free(p1);
  // done
  (*info)=ret;
  return e;
}


/**
 @brief 行列AのLU分解.
 @param[in]  A サイズnの正方行列A.
 @param[out] A LU分解の結果.
 @param[in]  p サイズがnの初期化済みの配列.
 @param[out] p ピボット選択の結果.
*/
int irsolve_lu_decomp(int n, rmulti **A0, rmulti **A1, int LDA, int *p0, int *p1, int *info)
{
  int prec0,prec1,prec,ret=0,e=0,i,j,k,l;
  rmulti *a0=NULL,*a1=NULL,*value0=NULL,*value1=NULL;
  //allocate
  prec0=rmat_get_prec_max(n,n,A0,LDA);prec1=rmat_get_prec_max(n,n,A1,LDA);
  prec=MAX2(prec0,prec1);
  a0=rallocate_prec(prec);a1=rallocate_prec(prec);
  value0=rallocate_prec(prec);value1=rallocate_prec(prec);
  // LU分解
  for(k=0; k<n; k++){    
    // pivot select
    e+=irabs(value0,value1,MA0(k,k),MA1(k,k));
    for(l=k,j=k+1; j<n; j++){
      e+=irabs(a0,a1,MA0(j,k),MA1(j,k));
      if(rgt(a0,value0)) { l=j; e+=ircopy(value0,value1,a0,a1); } // value=a
    }
    // エラー処理
    if(ris_zero(value0) || ris_zero(value1)){ ret=l+1; break; }
    p0[k]=l;p1[k]=l;
    // swap A(k,k:end)<-> A(l,k:end)
    if(l!=k){
      for(j=k; j<n; j++){
	rswap(MA0(k,j),MA0(l,j));
	rswap(MA1(k,j),MA1(l,j));
      }
    }
    // L行列とU行列の作成
    for(i=k+1; i<n; i++){
      e+=irdiv(a0,a1,MA0(i,k),MA1(i,k),MA0(k,k),MA1(k,k));
      // L行列 A(i,k)=a
      e+=ircopy(MA0(i,k),MA1(i,k),a0,a1);
      // U行列 A(i,k+1:end)+=(-a)*A(k,k+1:end)
      for(j=k+1; j<n; j++){
	e+=irsub_mul(MA0(i,j),MA1(i,j),a0,a1,MA0(k,j),MA1(k,j));
      }
    }
  }
  // done
  a0=rfree(a0);a1=rfree(a1);
  value0=rfree(value0);value1=rfree(value1);
  (*info)=ret;
  return e;
}
  
/**
 @brief 線形方程式A*X=Bを後退代入 A=L*U,L*y=b,U*x=y で解く.
 @param[in]  B サイズは(n,NRHS)の行列B.
 @param[out] B 解の行列X.
 @param[in]  A サイズがnの正方行列でLU分解済みの係数行列A.
 @param[in]  p ピボット選択の要素の並び.
*/
int irsolve_lu_backsubs(int n, int NRHS, rmulti **B0, rmulti **B1, int LDB, rmulti **A0, rmulti **A1, int LDA, int *p0, int *p1)
{
  int prec0,prec1,prec,e=0,i,j,k;
  rmulti *a0=NULL,*a1=NULL,*b0=NULL,*b1=NULL;
  // allocate
  prec0=rmat_get_prec_max(n,NRHS,B0,LDB);prec1=rmat_get_prec_max(n,NRHS,B1,LDB);
  prec=MAX2(prec0,prec1);
  a0=rallocate_prec(prec); a1=rallocate_prec(prec);
  b0=rallocate_prec(prec); b1=rallocate_prec(prec);
  // y=inv(L)*b
  for(k=0; k<n-1; k++){
    // swap b(k)<-> b(p[k])
    rmat_rows_swap(n,NRHS,B0,LDB,k,p0[k]);
    rmat_rows_swap(n,NRHS,B1,LDB,k,p1[k]);
    for(i=k+1; i<n; i++){
      for(j=0; j<NRHS; j++){
	e+=irsub_mul(MB0(i,j),MB1(i,j),MA0(i,k),MA1(i,k),MB0(k,j),MB1(k,j));
      }
    }
  }
  // x=inv(U)*y
  for(k=n-1; k>=0; k--){
    for(j=0; j<NRHS; j++){
      e+=irset_d(a0,a1,0);
      for(i=k+1; i<n; i++){
	e+=iradd_mul(a0,a1,MA0(k,i),MA1(k,i),MB0(i,j),MB1(i,j));
      }
      e+=irsub(MB0(k,j),MB1(k,j),MB0(k,j),MB1(k,j),a0,a1);
      e+=irdiv(b0,b1,MB0(k,j),MB1(k,j),MA0(k,k),MA1(k,k));
      e+=ircopy(MB0(k,j),MB1(k,j),b0,b1);
    }
  }
  // done
  a0=rfree(a0);a1=rfree(a1);
  b0=rfree(b0);b1=rfree(b1);
  return e;
}

/** @} */
//ここまで
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @name ガウスの消去法に関する関数 */
/** @{ */
   
/**
 @brief 線形方程式A*X=Bのガウスの消去法による解法.
 @param[in]  B 行列B.サイズは(n,NRHS).
 @param[in]  B 解の行列X.サイズは(n,NRHS).
 @param[in]  A 係数行列A.サイズは(n,n).
 @param[out] A 破壊される.
 */
int irsolve_gauss_sweeper(int n, int NRHS, rmulti **B0, rmulti **B1, int LDB, rmulti **A0, rmulti **A1, int LDA, int *info)
{
  int p0,p1,p2,p3,prec,ret=0,i,j,k,l,e=0;
  rmulti *a0=NULL,*a1=NULL,*value0=NULL,*value1=NULL;
  rmulti **rws=NULL;int rws_size,rwss;
  // allocate
  p0=rmat_get_prec_max(n,NRHS,B0,LDB);
  p1=rmat_get_prec_max(n,NRHS,B1,LDB);
  p2=rmat_get_prec_max(n,n,A0,LDA);
  p3=rmat_get_prec_max(n,n,A1,LDA);
  p0=MAX2(p0,p1);p2=MAX2(p2,p3);
  prec=MAX2(p0,p2);
  a0=rallocate_prec(prec); a1=rallocate_prec(prec);
  value0=rallocate_prec(prec); value1=rallocate_prec(prec);
  rws_size=6; rwss=rws_size;  //ワークスペース
  rws=rvec_allocate_prec(rws_size,prec);
  // 上三角化
  for(k=0; k<n; k++){
    // ピボット選択
    e+=irabs(value0,value1,MA0(k,k),MA1(k,k));
    for(l=k,j=k+1; j<n; j++){
      e+=irabs(a0,a1,MA0(j,k),MA1(j,k));
      if(rgt(a0,value0)) { l=j; e+=ircopy(value0,value1,a0,a1); } // value=a
    }
    if(ris_zero(value0)) { ret=l+1; break; } // error
    if(l!=k){
      rmat_rows_swap(n,NRHS,B0,LDB,k,l);          //swap b0(k) <-> b0(l)
      rmat_rows_swap(n,NRHS,B1,LDB,k,l);          //swap b1(k) <-> b1(l)
      rmat_rows_swap(n,n,A0,LDA,k,l);   
      rmat_rows_swap(n,n,A1,LDA,k,l);           //swap A(k,:) <-> A(l,:)
    }
    //軸要素を1にする
    e+=irinv(a0,a1,MA0(k,k),MA1(k,k));
    for(j=k; j<n; j++) {
      e+=irmul_ws(MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),a0,a1,MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),&rwss,rws);
    }
    for(j=0; j<NRHS; j++) {
      e+=irmul_ws(MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),a0,a1,MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),&rwss,rws);      
    }
    //軸要素以外が 0 になるように他の列から軸要素の列を引く
    for(i=k+1; i<n; i++){
      if(i!=k){
	e+=ircopy(a0,a1,MA0(i,k),MA1(i,k));
	for(j=k; j<n; j++){
	  e+=irsub_mul_ws(MAT(A0,i,j,LDA),MAT(A1,i,j,LDA),a0,a1,MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),&rwss,rws);	 
	}	
	for(j=0; j<NRHS; j++){
	  e+=irsub_mul_ws(MAT(B0,i,j,LDB),MAT(B1,i,j,LDB),a0,a1,MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),&rwss,rws);	 
	}
      }
    }
  }  
  //後退代入 x=inv(U)*b
  if(ret==0){
    for(k=0; k<NRHS; k++){
      for(i=n-1; i>=0; i--){
	for(j=n-1; j>=i+1; j--){
	  e+=irsub_mul_ws(MAT(B0,i,k,LDB),MAT(B1,i,k,LDB),MAT(A0,i,j,LDA),MAT(A1,i,j,LDA),MAT(B0,j,k,LDB),MAT(B1,j,k,LDB),&rwss,rws);	 
	}
      }
    }
  }
  // free
  a0=rfree(a0); a1=rfree(a1);
  value0=rfree(value0); value1=rfree(value1);
  rws=rvec_free(rws_size,rws);
  // done
  (*info)=ret;
  return e;
}

/** @} */

//EOF



