function [Tree,C,Err] = FTreeIII(AugX ,Y ,Options,r)
% FunFTree: 模糊树方法辨识函数   
% Tree: 模糊树模型结构
% Tree=[节点  left(节点) right(节点) 父节点 alfa theta]
% C:    树节点系数,每列对应tree中每行的节点
% alfa,theta:  对应的隶属度函数中的参数
% Options=[ MaxLeaveNode, ExpectErr ,afla]

[mAugX,nAugX]=size(AugX);
%====================   Initialization    ====================%
Tree = [1  0  0  0  0  0];
alfa = Options(3);
C = insensitivelearning(AugX ,Y, nAugX, r);
%C = RecursionLS(AugX ,Y);
%C = RecursionLSSVD(AugX ,Y);
[Err Mu] = EvalTree(AugX ,Y,Tree,C);
depth= 1; 
LeaveNum = 1;
flag = 0;
%====================   Training   ====================%
while( 1 )
%    if (LeaveNum > Options(1))
%        disp('超过允许的叶节点数目')
%        break
%    end
    Leaves = find( Tree(:,2)==0 & Tree(:,3)==0 );
    CurDepthLeaves = Leaves( find(2^(depth-1) <= Tree(Leaves,1) & Tree(Leaves,1) < 2^depth) );
    for l = 1:length(CurDepthLeaves)
        TreeTemp = Tree;
        CTemp = C;
        MuTemp = Mu;
        if CurDepthLeaves(l) == 1
            TreeTemp(1,2:3) = [2 3];
            theta = sum(AugX*CTemp)/mAugX;
            TreeTemp(2,1:6) = [2 0 0 1 -alfa theta];
            TreeTemp(3,1:6) = [3 0 0 1 alfa theta];
            MuTemp(:,2) = EvalIms(AugX*CTemp,[-alfa,theta]);
            MuTemp(:,3) = EvalIms(AugX*CTemp,[alfa,theta]);
            Zeta = [repmat(MuTemp(:,2),1,nAugX) repmat(MuTemp(:,3),1,nAugX)].*repmat(AugX,1,2);
            c = insensitivelearning(Zeta ,Y, nAugX, r);
            %c = RecursionLS(Zeta ,Y);
             %c = RecursionLSSVD(Zeta ,Y);
            CTemp(:,2:3) = [c(1:nAugX) c((nAugX+1):length(c))];
            [ErrTemp MuTemp] = EvalTree(AugX ,Y,TreeTemp,CTemp);
            if Err(depth)>ErrTemp
                LeaveNum = LeaveNum+1;
                if LeaveNum > Options(1)
                    flag = 1;
                    TreeTemp = Tree;
                    CTemp = C;
                    MuTemp = Mu;
                else
                    flag = 0;
                    Tree = TreeTemp;
                    C = CTemp;
                    Mu = MuTemp;
                    Err(depth+1) = ErrTemp;
                end
            else
                TreeTemp = Tree;
                CTemp = C;
                MuTemp = Mu;
            end
        else
            TreeTemp(CurDepthLeaves(l),2:3) = [2*TreeTemp(CurDepthLeaves(l),1) 1+2*TreeTemp(CurDepthLeaves(l),1)];
            YNodecx = AugX*CTemp;
            theta = sum(YNodecx(:,CurDepthLeaves(l)).*MuTemp(:,CurDepthLeaves(l)))/sum(MuTemp(:,CurDepthLeaves(l)));
            TreeTemp(size(TreeTemp,1)+1,1:6) = [TreeTemp(CurDepthLeaves(l),2) 0 0 TreeTemp(CurDepthLeaves(l),1) -alfa theta];
            TreeTemp(size(TreeTemp,1)+1,1:6) = [TreeTemp(CurDepthLeaves(l),3) 0 0 TreeTemp(CurDepthLeaves(l),1) alfa theta];
            AuxiliaryMu = EvalIms(YNodecx(:,CurDepthLeaves(l)),[TreeTemp((size(TreeTemp,1)-1),5) TreeTemp((size(TreeTemp,1)-1),6)]);
            MuTemp(:,size(MuTemp,2)+1) = AuxiliaryMu.*MuTemp(:,CurDepthLeaves(l));
            AuxiliaryMu = EvalIms(YNodecx(:,CurDepthLeaves(l)),[TreeTemp(size(TreeTemp,1),5) TreeTemp(size(TreeTemp,1),6)]);
            MuTemp(:,size(MuTemp,2)+1) = AuxiliaryMu.*MuTemp(:,CurDepthLeaves(l));
            Ctemp(:,[size(CTemp,2)+1 size(CTemp,2)+2]) = zeros(nAugX,2);
            LeavesTemp = find( TreeTemp(:,2)==0 & TreeTemp(:,3)==0 );
            Zeta = [];
            for l=1:length(LeavesTemp)
                Zeta = [Zeta repmat(MuTemp(:,LeavesTemp(l)),1,nAugX)];
            end
            Zeta = Zeta.*repmat(AugX,1,length(LeavesTemp));
             c = insensitivelearning(Zeta ,Y,nAugX,r);
            %c = RecursionLS(Zeta ,Y);
             %c = RecursionLSSVD(Zeta ,Y);
            for l=1:length(LeavesTemp)
                cc(:,l)=c((1+nAugX*(l-1)):nAugX*l);
            end
            CTemp(:,LeavesTemp)= cc;
            [ErrTemp MuTemp] = EvalTree(AugX ,Y,TreeTemp,CTemp);
            if Err(depth)>ErrTemp
                LeaveNumTemp = length(find( TreeTemp(:,2)==0 & TreeTemp(:,3)==0 ));
                if LeaveNumTemp > Options(1)
                    flag = 1;
                    TreeTemp = Tree;
                    CTemp = C;
                    MuTemp = Mu;
                else
                    flag = 0;
                    Tree = TreeTemp;
                    C = CTemp;
                    Mu = MuTemp;
                    Err(depth+1) = ErrTemp;
                end
            else
                TreeTemp = Tree;
                Ctemp = C;
                MuTemp = Mu;
            end
        end
        if flag == 1
            break
        end
    end
    if flag == 1
        disp('超过允许的叶节点数目')
        break
    end
    if length(Err) == depth
        disp('在规定的叶节点划分条件下，没有叶节点需要划分')
        break
    else
        depth = depth+1;
    end
    if Err(depth) <= Options(2)
        disp('模糊树的输出满足规定的精度')
        break
    end
end
