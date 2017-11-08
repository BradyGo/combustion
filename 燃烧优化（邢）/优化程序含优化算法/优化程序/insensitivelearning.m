 function [w] = insensitivelearning(X,Y,nAugX,r)
%replace LS with epsin-insensitive learning Y=X*c
%epsin-LSSI

epsin = 0.01;
ro = 0.98;
k2 = 1e-4;   %基本上可固定了
%[N t] = size(X);
[N n] = size(X);
t = n/nAugX;       %nAugX是算例中输入变量的维数加1，nAugX-1相当于论文中的t（输入维数） 此处的t是叶节点的个数即规则条数
D = diag(ones(2*N,1));
%b = abs(rand(2*N,1));
b = 1e-6*ones(2*N,1);   %暂时先固定
XX = [X' -X'];  %t*2N维
k  = 1;
while (k==1) || (norm(b-b0)>k2 &(k<=20)) 
   ye  = [Y'-epsin*ones(1,N) -Y'-epsin*ones(1,N)]';
%   w_k = ([X'-X']*D_k*[X -X]'+(r/2)*diag([ones(1,t-1) 0]))\([X' -X']*(y_e+b_k));
%   w = inv(XX*D*XX'+(r/2)*diag([ones(1,t-1) 0]))*XX*D*3ye+b); 
    w = inv(XX*D*XX'+(r/2)*diag(repmat([ones(1,nAugX-1) 0], 1, t)))*XX*D*(ye+b);
   ee = XX'*w-ye -b;
   for i=1:(2*N)
      E(i) = 1/abs(ee(i));
   end
   D = diag(E);
   b0 = b;
   b = b+ro*(ee+abs(ee)); 
   k = k+1;  
end    


