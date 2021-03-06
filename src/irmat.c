#include"is_rmulti.h"
#include"is_rmat.h"
#include"is_irmulti.h"
#include"is_irvec.h"
#include"is_func.h"
//追加済み
#include"is_irsolve.h"
#include"is_irmat.h"
//

/**
 @file  irmat.c
 @brief 多倍長精度実数型rmultiの機械区間演算の行列に関する関数の定義.
 @details スカラーに関しては@link irmulti.c@endlinkを参照のこと.
          ベクトルに関しては@link irvec.c@endlinkを参照のこと.
          行列に関しては@link irmat.c@endlinkを参照のこと.
 */

/** @name 基本操作 */
/** @{ */

/**
 @brief 区間rmulti型の行列の値を倍精度実数から設定 [B0,B1]=A.
*/
int irmat_set_d(int m, int n, rmulti **B0, rmulti **B1, int LDB, const double *A, int LDA)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=irset_d(MAT(B0,i,j,LDB),MAT(B1,i,j,LDB),MAT(A,i,j,LDA));
    }
  }
  return e;
}

/**
 @brief コピー [B0,B1]=[A0,A1]
*/
int irmat_copy(int m, int n, rmulti **B0, int LDB0, rmulti **B1, int LDB1, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=ircopy(MAT(B0,i,j,LDB0),MAT(B1,i,j,LDB1),MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
  }
  return e;
}

/**
 @brief 転置のコピー [B0,B1]=[A0,A1]'
*/
int irmat_copy_t(int m, int n, rmulti **B0, int LDB0, rmulti **B1, int LDB1, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=ircopy(MAT(B0,j,i,LDB0),MAT(B1,j,i,LDB1),MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
  }
  return e;
}

/**
 @brief 表示
 */
void irmat_print(int m, int n, rmulti **A0, int LDA0, rmulti **A1, int LDA1, const char *name, const char *f, int digits)
{
  int i,j,k;
  char format[128];
  if(STR_EQ(f,"f") || STR_EQ(f,"F")){ k=3; }
  else if((strcmp(f,"e")==0) || (strcmp(f,"E")==0)){ k=7; }
  else{ k=3; }
  sprintf(format,"[%%%d.%dR%s, %%%d.%dR%s] ",digits+k,digits,f,digits+k,digits,f);
  if(A0==NULL || A1==NULL){
    if(name!=NULL){ printf("%s=NULL\n",name); }
    else          { printf("NULL\n"); }
    return;
  }
  if(name!=NULL){ printf("%s\n",name); }
  if(A0==NULL || A1==NULL) return;
  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      mpfr_printf(format,MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
    printf("\n");
  }
}

/**
 @brief 区間の中心 [m-r,m+r]=[A0,A1]
*/
int irmat_mid(int m, int n, rmulti **mid, int LDmid, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=irmid(MAT(mid,i,j,LDmid),MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
  }
  return e;
}

/**
 @brief 区間の半径 [m-r,m+r]=[A0,A1]
*/
int irmat_rad(int m, int n, rmulti **rad, int LDrad, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=irrad(MAT(rad,i,j,LDrad),MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
  }
  return e;
}

/**
 @brief 区間の中心と半径 [m-r,m+r]=[A0,A1]
*/
int irmat_mr(int m, int n, rmulti **mid, int LDmid, rmulti **rad, int LDrad, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=irmr(MAT(mid,i,j,LDmid),MAT(rad,i,j,LDrad),MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1));
    }
  }
  return e;
}

/**
 @brief 区間の中心 Ac=(A1+A0)/2 と半径 Ar=A1-A0
*/
int irmat_center_radius(int m, int n, rmulti **Ac, int LDAc, rmulti **Ar, int LDAr, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int e=0;
  mpfr_rnd_t mode;
  mode=get_round_mode();
  set_round_mode(MPFR_RNDU);                // up
  e+=rmat_sub(m,n,Ac,LDAc,A1,LDA1,A0,LDA0); // Ac=A1-A0
  e+=rmat_mul_d(m,n,Ac,LDAc,Ac,LDAc,0.5);   // Ac=(A1-A0)/2
  e+=rmat_add(m,n,Ac,LDAc,Ac,LDAc,A0,LDA0); // Ac=(A1-A0)/2+A0
  e+=rmat_sub(m,n,Ar,LDAr,Ac,LDAc,A0,LDA0); // Ar=Ac-A0
  set_round_mode(mode);                     // back
  return e;
}
//追加

/**
 @brief [A0,A1]=NaN(m,n)
*/
int irmat_set_nan(int m, int n, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  rmat_set_nan(m,n,A0,LDA0);
  rmat_set_nan(m,n,A1,LDA1);
  return 0;
}

//ここまで

/**
 @brief [A0,A1]=ones(m,n)*a
*/
int irmat_set_all_d(int m, int n, rmulti **A0, int LDA0, rmulti **A1, int LDA1, double a)
{
  int i,j,e=0;
  for(j=0; j<n; j++){
    for(i=0; i<m; i++){
      e+=irset_d(MAT(A0,i,j,LDA0),MAT(A1,i,j,LDA1),a);
    }
  }
  return e;
}

