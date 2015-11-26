clear all
close all
set_default_prec(128);




% %% plus
A=multi([2 3; 4 5; -2 -3])
B=multi([2+i 3-i; 4*i 5-i; -2*i -3+i])
A+B
B+A
A+A
B+B
1+A
i+A
1+B
i+B
A+1
A+i
B+1
B+i

%% neg
A=multi([2 3; 4 5; -2 -3])
B=multi([2+i 3*i; 4 5; -2 -3])
-A
-B

%% copy
A=multi([2 3; 4 5; -2 -3])
B=multi([2+i 3*i; 4 5; -2 -3])
multi(A)
multi(B)

%% zeros
disp('=================== zeros ==================')
A=zeros(3,2,'multi')
size(A)
B=zeros([3,2,2],'multi')
s=size(B)
m=size(B,1)
n=size(B,2)
l=size(B,3)
[m,n,l]=size(B)


%% ones
A=ones(3,2,'multi')
B=ones([3,2,2],'multi')

%% rand
% A=rand(3,2,'multi')
% B=rand([3,2,2],'multi')

%% disp
disp(A);

%% double
double(A)

%% auto prec mode
set_default_prec(64);
auto_prec_enabled;
A=multi([sqrt(2) sqrt(3); sqrt(5) sqrt(7)])
B=multi([sqrt(8)/2^32 sqrt(10)/2^32; sqrt(11)/2^32 sqrt(12)/2^32])
C=A+B
A_prec=get_prec(A)
B_prec=get_prec(B)
C_prec=get_prec(C)
A_sign=get_sign(A)
B_sign=get_sign(B)
C_sign=get_sign(C)
A_exp=get_exp(A)
B_exp=get_exp(B)
C_exp=get_exp(C)
auto_prec_disabled;
set_default_prec(64);


%% transpose
disp('=================== transpose ==================')
A=rand(2,3,'multi')
A'
A=rand(2,3,'multi')+i
A'
A.'

%% eq
disp('=================== eq ==================')
A=multi([2 3; 4 5; -2 -3])
B=multi([2 -3; 4 -5; -2 3])
C=multi([2+i 3; 4 5-i; -2*i -3])
A==B
A==4
5==A
C==A
C==2+i
C==4
C==-2*i
3==C
5-i==C
-3==C

%% ne
disp('=================== ne ==================')
A=multi([2 3; 4 5; -2 -3])
B=multi([2 -3; 4 -5; -2 3])
C=multi([2 3+i; 4 5+i; -2 -3+i])
A~=B
A~=4
5~=A
C~=A
C~=5+i
C~=4
C~=-2
-2~=C
5+i~=C
-3+i~=C

% %% times
disp('=================== times ==================')
A=multi([1 -1; 2 -2; 3 -3])
B=multi([-2 -2; -2 -2; -2 -2])
C=multi([i -i; i -i; i -i])
A.*B
A.*(-2)
(-2).*A
A.*(-2*i)
(-2*i).*A
A.*C
C.*A
C.*2
2.*C
C.*(2*i)
(2*i).*C

% %% rdivide
disp('=================== rdivide ==================')
A=multi([1 -1; 2 -2; 3 -3])
B=multi([-2 -2; -2 -2; -2 -2])
C=multi([i -i; i -i; i -i])
A./B
A./(-2)
(-2)./A
A./(-2*i)
(-2*i)./A
A./C
C./A
C./2
2./C
C./(2*i)
(2*i)./C

%% power
disp('=================== power ==================')
A=multi([1 -1; 2 -2; 3 -3])
B=multi([-2 -2; -2 -2; -2 -2])
C=multi([1+i 1-i; 1+i 1-i; 1+i 1-i])
%A.^B
%A.^(-2)
%(-2).^A
A.^(-2*i)
%(-2*i).^A
A.^C
%C.^A
% C.^2
% 2.^C
% C.^(2*i)
% (2*i).^C

