/**
 * @breif y=min(x)
 */
//区間の場合 [y0,y1]=[min(x0),min(x1)]
void multi_min(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  multi *x=NULL,*y=NULL;
  if(nlhs>1){ mexErrMsgIdAndTxt("MATLAB:multi_mex:maxlhs","Too many output arguments."); }
  if(!(IS_STRT(nrhs,prhs,N0))){ MATLAB_ERROR("multi_min: The 1st-arg should be Struct."); }
  // allocate by clone
  x=multi_allocate_mxArray(prhs[N0]);
  // operation
  ccmp_set_abs_arg();
  if((_M(x)==1 && _L(x)==1) || (_N(x)==1 && _L(x)==1)){
         if(_T(x)=='r'){ y=multi_allocate('r',1,1,1); rvec_min(_R(y)[0],_M(x)*_N(x)*_L(x),_R(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,1,1); cvec_min(_C(y)[0],_M(x)*_N(x)*_L(x),_C(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,1,1); irvec_min(_R0(y)[0],_R1(y)[0],_M(x)*_N(x)*_L(x),_R0(x),_R1(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,1,1); icvec_min(_C0(y)[0],_C1(y)[0],_M(x)*_N(x)*_L(x),_C0(x),_C1(x)); }
  }else if(_L(x)==1){
         if(_T(x)=='r'){ y=multi_allocate('r',1,_N(x),1); rvec_min_rmat(_M(x),_N(x),_R(y),_R(x),_LD1(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,_N(x),1); cvec_min_cmat(_M(x),_N(x),_C(y),_C(x),_LD1(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,_N(x),1); irvec_min_irmat(_M(x),_N(x),_R0(y),_R1(y),_R0(x),_R1(x),_LD1(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,_N(x),1); icvec_min_icmat(_M(x),_N(x),_C0(y),_C1(y),_C0(x),_C1(x),_LD1(x)); }
  }else if(_L(x)>1 && _M(x)==1 && _N(x)==1){
         if(_T(x)=='r'){ y=multi_allocate('r',1,1,1); rvec_min(_R(y)[0],_M(x)*_N(x)*_L(x),_R(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,1,1); cvec_min(_C(y)[0],_M(x)*_N(x)*_L(x),_C(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,1,1); irvec_min(_R0(y)[0],_R1(y)[0],_M(x)*_N(x)*_L(x),_R0(x),_R1(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,1,1); icvec_min(_C0(y)[0],_C1(y)[0],_M(x)*_N(x)*_L(x),_C0(x),_C1(x)); }
   }else if(_L(x)>1 && _M(x)>1 && _N(x)==1){
         if(_T(x)=='r'){ y=multi_allocate('r',1,1,_L(x)); rvec_min_rmat(_M(x),_L(x),_R(y),_R(x),_M(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,1,_L(x)); cvec_min_cmat(_M(x),_L(x),_C(y),_C(x),_M(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,1,_L(x)); irvec_min_irmat(_M(x),_L(x),_R0(y),_R1(y),_R0(x),_R1(x),_M(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,1,_L(x)); icvec_min_icmat(_M(x),_L(x),_C0(y),_C1(y),_C0(x),_C1(x),_M(x)); }
  }else if(_L(x)>1 && _M(x)==1 && _N(x)>1){
         if(_T(x)=='r'){ y=multi_allocate('r',1,1,_L(x)); rvec_min_rmat(_N(x),_L(x),_R(y),_R(x),_N(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,1,_L(x)); cvec_min_cmat(_N(x),_L(x),_C(y),_C(x),_N(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,1,_L(x)); irvec_min_irmat(_N(x),_L(x),_R0(y),_R1(y),_R0(x),_R1(x),_N(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,1,_L(x)); icvec_min_icmat(_N(x),_L(x),_C0(y),_C1(y),_C0(x),_C1(x),_N(x)); }
  }else if(_L(x)>1 && _M(x)>1 && _N(x)>1){
         if(_T(x)=='r'){ y=multi_allocate('r',1,_N(x),_L(x)); rmat3_min(_M(x),_N(x),_L(x),_R(y),_LD1(y),_LD2(y),_R(x),_LD1(x),_LD2(x)); }
    else if(_T(x)=='c'){ y=multi_allocate('c',1,_N(x),_L(x)); cmat3_min(_M(x),_N(x),_L(x),_C(y),_LD1(y),_LD2(y),_C(x),_LD1(x),_LD2(x)); }
    else if(_T(x)=='R'){ y=multi_allocate('R',1,_N(x),_L(x)); irmat3_min(_M(x),_N(x),_L(x),_R0(y),_R1(y),_LD1(y),_LD2(y),_R0(x),_R1(x),_LD1(x),_LD2(x)); }
    else if(_T(x)=='C'){ y=multi_allocate('C',1,_N(x),_L(x)); icmat3_min(_M(x),_N(x),_L(x),_C0(y),_C1(y),_LD1(y),_LD2(y),_C0(x),_C1(x),_LD1(x),_LD2(x)); }
  }else{ MATLAB_ERROR("multi_min: error"); }
  // done
  plhs[0]=mxCreateStructMulti(y);
  x=multi_free(x);
  y=multi_free(y);
  return;
}

//EOF




//EOF
