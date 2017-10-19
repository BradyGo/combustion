clc;close all;clear all
%ȡ����
X=xlsread('2016px.xls','sheet1');
Y=xlsread('2016px.xls','sheet4');%�����¶�
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

%��Ԥ����������¶Ƚ�ģ��Ԥ��
tic
[Tree1,C1,Err1] =FTreeIII( [ones(size(X1 ,1),1) X1] ,Y1 ,Options,0.28);
t1 = toc
[RMSE1,Mu1,YFT11] = EvalTree( [ones(size(X1 ,1),1) X1] ,Y1 ,Tree1 ,C1);
[tRMSE1,Mu1,tYFT11] = EvalTree( [ones(size(tX ,1),1) tX] ,tY1 ,Tree1 ,C1);

%NOX��ģ��Ԥ��
tic
[Tree2,C2,Err2]  = FTreeIII( [ones(size(X1 ,1),1) X1] ,Z1 ,Options,0.27);
t2 = toc
[a,b]=size(Tree2)
[c,d]=size(C2)
[RMSE2,Mu2,YFT22] = EvalTree( [ones(size(X1 ,1),1) X1] ,Z1 ,Tree2 ,C2);
[tRMSE2,Mu2,tYFT22] = EvalTree( [ones(size(tX ,1),1) tX] ,tY2 ,Tree2 ,C2);

tYFT11;
tYFT22;
%���ɿر���
load =tX(:,1);%����
Q =tX(:,2);%������
Qi=tX(:,3);%����������
W=tX(:,4);%��ˮ�¶�
P=tX(:,5);%��Ԥ��ѹ��
T2=tX(:,6);%ů����ڶ��η���
T1=tX(:,7);%ů�����һ�η���
G=tX(:,8);%���ۻ�ת��ƽ��
M=tX(:,9);%ú�ʲ���
Yo2 = tX(:,10);%��ں�����
GA =tX(:,11);%���ۻ�A�����
GB= tX(:,12);%���ۻ�B�����
GC= tX(:,13);%���ۻ�C�����
GD= tX(:,14);%���ۻ�D�����
GE= tX(:,15);%���ۻ�E�����
S18= tX(:,16);%ʮ�˲�SOFA3
S17= tX(:,17);%ʮ�߲�SOFA2
S16= tX(:,18);%ʮ����SOFA1
S15= tX(:,19);%ʮ���OFA HI
S14= tX(:,20);%ʮ�Ĳ�OFA HH
S13= tX(:,21);%ʮ�������η���H
S12= tX(:,22);%ʮ�������η���G
S11= tX(:,23);%ʮһ�����η���F
S10= tX(:,24);%ʮ��E��
S9= tX(:,25);%�Ų�DE
S8= tX(:,26);%�˲�D��
S7= tX(:,27);%�߲�CD
S6= tX(:,28);%����C��
S5= tX(:,29);%���BC
S4= tX(:,30);%�Ĳ�(B��)
S3= tX(:,31);%����(AB)
S2= tX(:,32);%����(A��)
S1= tX(:,33);%һ�㣨AA��

tic
for i=1:50 %��50����ֱ��Ż����õ������Ż���ķ��ſ����Լ������¶ȡ�NOxֵ
   
    x_axis = rand(1,11);
    y_axis = rand(1,11);%rand(1,6);
    sizepop = 20;%��Ⱥ��ģ
    maxgen =40;%��������
    for m=1:sizepop
        x(m,:) = x_axis() + rand()*2+1;
        y(m,:) = y_axis() + rand()*2+1;
        
        D(m,1) = (x(m,1)^2 + y(m,1)^2)^0.5;%��Ӭ����λ�þ�ԭ��ľ���
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
        
        S11(m) = 1/D(m,1)+rand()*D(m,1)+S1(i);%ζ��Ũ���ж�ֵ������������忪��
        S22(m) = 1/D(m,2)+rand()*D(m,2)+S2(i);
        S33(m) = 1/D(m,3)+rand()*D(m,3)+S3(i);
        S44(m) = 1/D(m,4)+rand()*D(m,4)+S4(i);
        S55(m) = 1/D(m,5)+rand()*D(m,5)+S5(i);
        S66(m) = 1/D(m,6)+rand()*D(m,6)+S6(i);
        S77(m) = 1/D(m,7)+rand()*D(m,7)+S7(i);%ζ��Ũ���ж�ֵ������������忪��
        S88(m) = 1/D(m,8)+rand()*D(m,8)+S8(i);
        S99(m) = 1/D(m,9)+rand()*D(m,9)+S9(i);
        S100(m) = 1/D(m,10)+rand()*D(m,10)+S10(i);
        Yo22(m)= 1/D(m,11)+rand()*D(m,11)+Yo2(i);

