function res = optmain(opt,para)
%res 返回结果（程序执行到了哪一步）
%opt 建模　or　优化
%para 程序运算所需其他参数　
%取数据
X=xlsread('2016px.xls','sheet1');
Y=xlsread('2016px.xls','sheet4');%排烟温度
Z=xlsread('2016px.xls','sheet3');%NOx
XX=X(3001:4000,:);
YY=Y(3001:4000,:);
ZZ=Z(3001:4000,:);
a1 = 1; 
a2 =550; 
a3 =600; 
X1 = XX(a1:a2,:);
Y1= YY(a1:a2);
Z1= ZZ(a1:a2);
tX = XX(a2+1:a3,:);
tY1 = YY(a2+1:a3);
tY2 = ZZ(a2+1:a3);
Options = [8 0 5]; 

if opt==1
%空预器入口排烟温度建模及预测
tic;
[Tree1,C1,Err1] =FTreeIII( [ones(size(X1 ,1),1) X1] ,Y1 ,Options,0.28);
t1 = toc;
[RMSE1,Mu1,YFT11] = EvalTree( [ones(size(X1 ,1),1) X1] ,Y1 ,Tree1 ,C1);
[tRMSE1,Mu1,tYFT11] = EvalTree( [ones(size(tX ,1),1) tX] ,tY1 ,Tree1 ,C1);

%NOX建模及预测
tic;
[Tree2,C2,Err2]  = FTreeIII( [ones(size(X1 ,1),1) X1] ,Z1 ,Options,0.27);
t2 = toc;
[a,b]=size(Tree2);
[c,d]=size(C2);
[RMSE2,Mu2,YFT22] = EvalTree( [ones(size(X1 ,1),1) X1] ,Z1 ,Tree2 ,C2);
[tRMSE2,Mu2,tYFT22] = EvalTree( [ones(size(tX ,1),1) tX] ,tY2 ,Tree2 ,C2);

xlswrite('Exa.xls',Tree1,'sheet1');
xlswrite('Exa.xls',C1,'sheet2');
xlswrite('Exa.xls',Tree2,'sheet3');
xlswrite('Exa.xls',C2,'sheet4');
xlswrite('Exa.xls',tYFT11,'sheet5');
xlswrite('Exa.xls',tYFT22,'sheet6');
xlswrite('Exa.xls',RMSE1,'sheet7');
xlswrite('Exa.xls',tRMSE1,'sheet8');
xlswrite('Exa.xls',RMSE2,'sheet9');
xlswrite('Exa.xls',tRMSE2,'sheet10');
xlswrite('Exa.xls',YFT11,'sheet11');
xlswrite('Exa.xls',YFT22,'sheet12');


res = 1;
return
end

Tree1 = xlsread('Exa.xls','sheet1');
C1 = xlsread('Exa.xls','sheet2');
Tree2 = xlsread('Exa.xls','sheet3');
C2 = xlsread('Exa.xls','sheet4');
tYFT11 = xlsread('Exa.xls','sheet5');
tYFT22 = xlsread('Exa.xls','sheet6');
RMSE1 = xlsread('Exa.xls','sheet7');
tRMSE1 = xlsread('Exa.xls','sheet8');
RMSE2 = xlsread('Exa.xls','sheet9');
tRMSE2 = xlsread('Exa.xls','sheet10');
YFT11 = xlsread('Exa.xls','sheet11');
YFT22 = xlsread('Exa.xls','sheet12');




%不可控变量
load =tX(:,1);%负荷
Q =tX(:,2);%供热量
Qi=tX(:,3);%主蒸汽流量
W=tX(:,4);%给水温度
P=tX(:,5);%空预器压差
T2=tX(:,6);%暖风出口二次风温
T1=tX(:,7);%暖风出口一次风温
G=tX(:,8);%给粉机转速平均
M=tX(:,9);%煤质参数
Yo2 = tX(:,10);%入口含氧量
GA =tX(:,11);%给粉机A层比例
GB= tX(:,12);%给粉机B层比例
GC= tX(:,13);%给粉机C层比例
GD= tX(:,14);%给粉机D层比例
GE= tX(:,15);%给粉机E层比例
S18= tX(:,16);%十八层SOFA3
S17= tX(:,17);%十七层SOFA2
S16= tX(:,18);%十六层SOFA1
S15= tX(:,19);%十五层OFA HI
S14= tX(:,20);%十四层OFA HH
S13= tX(:,21);%十三层三次风周H
S12= tX(:,22);%十二层三次风周G
S11= tX(:,23);%十一层三次风周F
S10= tX(:,24);%十层E周
S9= tX(:,25);%九层DE
S8= tX(:,26);%八层D周
S7= tX(:,27);%七层CD
S6= tX(:,28);%六层C周
S5= tX(:,29);%五层BC
S4= tX(:,30);%四层(B周)
S3= tX(:,31);%三层(AB)
S2= tX(:,32);%二层(A周)
S1= tX(:,33);%一层（AA）

