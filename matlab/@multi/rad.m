% y=rad(x)
function y=rad(x)
cmd='rad';
if isa(x,'multi')
    y=multi(cmd,x.data);
else
    y=multi(cmd,multi(x).data);
end