%         S11(m) = 1/D(m,1)*0.5+S1(i);%ζ��Ũ���ж�ֵ������������忪��
%         S22(m) = 1/D(m,2)*0.5+S2(i);
%         S33(m) = 1/D(m,3)*0.3+S3(i);
%         S44(m) = 1/D(m,4)*0.3+S4(i);
%         S55(m) = 1/D(m,5)*0.5+S5(i);
%         S66(m) = 1/D(m,6)*0.5+S6(i);
%         S77(m) = 1/D(m,7)*0.7+S7(i);%ζ��Ũ���ж�ֵ������������忪��
%         S88(m) = 1/D(m,8)*0.7+S8(i);
%         S99(m) = 1/D(m,9)*0.3+S9(i);
%         S100(m) = 1/D(m,10)*0.3+S10(i);
%         Yo22(m)= 1/D(m,11)*0.3+Yo2(i);

%         S11(m) = 1/D(m,1)+rand()*D(m,1)+S1(i);%ζ��Ũ���ж�ֵ������������忪��
%         S22(m) = 1/D(m,2)+rand()*D(m,2)+S2(i);
%         S33(m) = 1/D(m,3)+rand()*D(m,3)+S3(i);
%         S44(m) = 1/D(m,4)+rand()*D(m,4)+S4(i);
%         S55(m) = 1/D(m,5)+rand()*D(m,5)+S5(i);
%         S66(m) = 1/D(m,6)+rand()*D(m,6)+S6(i);
%         S77(m) = 1/D(m,7)+rand()*D(m,7)+S7(i);%ζ��Ũ���ж�ֵ������������忪��
%         S88(m) = 1/D(m,8)+rand()*D(m,8)+S8(i);
%         S99(m) = 1/D(m,9)+rand()*D(m,9)+S9(i);
%         S100(m) = 1/D(m,10)+rand()*D(m,10)+S10(i);
%         Yo22(m)= 1/D(m,11)+rand()*D(m,11)+Yo2(i);
        %���Ż�Ŀ�꺯��
        %����X
        X11 = [load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err11,Mu,YFT1(m)] = EvalTree( [ones(size(X11,1),1) X11] ,tYFT11(i) ,Tree1 ,C1);
        X22 =[load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err22,Mu,YFT2(m)] = EvalTree( [ones(size(X22,1),1) X22] ,tYFT22(i) ,Tree2 ,C2);

                u1 = 1000000;%Ȩֵϵ��
%        �Ż�����1��NOx�����ŷű�׼�������¶����

%      smell(m) =YFT1(m) + u1*(max(0,YFT2(m)-300))^2;
%         �Ż�����2:�����¶������趨��NOx�ŷ����
       smell(m) =YFT2(m) + u1*(max(0,YFT1(m)-300))^2;
