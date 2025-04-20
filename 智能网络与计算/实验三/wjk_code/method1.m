global a;
T = 10;
a = rand(T,1);
cvx_begin
    variable p(T,1);
    maximize( sum( log(1 + p .* a) / log(2) ) );
    subject to
        p >= 0;
        sum(p) == 1;
cvx_end
