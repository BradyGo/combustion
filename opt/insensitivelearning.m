 function [w] = insensitivelearning(X,Y,nAugX,r)
%replace LS with epsin-insensitive learning Y=X*c
%epsin-LSSI

epsin = 0.01;
ro = 0.98;
k2 = 1e-4;   %�����Ͽɹ̶���
%[N t] = size(X);
[N n] = size(X);
t = n/nAugX;       %nAugX�����������������ά����1��nAugX-1�൱�������е�t������ά���� �˴���t��Ҷ�ڵ�ĸ�������������
D = diag(ones(2*N,1));
%b = abs(rand(2*N,1));
b = 1e-6*ones(2*N,1);   %��ʱ�ȹ̶�
XX = [X' -X'];  %t*2Nά
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