tic;
for i=1:50 %对50个点分别优化，得到各点优化后的风门开度以及排烟温度、NOx值
   
    x_axis = rand(1,11);
    y_axis = rand(1,11);%rand(1,6);
    sizepop = 20;%种群规模
    maxgen =40;%迭代次数
    for m=1:sizepop
        x(m,:) = x_axis() + rand()*2+1;
        y(m,:) = y_axis() + rand()*2+1;
        
        D(m,1) = (x(m,1)^2 + y(m,1)^2)^0.5;%果蝇所在位置距原点的距离
        D(m,2) = (x(m,2)^2 + y(m,2)^2)^0.5;
        D(m,3) = (x(m,3)^2 + y(m,3)^2)^0.5;
        D(m,4) = (x(m,4)^2 + y(m,4)^2)^0.5;
        D(m,5) = (x(m,5)^2 + y(m,5)^2)^0.5;
        D(m,6) = (x(m,6)^2 + y(m,6)^2)^0.5;
        D(m,7) = (x(m,7)^2 + y(m,7)^2)^0.5;
        D(m,8) = (x(m,8)^2 + y(m,8)^2)^0.5;
        D(m,9) = (x(m,9)^2 + y(m,9)^2)^0.5;
        D(m,10) = (x(m,10)^2 + y(m,10)^2)^0.5;
        D(m,11) = (x(m,11)^2 + y(m,11)^2)^0.5;
        
        S11(m) = 1/D(m,1)+rand()*D(m,1)+S1(i);%味道浓度判定值，即六处挡风板开度
        S22(m) = 1/D(m,2)+rand()*D(m,2)+S2(i);
        S33(m) = 1/D(m,3)+rand()*D(m,3)+S3(i);
        S44(m) = 1/D(m,4)+rand()*D(m,4)+S4(i);
        S55(m) = 1/D(m,5)+rand()*D(m,5)+S5(i);
        S66(m) = 1/D(m,6)+rand()*D(m,6)+S6(i);
        S77(m) = 1/D(m,7)+rand()*D(m,7)+S7(i);%味道浓度判定值，即六处挡风板开度
        S88(m) = 1/D(m,8)+rand()*D(m,8)+S8(i);
        S99(m) = 1/D(m,9)+rand()*D(m,9)+S9(i);
        S100(m) = 1/D(m,10)+rand()*D(m,10)+S10(i);
        Yo22(m)= 1/D(m,11)+rand()*D(m,11)+Yo2(i);


        %求优化目标函数
        %重组X
        X11 = [load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err11,Mu,YFT1(m)] = EvalTree( [ones(size(X11,1),1) X11] ,tYFT11(i) ,Tree1 ,C1);
        X22 =[load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err22,Mu,YFT2(m)] = EvalTree( [ones(size(X22,1),1) X22] ,tYFT22(i) ,Tree2 ,C2);

                u1 = 1000000;%权值系数
%        优化策略1：NOx满足排放标准，排烟温度最低

%      smell(m) =YFT1(m) + u1*(max(0,YFT2(m)-300))^2;
%         优化策略2:排烟温度满足设定，NOx排放最低
       smell(m) =YFT2(m) + u1*(max(0,YFT1(m)-300))^2;