%        �Ż�����3:�����¶������趨��NOx�ŷ����
%                       a=0.3;
%           smell(m) =a*(YFT1(m)/400) +(1-a)*(YFT2(m)/500);  
%         �Ż�����4:�����¶������趨��NOx�ŷ����
%                 a=0.3; b=0.5; 
%           smell(m)=a*(YFT2(m)-tYFT11(i))+b*(YFT1(m)-tYFT11(i));
    end
    [bestsmell bestindex]=min(smell);%�ó���Ⱥ��Ŀ�꺯��ֵ��С��Ŀ��ֵF(m)������
    x_axis = x(bestindex,:);
    y_axis = y(bestindex,:);
    S1_new(i) = S11(bestindex);%ȡ����СĿ��ֵʱ���ɵ��������ſ���
    S2_new(i) = S22(bestindex);
    S3_new(i) = S33(bestindex);
    S4_new(i) = S44(bestindex);
    S5_new(i) = S55(bestindex);
    S6_new(i) = S66(bestindex);
    S7_new(i) = S77(bestindex);
    S8_new(i) = S88(bestindex);
    S9_new(i) = S99(bestindex);
    S10_new(i) = S100(bestindex);
    Yo2_new(i) = Yo22(bestindex);%ȡ����СĿ��ֵʱ���ɵ���������ֵ
    
    Y11_new(i) = YFT1(bestindex);%ȡ����СĿ��ֵʱ�������¶ȡ�NOx
    Y22_new(i) = YFT2(bestindex);
    smellbest = bestsmell;%ȡ����Ⱥ����С��Ŀ��ֵ
      for n=1:maxgen
        for m=1:sizepop
            x(m,:) = x_axis()+rand()*2+1;
            y(m,:) = y_axis()+rand()*2+1;
            
        D(m,1) = (x(m,1)^2 + y(m,1)^2)^0.5;%��Ӭ����λ�þ�ԭ��ľ���
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
        
        S11(m) = 1/D(m,1)+rand()*D(m,1)+S1(i);%ζ��Ũ���ж�ֵ������������忪��
        S22(m) = 1/D(m,2)+rand()*D(m,2)+S2(i);
        S33(m) = 1/D(m,3)+rand()*D(m,3)+S3(i);
        S44(m) = 1/D(m,4)+rand()*D(m,4)+S4(i);
        S55(m) = 1/D(m,5)+rand()*D(m,5)+S5(i);
        S66(m) = 1/D(m,6)+rand()*D(m,6)+S6(i);
        S77(m) = 1/D(m,7)+rand()*D(m,7)+S7(i);%ζ��Ũ���ж�ֵ������������忪��
        S88(m) = 1/D(m,8)+rand()*D(m,8)+S8(i);
        S99(m) = 1/D(m,9)+rand()*D(m,9)+S9(i);
        S100(m) = 1/D(m,10)+rand()*D(m,10)+S10(i);
        Yo22(m)= 1/D(m,11)+rand()*D(m,11)+Yo2(i);
            %���Ż�Ŀ�꺯��
            %����X
        X11 = [load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err11,Mu,YFT1(m)] = EvalTree( [ones(size(X11,1),1) X11] ,tYFT11(i) ,Tree1 ,C1);
        X22 =[load(i),Q(i),Qi(i),W(i),P(i),T2(i),T1(i),G(i),M(i),GA(i),GB(i),GC(i),GD(i),GE(i),S18(i),S17(i),S16(i),S15(i),S14(i),S13(i),S12(i),S11(i),S100(m),S99(m),S88(m),S77(m),S66(m),S55(m),S44(m),S33(m),S22(m),S11(m),Yo22(m)];
        [Err22,Mu,YFT2(m)] = EvalTree( [ones(size(X22,1),1) X22] ,tYFT22(i) ,Tree2 ,C2);


            u1 = 1000000;%Ȩֵϵ��  
%        �Ż�����1��NOx�����ŷű�׼�������¶����

%      smell(m) =YFT1(m) + u1*(max(0,YFT2(m)-300))^2;
%         �Ż�����2:�����¶������趨��NOx�ŷ����
       smell(m) =YFT2(m) + u1*(max(0,YFT1(m)-300))^2;
