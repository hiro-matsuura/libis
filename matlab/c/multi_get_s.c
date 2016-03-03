/**
 * @breif chare型のセルへのキャスト y=get_s(x)
 */
void multi_get_s(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *p=NULL,*q=NULL,*fmt=NULL,buf[1048576];
  mwSize ndim=3,dims[]={1,1,1};
  int i,j,k,t,c;
  multi *x=NULL;
  mxArray *s=NULL;
  if(nlhs>1){ mexErrMsgIdAndTxt("MATLAB:multi_mex:maxlhs","Too many output arguments."); }
  if(!(IS_STRT(nrhs,prhs,N0))){ MATLAB_ERROR("multi_get_s: The 1st-arg should be Struct."); }
  if(nrhs-N0>=2){
    if(!(IS_CHAR(nrhs,prhs,N0+1))){ MATLAB_ERROR("multi_get_s: The 2nd-arg should be Char."); }
    fmt=mxArrayToString(prhs[N0+1]);
    for(p=fmt, c=0; (*p)!='\0'; p++){ if((*p)=='g' || (*p)=='f' || (*p)=='e'){ c++; } }
    if(c!=1){ MATLAB_ERROR("multi_get_s: The 2nd-arg should contain one of %%g, %%f and %%e."); }
    strcpy(buf,fmt);
    for(q=fmt, p=buf; (*p)!='\0' && (*p)!='g' && (*p)!='f' && (*p)!='e'; p++, q++){}
    (*q)='R'; q++;
    (*q)=(*p); q++; p++;
    strcpy(q,p);
    //mexPrintf("fmt=%s\n",fmt);
  }
  // get multi
  x=multi_allocate_mxArray(prhs[N0]);
  // get size
  dims[0]=_M(x);  dims[1]=_N(x);  dims[2]=_L(x);
  if(dims[2]==1){ ndim=2; }
  // allocate
  plhs[0]=mxCreateCellArray(ndim,dims);
  // convert
  for(k=0; k<_L(x); k++){
    for(j=0; j<_N(x); j++){
      for(i=0; i<_M(x); i++){
	t=i+j*_M(x)+k*_M(x)*_N(x);
	if(_T(x)=='r'){
	  if(fmt==NULL){
	    if(j==0){ mpfr_sprintf(buf,"%.5Rg", MAT3(_R(x),i,j,k,_LD1(x),_LD2(x))); }
	    else    { mpfr_sprintf(buf,"%11.5Rg",MAT3(_R(x),i,j,k,_LD1(x),_LD2(x))); }
	  }
	  else         { mpfr_sprintf(buf,fmt,MAT3(_R(x),i,j,k,_LD1(x),_LD2(x))); }
	  s=mxCreateString(buf);
	}else if(_T(x)=='c'){
	  if(fmt==NULL){ mpfr_sprintf(buf,"%6.5Rg    ",C_R(MAT3(_C(x),i,j,k,_LD1(x),_LD2(x)))); }
	  else         { mpfr_sprintf(buf,fmt,         C_R(MAT3(_C(x),i,j,k,_LD1(x),_LD2(x)))); }
	  s=mxCreateString(buf);		 
	}else{
	  MATLAB_ERROR("multi_get_s: Unknow type.");
	}
	mxSetCell(plhs[0],t,s);
      }
    }
  }
  if(fmt!=NULL){ mxFree(fmt); }
  x=multi_free(x);
}

//EOF
