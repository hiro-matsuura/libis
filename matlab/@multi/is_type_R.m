function tf=is_type_R(A)
if isa(A,'multi')
tf=prod(isfield(A.data,{'R0_digits','R0_exp','R0_prec','R0_sign','R1_digits','R1_exp','R1_prec','R1_sign'}));
else
    tf=0; % 入力がmulti型以外ならそもそも呼ばれない
end