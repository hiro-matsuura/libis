% s=get_s(A,opt)
function s=get_s(A,opt)
cmd='get_s';
if nargin==1
    if isa(A,'multi')
        s=multi(cmd,A.data).data;
    else
        s=multi(cmd,multi(A).data).data;
    end
else
    if isa(opt,'char')
        opt=strrep(opt,'g','Rg');
        opt=strrep(opt,'f','Rf');
        opt=strrep(opt,'e','Re');        
    end
    if isa(A,'multi')
        s=multi(cmd,A.data,opt).data;
    else
        s=multi(cmd,multi(A).data,opt).data;
    end
end