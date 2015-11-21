/**
 * @breif eq
 */
void multi_eq(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  multi *x=NULL,*y=NULL,*z=NULL;
  if(nlhs>1){ mexErrMsgIdAndTxt("MATLAB:multi_mex:maxlhs","Too many output arguments."); }
  if(!(IS_STRT(nrhs,prhs,2))){ MATLAB_ERROR("multi_eq: The arg2 should be Struct."); }
  if(!(IS_STRT(nrhs,prhs,3))){ MATLAB_ERROR("multi_eq: The arg3 should be Struct."); }
  // allocate by clone
  x=multi_allocate_mxArray(prhs[2]);
  y=multi_allocate_mxArray(prhs[3]);
  // operation
  if(_M(x)==_M(y) && _N(x)==_N(y) && _L(x)==_L(y)){  // In the case of same sizes
         if(_T(x)=='r' && _T(y)=='r'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); rmat3_eq      (_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_R(x),_LD1(x),_LD2(x),_R(y),_LD1(y),_LD2(y)); }
    else if(_T(x)=='r' && _T(y)=='c'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); cmat3_eq_rmat3(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(y),_LD1(y),_LD2(y),_R(x),_LD1(x),_LD2(x)); }
    else if(_T(x)=='c' && _T(y)=='r'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); cmat3_eq_rmat3(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(x),_LD1(x),_LD2(x),_R(y),_LD1(y),_LD2(y)); }
    else if(_T(x)=='c' && _T(y)=='c'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); cmat3_eq      (_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(x),_LD1(x),_LD2(x),_C(y),_LD1(y),_LD2(y)); }
    else{ MATLAB_ERROR("multi_eq: Unkown type"); }
  }else if(_M(x)==1 && _N(x)==1 && _L(x)==1){    // In the case of x is scalar    
         if(_T(x)=='r' && _T(y)=='r'){ z=multi_allocate('i',_M(y),_N(y),_L(y)); rmat3_eq_r(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_R(y),_LD1(y),_LD2(y),MAT3(_R(x),0,0,0,_LD1(x),_LD2(x))); }
    else if(_T(x)=='r' && _T(y)=='c'){ z=multi_allocate('i',_M(y),_N(y),_L(y)); cmat3_eq_r(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(y),_LD1(y),_LD2(y),MAT3(_R(x),0,0,0,_LD1(x),_LD2(x))); }
    else if(_T(x)=='c' && _T(y)=='r'){ z=multi_allocate('i',_M(y),_N(y),_L(y)); rmat3_eq_c(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_R(y),_LD1(y),_LD2(y),MAT3(_C(x),0,0,0,_LD1(x),_LD2(x))); }
    else if(_T(x)=='c' && _T(y)=='c'){ z=multi_allocate('i',_M(y),_N(y),_L(y)); cmat3_eq_c(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(y),_LD1(y),_LD2(y),MAT3(_C(x),0,0,0,_LD1(x),_LD2(x))); }
    else{ MATLAB_ERROR("multi_eq: Unkown type"); }
  }else if(_M(y)==1 && _N(y)==1 && _L(y)==1){    // In the case of x is scalar
         if(_T(x)=='r' && _T(y)=='r'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); rmat3_eq_r(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_R(x),_LD1(x),_LD2(x),MAT3(_R(y),0,0,0,_LD1(y),_LD2(y))); }
    else if(_T(x)=='r' && _T(y)=='c'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); rmat3_eq_c(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_R(x),_LD1(x),_LD2(x),MAT3(_C(y),0,0,0,_LD1(y),_LD2(y))); }
    else if(_T(x)=='c' && _T(y)=='r'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); cmat3_eq_r(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(x),_LD1(x),_LD2(x),MAT3(_R(y),0,0,0,_LD1(y),_LD2(y))); }
    else if(_T(x)=='c' && _T(y)=='c'){ z=multi_allocate('i',_M(x),_N(x),_L(x)); cmat3_eq_c(_M(z),_N(z),_L(z),_I(z),_LD1(z),_LD2(z),_C(x),_LD1(x),_LD2(x),MAT3(_C(y),0,0,0,_LD1(y),_LD2(y))); }
    else{ MATLAB_ERROR("multi_eq: Unkown type"); }
  }else{ MATLAB_ERROR("multi_eq: z=x+y: Dimensions of x and y are NOT same."); }
  // done
  plhs[0]=mxCreateStructMulti(z);
  
  x=multi_free(x);
  y=multi_free(y);
  z=multi_free(z);
  return;
}

//EOF