/**
 * @breif y=imag(x)
 */
void multi_imag(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  multi *x=NULL,*y=NULL;
  int info=-1;
  if(nlhs>1){ mexErrMsgIdAndTxt("MATLAB:multi_mex:maxlhs","Too many output arguments."); }
  if(!(IS_STRT(nrhs,prhs,N0))){ MATLAB_ERROR("multi_imag: The 1st-arg should be Struct."); }
  // allocate by clone
  x=multi_allocate_mxArray(prhs[N0]);
  y=multi_allocate('r',_M(x),_N(x),_L(x)); 
  // operation
       if(_T(x)=='r'){ rmat3_set_zeros(_M(y),_N(y),_L(y),_R(y),_LD1(y),_LD2(y)); }
  else if(_T(x)=='c'){ cmat3_imag(_M(y),_N(y),_L(y),_R(y),_LD1(y),_LD2(y),_C(x),_LD1(x),_LD2(x)); }
  else{ MATLAB_ERROR("multi_imag: Unkown type"); }
  // done
  plhs[0]=mxCreateStructMulti(y);
  x=multi_free(x);
  y=multi_free(y);
  return;
}

//EOF