%        优化策略3:排烟温度满足设定，NOx排放最低
%                       a=0.3;
%           smell(m) =a*(YFT1(m)/400) +(1-a)*(YFT2(m)/500);  
%         优化策略4:排烟温度满足设定，NOx排放最低
%                 a=0.3; b=0.5; 
%           smell(m)=a*(YFT2(m)-tYFT11(i))+b*(YFT1(m)-tYFT11(i));
    end
    [bestsmell bestindex]=min(smell);%得出种群中目标函数值最小的目标值F(m)及个体
    x_axis = x(bestindex,:);
    y_axis = y(bestindex,:);
    S1_new(i) = S11(bestindex);%取得最小目标值时，可调变量风门开度
    S2_new(i) = S22(bestindex);
    S3_new(i) = S33(bestindex);
    S4_new(i) = S44(bestindex);
    S5_new(i) = S55(bestindex);
    S6_new(i) = S66(bestindex);
    S7_new(i) = S77(bestindex);
    S8_new(i) = S88(bestindex);
    S9_new(i) = S99(bestindex);
    S10_new(i) = S100(bestindex);
    Yo2_new(i) = Yo22(bestindex);%取得最小目标值时，可调变量氧量值
    
    Y11_new(i) = YFT1(bestindex);%取得最小目标值时，排烟温度、NOx
    Y22_new(i) = YFT2(bestindex);
    smellbest = bestsmell;%取得种群中最小的目标值
      for n=1:maxgen
        for m=1:sizepop
            x(m,:) = x_axis()+rand()*2+1;
            y(m,:) = y_axis()+rand()*2+1;
            
        D(m,1) = (x(m,1)^2 + y(m,1)^2)^0.5;%果蝇所在位置距原点的距离
        D(m,2) = (x(m,2)^2 + y(m,2)^2)^0.5;
        D(m,3) = (x(m,3)^2 + y(m,3)^2)^0.5;
        D(m,4) = (x(m,4)^2 + y(m,4)^2)^0.5;
        D(m,5) = (x(m,5)^2 + y(m,5)^2)^0.5;
        D(m,6) = (x(m,6)^2 + y(m,6)^2)^0.5;
        D(m,7) = (x(m,7)^2 + y(m,7)^2)^0.5;
        D(m,8) = (x(m,8)^2 + y(m,8)^2)^0.5;
        D(m,9) = (x(m,9)^2 + y(m,9)^2)^0.5;
        D(m,10) = (x(m,10)^2 + y(m,10)^2)^0.5;
        D(m,11) = (x(m,11)^2 + y(m,11)^2)^0.5;
        
        S11(m) = 1/D(m,1)+rand()*D(m,1)+S1(i);%味道浓度判定值，即六处挡风板开度
        S22(m) = 1/D(m,2)+rand()*D(m,2)+S2(i);
        S33(m) = 1/D(m,3)+rand()*D(m,3)+S3(i);
        S44(m) = 1/D(m,4)+rand()*D(m,4)+S4(i);
        S55(m) = 1/D(m,5)+rand()*D(m,5)+S5(i);
        S66(m) = 1/D(m,6)+rand()*D(m,6)+S6(i);
        S77(m) = 1/D(m,7)+rand()*D(m,7)+S7(i);%味道浓度判定值，即六处挡风板开度
        S88(m) = 1/D(m,8)+rand()*D(m,8)+S8(i);
        S99(m) = 1/D(m,9)+rand()*D(m,9)+S9(i);
        S100(m) = 1/D(m,10)+rand()*D(m,10)+S10(i);
        Yo22(m)= 1/D(m,11)+rand()*D(m,11)+Yo2(i);
            %求优化目标函数
            %重组X
        X11 = [load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err11,Mu,YFT1(m)] = EvalTree( [ones(size(X11,1),1) X11] ,tYFT11(i) ,Tree1 ,C1);
        X22 =[load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err22,Mu,YFT2(m)] = EvalTree( [ones(size(X22,1),1) X22] ,tYFT22(i) ,Tree2 ,C2);


            u1 = 1000000;%权值系数  
%        优化策略1：NOx满足排放标准，排烟温度最低

%      smell(m) =YFT1(m) + u1*(max(0,YFT2(m)-300))^2;
%         优化策略2:排烟温度满足设定，NOx排放最低
       smell(m) =YFT2(m) + u1*(max(0,YFT1(m)-300))^2;
%        优化策略3:排烟温度满足设定，NOx排放最低
%                       a=0.3;
%           smell(m) =a*(YFT1(m)/400) +(1-a)*(YFT2(m)/500);  
%         优化策略4:排烟温度满足设定，NOx排放最低
%                 a=0.3; b=0.5; 
%           smell(m)=a*(YFT2(m)-tYFT11(i))+b*(YFT1(m)-tYFT11(i));
        end
        [bestsmell bestindex]=min(smell);
        if bestsmell < smellbest
            x_axis=x(bestindex,:);
            y_axis=y(bestindex,:);
            smellbest=bestsmell;
    S1_new(i) = S11(bestindex);%取得最小目标值时，可调变量风门开度
    S2_new(i) = S22(bestindex);
    S3_new(i) = S33(bestindex);
    S4_new(i) = S44(bestindex);
    S5_new(i) = S55(bestindex);
    S6_new(i) = S66(bestindex);
    S7_new(i) = S77(bestindex);
    S8_new(i) = S88(bestindex);
    S9_new(i) = S99(bestindex);
    S10_new(i) = S100(bestindex);
    Yo2_new(i) = Yo22(bestindex);%取得最小目标值时，可调变量氧量值
    
            Y11_new(i) = YFT1(bestindex);%取得最小目标值时，排烟温度、NOx
            Y22_new(i) = YFT2(bestindex);
  
        end
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    排烟温度  优化前后对比效果%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t3 = toc;

%计算误差
avg1 = mean(tY1);
avg11 = mean(tYFT11);
avg111 = mean(Y11_new);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%% NOx排放   优化前后对比效果%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%计算误差
avg1 = mean(tY2);
avg22 = mean(tYFT22);
avg222 = mean(Y22_new);

RMSE1;
tRMSE1;
RMSE2;
tRMSE2;
e1 = sum(abs((YFT11-Y1))./Y1)/550;
e11 = sum(abs((tYFT11-tY1))./tY1)/50;
e2 = sum(abs((YFT22-Z1))./Z1)/550;
e22 = sum(abs((tYFT22-tY2))./tY2)/50;
RMSE111=sqrt(sum((YFT11-Y1).^2)/550);%排烟温度训练样本均方根误差
RMSE11=sqrt(sum((tYFT11-tY1).^2)/50);%测试样本均方根误差
RMSE222=sqrt(sum((YFT22-Z1).^2)/550);%NOx排放量训练样本均方根误差
RMSE22=sqrt(sum((tYFT22-tY2).^2)/50);%测试样本均方根误差

res = 2;
