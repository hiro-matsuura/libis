clear all
close all

% set_default_prec(512);
% N=500;
% %A=2*rand(3,3)-1;  
% A=2*rand(N,N)-1%+1i*(2*rand(N,N)-1); 
% %a=2*rand(1,4)-1%+1i*(2*rand(1,4)-1); 
% %A=15+1i*15;
% %a=15+1i*15; 
% %A=floor(A*10);
% %B=2*rand(3,3)-1;
% %B=2*rand(4,4)%-1i*(2*rand(4,4)-1);
% b=2*rand(N,N)-1%+1i*(2*rand(N,N)-1);
% %b=eye(N);
% %B=rand();
% %B=rand()+i*rand();
% %B=floor(B*10);
% %A*B
% %a*b
% 
% A=imulti(A)
% %B=imulti(B)
% %a=imulti(a)
% b=imulti(b)
%c=a+b
%C=A*B
%D=A.*B
%C=A+a
%c=a+b
%C=A+B;
% C=C+B;C=C+B;C=C+B;C=C+B;
% C=C+A;C=C+A;C=C+A;C=C+A;
%C=A\b;
%D=A*C-b;
%E=A*C;

%disp('A=');disp(num2str(A,'%+.7e'))
%disp('b=');disp(num2str(b,'%+.7e'))
%disp('C=');disp(num2str(C,'%+.7e'))
%disp('D=');disp(num2str(D,'%+.7e'))
%disp('E=');disp(num2str(E,'%+.7e'))
% 
% mid(A)
% mid(B)
% mid(C)
% % 
% rad(A)
% rad(B)
% rad(C)
% (up(C)-down(C))/2

%get_prec(B)  %A��prec

%clear all
N=10;
%A=2*rand(N,N,N)-1;
A=2*rand(N,N,N)-1+1i*(2*rand(N,N,N)-1);
%b=2*rand(N,1)-1;
%b=2*rand(N,1)-1+1i*(2*rand(N,1)-1);

set_default_prec(53);
b=A;
A=imulti(A);
% b=multi(b);
% tic
% x=A\b;
% toc
% B=A*x-b;

x=sum(A);
B=sum(b);
disp('A=');disp(num2str(A,'%+.7e'))
disp('x=');disp(num2str(x,'%+.7e'))
disp('B=');disp(num2str(B,'%+.7e'))

