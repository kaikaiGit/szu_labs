global lambda;
z = [];
n = 10;
v = 1 / (log(2) * lambda);
for i = 0:n-1
    y = 1/a(i+1);
    z = [z;i y;i+1 y];
end
figure(1);
plot(z(:,1),z(:,2));
line([0 n],[v v],'linestyle',':');
xlabel('i');
legend('1/a','注水线');
set(gca,'xtick',[],'ytick',[]);
text(-1.2,v,num2str(v));