/**
 @brief [A0,A1]=[zeros(m,n),zeros(m,n)]
*/
int irmat_set_zeros(int m, int n, rmulti **A0, int LDA0, rmulti **A1, int LDA1)
{
  int e=0;
  e+=irmat_set_all_d(m,n,A0,LDA0,A1,LDA1,0);
  return e;
}

//新規作成

/**
 @brief rmulti型の行列の値を単位行列に設定.
*/
int irmat_set_eye(int m, int n, rmulti **A0, rmulti **A1, int LDA)
{
  int e=0;
  e+=rmat_set_eye(m,n,A0,LDA);
  e+=rmat_set_eye(m,n,A1,LDA);
  return e;
}

//ここまで
/** @} */
/** @name 四則演算 */
/** @{ */

/**
 @brief 積 [C0,C1]=[A0,A1]*[B0,B1]
*/

/*
int irmat_prod(int l, int m, int n, rmulti **C0, int LDC0, rmulti **C1, int LDC1, rmulti **A0, int LDA0, rmulti **A1, int LDA1, rmulti **B0, int LDB0, rmulti **B1, int LDB1)
{
  int p0,p1,prec,i,j,k,e=0;
  rmulti **Z0=NULL,**Z1=NULL;
  p0=rmat_get_prec_max(l,n,C0,LDC0); p1=rmat_get_prec_max(l,n,C1,LDC1); prec=MAX2(p0,p1);
  Z0=rmat_allocate_prec(l,n,prec); Z1=rmat_allocate_prec(l,n,prec);
  for(i=0; i<l; i++){
    for(j=0; j<n; j++){
      e+=irset_d(MAT(Z0,i,j,l),MAT(Z1,i,j,l),0);
      for(k=0; k<m; k++){
	e+=iradd_mul(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(A0,i,k,LDA0),MAT(A1,i,k,LDA1),MAT(B0,k,j,LDB0),MAT(B1,k,j,LDB1));
      }
    }
  }
  e+=irmat_copy(l,n,C0,LDC0,C1,LDC1,Z0,l,Z1,l);
  Z0=rmat_free(l,n,Z0);
  Z1=rmat_free(l,n,Z1);
  return e;
}

*/

//追加

/**
 @brief 積 [C0,C1]=[A0,A1]*[B0,B1]
*/

 
int irmat_prod(int l, int m, int n, rmulti **C0, int LDC0, rmulti **C1, int LDC1, rmulti **A0, int LDA0, rmulti **A1, int LDA1, rmulti **B0, int LDB0, rmulti **B1, int LDB1)
{
  int p0,p1,prec,i,j,k,rws_size,rwss,e=0;
  rmulti **Z0=NULL,**Z1=NULL,**rws=NULL;
  p0=rmat_get_prec_max(l,n,C0,LDC0); p1=rmat_get_prec_max(l,n,C1,LDC1); prec=MAX2(p0,p1);
  Z0=rmat_allocate_prec(l,n,prec); Z1=rmat_allocate_prec(l,n,prec);
  rws_size=6; rwss=rws_size;  //ワークスペース
  rws=rvec_allocate_prec(rws_size,prec);
  for(i=0; i<l; i++){
    for(j=0; j<n; j++){
      e+=irset_d(MAT(Z0,i,j,l),MAT(Z1,i,j,l),0);
      for(k=0; k<m; k++){
	e+=iradd_mul_ws(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(A0,i,k,LDA0),MAT(A1,i,k,LDA1),MAT(B0,k,j,LDB0),MAT(B1,k,j,LDB1),&rwss,rws);
      }
    }
  }
  e+=irmat_copy(l,n,C0,LDC0,C1,LDC1,Z0,l,Z1,l);
  Z0=rmat_free(l,n,Z0);
  Z1=rmat_free(l,n,Z1);
  rws=rvec_free(rws_size,rws);
  return e;
}


//ここまで

/**
 @brief 積の加算 [C0,C1]=[C0,C1]+[A0,A1]*[B0,B1]
*/
int irmat_add_prod(int l, int m, int n, rmulti **C0, int LDC0, rmulti **C1, int LDC1, rmulti **A0, int LDA0, rmulti **A1, int LDA1, rmulti **B0, int LDB0, rmulti **B1, int LDB1)
{
  int p0,p1,prec,i,j,k,e=0;
  rmulti **Z0=NULL,**Z1=NULL;
  p0=rmat_get_prec_max(l,n,C0,LDC0); p1=rmat_get_prec_max(l,n,C1,LDC1); prec=MAX2(p0,p1);
  Z0=rmat_allocate_prec(l,n,prec); Z1=rmat_allocate_prec(l,n,prec);
  for(i=0; i<l; i++){
    for(j=0; j<n; j++){
      e+=ircopy(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(C0,i,j,LDC0),MAT(C1,i,j,LDC1));
      for(k=0; k<m; k++){
	e+=iradd_mul(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(A0,i,k,LDA0),MAT(A1,i,k,LDA1),MAT(B0,k,j,LDB0),MAT(B1,k,j,LDB1));
      }
    }
  }
  e+=irmat_copy(l,n,C0,LDC0,C1,LDC1,Z0,l,Z1,l);
  Z0=rmat_free(l,n,Z0); Z1=rmat_free(l,n,Z1);
  return e;
}

