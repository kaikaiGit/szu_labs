global a;
global lambda;
% 参数设置
T = 10; % 时隙数
P_max = 1; % 最大功率
% 初始化变量
lambda_min = 0;
lambda_max = 2;
tol = 1e-6; % 容差
p2 = zeros(T, 1); % 初始化功率分配
% 二分法实现注水算法
while lambda_max - lambda_min > tol
    lambda = (lambda_min + lambda_max) / 2;
    p2 = (1/(log(2) * lambda) - 1 ./ a);
    p2(p2 < 0) = 0; % 保证功率非负
    total_power = sum(p2);
    if total_power > P_max
        lambda_min = lambda;
    else
        lambda_max = lambda;
    end
end
