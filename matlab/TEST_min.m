clear all
clc

a=[1 2 3;4 5 6;7 8 9];
a(:,:,2)=[10 20 30;40 50 60;70 80 90+i];
A=multi(a)

disp('=================');

min(A)
min(min(A))
min(min(min(A)))


angle([-1-i,1-i,1+i,-1+i])%複素数で絶対値が等しい場合は、位相角の小さい順(これの小さい順)
min([-1-i,1-i,1+i,-1+i])
min(multi([-1-i,1-i,1+i,-1+i]))
min(multi([-1-i,1-i,1+i]))
min(multi([-1-i,1-i]))