/**
 @brief 積の減算 [C0,C1]=[C0,C1]-[A0,A1]*[B0,B1]
*/
int irmat_sub_prod(int l, int m, int n, rmulti **C0, int LDC0, rmulti **C1, int LDC1, rmulti **A0, int LDA0, rmulti **A1, int LDA1, rmulti **B0, int LDB0, rmulti **B1, int LDB1)
{
  int p0,p1,prec,i,j,k,e=0;
  rmulti **Z0=NULL,**Z1=NULL;
  p0=rmat_get_prec_max(l,n,C0,LDC0); p1=rmat_get_prec_max(l,n,C1,LDC1); prec=MAX2(p0,p1);
  Z0=rmat_allocate_prec(l,n,prec); Z1=rmat_allocate_prec(l,n,prec);
  for(i=0; i<l; i++){
    for(j=0; j<n; j++){
      e+=ircopy(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(C0,i,j,LDC0),MAT(C1,i,j,LDC1));
      for(k=0; k<m; k++){
	e+=irsub_mul(MAT(Z0,i,j,l),MAT(Z1,i,j,l),MAT(A0,i,k,LDA0),MAT(A1,i,k,LDA1),MAT(B0,k,j,LDB0),MAT(B1,k,j,LDB1));
      }
    }
  }
  e+=irmat_copy(l,n,C0,LDC0,C1,LDC1,Z0,l,Z1,l);
  Z0=rmat_free(l,n,Z0); Z1=rmat_free(l,n,Z1);
  return e;
}

/** @} */

////////////////////////////////////////////////////////////////////////
//新規作成

/** @name rmulti型の行列の数学関数に関する関数 */
/** @{ */
/**
 @brief irmulti型の逆行列 [B0,B1]=inv(A0,A1)
 @param[in]  A 初期化済みのサイズが(n,n)の行列.
 @param[out] B 初期化済みのサイズが(n,n)の行列.
*/
int irmat_inv(int n, rmulti **B0, rmulti **B1, int LDB, rmulti **A0, rmulti **A1, int LDA)
{
  int info,e=0;
  e+=irmat_set_eye(n,n,B0,B1,LDB);
  e+=irsolve(n,n,B0,B1,LDB,A0,A1,LDA,&info);
  return e;
}

/**
 @brief irmulti型の列ごとの和 B=sum(A)
*/
int irvec_sum_irmat(int m, int n, rmulti **B0, rmulti **B1, rmulti **A0, rmulti **A1, int LDA)
{
  int j,e=0;
  for(j=0; j<n; j++){ e+=irvec_sum(B0[j],B1[j],m,&COL(A0,j,LDA),&COL(A1,j,LDA)); }
  return e;
}

/**
 @brief irmulti型の列ごとの最大値 B=max(A)
*/
int irvec_max_irmat(int m, int n, rmulti **B0, rmulti **B1, rmulti **A0, rmulti **A1, int LDA)
{
  int j,e=0;
  for(j=0; j<n; j++){ e+=irvec_max(B0[j],B1[j],m,&COL(A0,j,LDA),&COL(A1,j,LDA)); }
  return e;
}

/**
 @brief irmulti型の列ごとの最大値 B=max_u(A)
*/
int irvec_umax_irmat(int m, int n, rmulti **B0, rmulti **B1, rmulti **A0, rmulti **A1, int LDA)
{
  int j,e=0;
  for(j=0; j<n; j++){ e+=irvec_umax(B0[j],B1[j],m,&COL(A0,j,LDA),&COL(A1,j,LDA)); }
  return e;
}


/**
 @brief irmulti型の列ごとの最小値 B=min(A)
*/
int irvec_min_irmat(int m, int n, rmulti **B0, rmulti **B1, rmulti **A0, rmulti **A1, int LDA)
{
  int j,e=0;
  for(j=0; j<n; j++){ e+=irvec_min(B0[j],B1[j],m,&COL(A0,j,LDA),&COL(A1,j,LDA)); }
  return e;
}

//ここまで
/** @} */
//////////////////////////////////////////////////////////////////////////

/** @name 写像 */
/** @{ */

/**
 @brief 行列写像 [A0,A1]=F([x0,x1])
*/
int irmat_func_list2(int m, int n, rmulti **A0, rmulti **A1, int LDA, func_t *f, int l, rmulti **x0, rmulti **x1)
{
  int i,j,e=0;
  for(i=0; i<m; i++){      
    for(j=0; j<n; j++){
      if(func_is_list(f) && i<func_asize(f) && func_is_list(func_aget(f,i)) && j<func_asize(func_aget(f,i))){
	e+=irvec_func(MAT(A0,i,j,LDA),MAT(A1,i,j,LDA),func_aget(func_aget(f,i),j),l,x0,x1);
      }else{ rset_nan(MAT(A0,i,j,LDA)); rset_nan(MAT(A1,i,j,LDA)); }
    }
  }
  return e;
}

/** @} */

//EOF
