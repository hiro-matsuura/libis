%% z=x.\y
function z=ldivide(x,y)
cmd='ldivide';
if isa(x,'multi') && isa(y,'multi')
    z=multi(cmd,x.data,y.data);
elseif isa(x,'multi')
    z=multi(cmd,x.data,multi(y).data);
elseif isa(y,'multi')
    z=multi(cmd,multi(x).data,y.data);
else
    z=multi(cmd,multi(x).data,multi(y).data);
end