%        �Ż�����3:�����¶������趨��NOx�ŷ����
%                       a=0.3;
%           smell(m) =a*(YFT1(m)/400) +(1-a)*(YFT2(m)/500);  
%         �Ż�����4:�����¶������趨��NOx�ŷ����
%                 a=0.3; b=0.5; 
%           smell(m)=a*(YFT2(m)-tYFT11(i))+b*(YFT1(m)-tYFT11(i));
        end
        [bestsmell bestindex]=min(smell);
        if bestsmell < smellbest
            x_axis=x(bestindex,:);
            y_axis=y(bestindex,:);
            smellbest=bestsmell;
    S1_new(i) = S11(bestindex);%ȡ����СĿ��ֵʱ���ɵ��������ſ���
    S2_new(i) = S22(bestindex);
    S3_new(i) = S33(bestindex);
    S4_new(i) = S44(bestindex);
    S5_new(i) = S55(bestindex);
    S6_new(i) = S66(bestindex);
    S7_new(i) = S77(bestindex);
    S8_new(i) = S88(bestindex);
    S9_new(i) = S99(bestindex);
    S10_new(i) = S100(bestindex);
    Yo2_new(i) = Yo22(bestindex);%ȡ����СĿ��ֵʱ���ɵ���������ֵ
    
            Y11_new(i) = YFT1(bestindex);%ȡ����СĿ��ֵʱ�������¶ȡ�NOx
            Y22_new(i) = YFT2(bestindex);
  
        end
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    �����¶�  �Ż�ǰ��Ա�Ч��%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t3 = toc
figure(1)
plot(tY1,'k-','linewidth',1.5) ,hold on ,plot(tYFT11,'k--','markersize',4.5,'linewidth',1.5) ,hold on ,plot(Y11_new,'k-s','markersize',4.5,'linewidth',1.3) ,hold off
%�����ע
xlabel('��������','FontSize',10.5,'FontName','����');
ylabel('�����¶�/��','FontSize',10.5,'FontName','����')
%�̶������С
set(gca,'FontSize',10.5)
%����legend
h=legend('ʵ��ֵ','ģ��Ԥ��ֵ','ģ���Ż�ֵ');
set(h,'Fontsize',10.5,'FontName','����');
% legend('boxoff')
box off%ȥ��ͼ���е��ҿ��ߺ��Ͽ���
%����������
 ylim([320,390]);%Ϊ���������÷�Χ
