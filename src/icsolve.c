#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"is_macros.h"
#include"is_icmulti.h"
#include"is_icvec.h"
#include"is_cmat.h"
#include"is_icmat.h"
#include"is_icsolve.h"
#include"is_cmulti.h"
#include"is_ivec.h"
#include"is_cvec.h"
#include"is_irmulti.h"
/**
 @file  icsolve.c
 @brief 多倍長精度実数型cmultiの機械区間演算による線形方程式A*X=Bの解法に関する関数の定義.
 @details icmulti型の関数に関する定義は@link icmulti.c@endlinkを参照のこと.
          icmulti型のベクトルの関数に関する定義は@link icvec.c@endlinkを参照のこと.
          icmulti型の行列の関数に関する定義は@link icmat.c@endlinkを参照のこと.
 */


#define MA0(I,J) (MAT(A0,(I),(J),LDA))
#define MA1(I,J) (MAT(A1,(I),(J),LDA))
#define MB0(I,J) (MAT(B0,(I),(J),LDB))
#define MB1(I,J) (MAT(B1,(I),(J),LDB))
#define MC0(I,J) (MAT(C0,(I),(J),LDC))
#define MC1(I,J) (MAT(C1,(I),(J),LDC))
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @name 線形方程式 A*X=B の解法に関する関数 */
/** @{ */

/**
 @brief 線形方程式A*X=Bの解法.
 @param[in]  B サイズ(n,NRHS)の行列B.
 @param[out] B サイズ(n,NRHS)の解の行列X.
 @param[in]  A サイズnの正方行列で係数行列A.
 */
int icsolve(int n, int NRHS, cmulti **B0, cmulti **B1, int LDB, cmulti **A0, cmulti **A1, int LDA, int *info)
{
  int prec0,prec1,prec,e=0;
  cmulti **C0=NULL, **C1=NULL;
  prec0=cmat_get_prec_max(n,NRHS,B0,LDB);
  prec1=cmat_get_prec_max(n,NRHS,B1,LDB);
  prec=MAX2(prec0,prec1);
  C0=cmat_allocate_prec(n,n,prec);
  C1=cmat_allocate_prec(n,n,prec);
  e+=icmat_copy(n,n,C0,n,C1,n,A0,LDA,A1,LDA);
  //e+=icsolve_lu(n,NRHS,B0,B1,LDB,C0,C1,n,info);
  e+=icsolve_gauss_sweeper(n,NRHS,B0,B1,LDB,C0,C1,n,info);
 
  C0=cmat_free(n,n,C0);
  C1=cmat_free(n,n,C1);
  return e;
}



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
int icsolve_gauss_sweeper(int n, int NRHS, cmulti **B0, cmulti **B1, int LDB, cmulti **A0, cmulti **A1, int LDA, int *info)
{
  int p0,p1,p2,p3,prec,ret=0,i,j,k,l,e=0;
  cmulti *c0=NULL,*c1=NULL;
  rmulti *a0=NULL,*a1=NULL,*value0=NULL,*value1=NULL;
  rmulti **rws=NULL;int rws_size,rwss;
  cmulti **cws=NULL;int cws_size,cwss;
  // allocate
  p0=cmat_get_prec_max(n,NRHS,B0,LDB);
  p1=cmat_get_prec_max(n,NRHS,B1,LDB);
  p2=cmat_get_prec_max(n,n,A0,LDA);
  p3=cmat_get_prec_max(n,n,A1,LDA);
  p0=MAX2(p0,p1);p2=MAX2(p2,p3);
  prec=MAX2(p0,p2);
  c0=callocate_prec(prec); c1=callocate_prec(prec);
  a0=rallocate_prec(prec); a1=rallocate_prec(prec);
  value0=rallocate_prec(prec); value1=rallocate_prec(prec);
  rws_size=8; rwss=rws_size;
  cws_size=4; cwss=cws_size;  //ワークスペース
  rws=rvec_allocate_prec(rws_size,prec);
  cws=cvec_allocate_prec(cws_size,prec);
   // 上三角化
  for(k=0; k<n; k++){
    // ピボット選択
    e+=icabs_ws(value0,value1,MA0(k,k),MA1(k,k),&cwss,cws);
    for(l=k,j=k+1; j<n; j++){
      e+=icabs_ws(a0,a1,MA0(j,k),MA1(j,k),&cwss,cws);
      if(rgt(a0,value0)) { l=j; e+=ircopy(value0,value1,a0,a1); } // value=a
    }
    if(ris_zero(value0)) { ret=l+1; break; } // error
    if(l!=k){
      cmat_swap_rows(n,NRHS,B0,LDB,k,l);          //swap b0(k) <-> b0(l)
      cmat_swap_rows(n,NRHS,B1,LDB,k,l);          //swap b1(k) <-> b1(l)
      cmat_swap_rows(n,n,A0,LDA,k,l);   
      cmat_swap_rows(n,n,A1,LDA,k,l);           //swap A(k,:) <-> A(l,:)
    }
    //軸要素を1にする
    e+=icinv(c0,c1,MA0(k,k),MA1(k,k));
    for(j=k; j<n; j++) {
      e+=icmul_ws(MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),c0,c1,MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),&rwss,rws,&cwss,cws);
    }
    for(j=0; j<NRHS; j++) {
      e+=icmul_ws(MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),c0,c1,MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),&rwss,rws,&cwss,cws);
      }
    //軸要素以外が 0 になるように他の列から軸要素の列を引く
    for(i=k+1; i<n; i++){
      if(i!=k){
	e+=iccopy(c0,c1,MA0(i,k),MA1(i,k));
	for(j=k; j<n; j++){
	  e+=icsub_mul_ws(MAT(A0,i,j,LDA),MAT(A1,i,j,LDA),c0,c1,MAT(A0,k,j,LDA),MAT(A1,k,j,LDA),&rwss,rws,&cwss,cws);
        }	
	for(j=0; j<NRHS; j++){
	  e+=icsub_mul_ws(MAT(B0,i,j,LDB),MAT(B1,i,j,LDB),c0,c1,MAT(B0,k,j,LDB),MAT(B1,k,j,LDB),&rwss,rws,&cwss,cws);
	}
      }
    }
  }  
  //後退代入 x=inv(U)*b
  if(ret==0){
    for(k=0; k<NRHS; k++){
      for(i=n-1; i>=0; i--){
	for(j=n-1; j>=i+1; j--){
	  e+=icsub_mul_ws(MAT(B0,i,k,LDB),MAT(B1,i,k,LDB),MAT(A0,i,j,LDA),MAT(A1,i,j,LDA),MAT(B0,j,k,LDB),MAT(B1,j,k,LDB),&rwss,rws,&cwss,cws);
	}
      }
    }
  }
  // free
  c0=cfree(c0); c1=cfree(c1);
  a0=rfree(a0); a1=rfree(a1);
  value0=rfree(value0); value1=rfree(value1);
  rws=rvec_free(rws_size,rws);
  cws=cvec_free(cws_size,cws);
  // done
  (*info)=ret;
  return e;
}

/** @} */

//EOF