%�������
avg1 = mean(tY1)
avg11 = mean(tYFT11)
avg111 = mean(Y11_new)
set (gcf,'windowstyle','normal')
set (gcf,'Position',[1000,300,1000,300])
% E1 = sum((Y11_new'-tYFT11)./tYFT11)/50       %ƽ��������
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% NOx�ŷ�   �Ż�ǰ��Ա�Ч��%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2)
plot(tY2,'k-','linewidth',1.5) ,hold on ,plot(tYFT22,'k--','markersize',4,'linewidth',1.5) ,hold on ,plot(Y22_new,'k-s','markersize',4.5,'linewidth',1.3) ,hold off
%�����ע
xlabel('��������','FontSize',10.5,'FontName','����'); 
ylabel('NO_x�ŷ���/��mg��m^-^3��','FontSize',10.5,'FontName','����');
%�̶������С
set(gca,'FontSize',10.5)
%����legend
h=legend('ʵ��ֵ','ģ��Ԥ��ֵ','ģ���Ż�ֵ');
set(h,'Fontsize',10.5,'FontName','����');
% legend('boxoff')
box off
%����������
 ylim([150,550]);%Ϊ���������÷�Χ
%�������
avg1 = mean(tY2)
avg22 = mean(tYFT22)
avg222 = mean(Y22_new)
set (gcf,'windowstyle','normal')
set (gcf,'Position',[1000,300,1000,300])
% E2 = sum((Y22_new'-tYFT22)./tYFT22)/50       %ƽ��������  
RMSE1
tRMSE1
RMSE2
tRMSE2
e1 = sum(abs((YFT11-Y1))./Y1)/550
e11 = sum(abs((tYFT11-tY1))./tY1)/50
e2 = sum(abs((YFT22-Z1))./Z1)/550
e22 = sum(abs((tYFT22-tY2))./tY2)/50
RMSE111=sqrt(sum((YFT11-Y1).^2)/550)%�����¶�ѵ���������������
RMSE11=sqrt(sum((tYFT11-tY1).^2)/50)%�����������������
RMSE222=sqrt(sum((YFT22-Z1).^2)/550)%NOx�ŷ���ѵ���������������
RMSE22=sqrt(sum((tYFT22-tY2).^2)/50)%�����������������
% E1 = sum(abs((S1_new(1:50)'-S1(1:50))./S1(1:50)))/50
% E2 = sum(abs((S2_new(1:50)'-S2(1:50))./S2(1:50)))/50
% E3 = sum(abs((S3_new(1:50)'-S3(1:50))./S3(1:50)))/50
% E4 = sum(abs((S4_new(1:50)'-S4(1:50))./S4(1:50)))/50
% E5 = sum(abs((S5_new(1:50)'-S5(1:50))./S5(1:50)))/50
% E6 = sum(abs((S6_new(1:50)'-S6(1:50))./S6(1:50)))/50
% E7 = sum(abs((S7_new(1:50)'-S7(1:50))./S7(1:50)))/50
% E8 = sum(abs((S8_new(1:50)'-S8(1:50))./S8(1:50)))/50
% E9 = sum(abs((S9_new(1:50)'-S9(1:50))./S9(1:50)))/50
% E10 = sum(abs((S10_new(1:50)'-S10(1:50))./S10(1:50)))/50
% E11 = sum(abs((Yo2_new(1:50)'-Yo2(1:50))./Yo2(1:50)))/50

%%%%%%%%%%%%%%%%%%%%��������%%%%%%%%%%%%%%%%%%%%%%%
% a=Y1(81:125);
% % save('Boiler.mat','a')
% % save('Boiler1.mat','Y11_new');
% save('Boiler2.mat','Y11_new');
% % save('Boiler3.mat','Y11_new');
% b=Y2(81:125);
% % save('NOx.mat','b')
% % save('NOx1.mat','Y22_new');
% save('NOx2.mat','Y22_new');
% % save('NOx3.mat','Y22_new');
% c=Y3(81:125);
% % save('SO2.mat','c');
% % save('SO21.mat','Y33_new');
% save('SO22.mat','Y33_new');
% % save('SO23.mat','Y33_new');
%%%%%%%%%%%%%%%%%%%%�ɵ������ı仯��Χ%%%%%%%%%%%%%%%%%%%%%%%
%  figure(3)
% [AX]=plotyy(S1,'k',load,'b')
% hold on;
% plot(S1_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','һ���');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[40,100],'yTick',[40:5:100]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(4)
% [AX]=plotyy(S2,'k',load,'b')
% hold on;
% plot(S2_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�����');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[0,40],'yTick',[0:5:40]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
%  figure(5)
% [AX]=plotyy(S3,'k',load,'b')
% hold on;
% plot(S3_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�����');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[50,100],'yTick',[50:5:100]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(6)
% [AX]=plotyy(S4,'k',load,'b')
% hold on;
% plot(S4_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�Ĳ��');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[0,40],'yTick',[0:5:40]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(7)
% [AX]=plotyy(S5,'k',load,'b')
% hold on;
% plot(S5_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','����');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[5,40],'yTick',[5:5:40]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
%  figure(8)
% [AX]=plotyy(S6,'k',load,'b')
% hold on;
% plot(S6_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�����');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[0,25],'yTick',[0:5:25]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(9)
% [AX]=plotyy(S7,'k',load,'b')
% hold on;
% plot(S7_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�߲��');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[25,80],'yTick',[25:5:80]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
%  figure(10)
% [AX]=plotyy(S8,'k',load,'b')
% hold on;
% plot(S8_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�˲��');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[6,25],'yTick',[6:5:25]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(11)
% [AX]=plotyy(S9,'k',load,'b')
% hold on;
% plot(S9_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','�Ų��');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[20,80],'yTick',[20:5:80]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% % 
% figure(12)
% [AX]=plotyy(S10,'k',load,'b')
% hold on;
% plot(S10_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','ʮ���');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[6,30],'yTick',[6:5:30]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% 
% figure(13)
% [AX]=plotyy(Yo2,'k',load,'b')
% hold on;
% plot(Yo2_new,'k:');
% %�����ע
% set(get(gca,'xlabel'),'string','��������')
% set(get(AX(1),'Ylabel'),'string','����������');
% set(get(AX(2),'Ylabel'),'string','���鸺��');
% set(AX(1),'ylim',[0,25],'yTick',[0:5:25]);%�趨���Y���귶Χ
% set(AX(2),'ylim',[240,300],'yTick',[240:10:280]);%�趨���Y���귶Χ
% h=legend('�Ż�ǰ','�Ż���','���鸺��');
% set(h,'Fontsize',10.5);
% legend('boxoff')
% set(h,'Fontsize',10.5);
% box off%ȥ��ͼ���е��ҿ��ߺ��Ͽ���