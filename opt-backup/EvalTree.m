function [Err,Mu,YFT] = EvalTree(AugX ,Y,Tree,C)

YNodecx = AugX*C;
[mAugX,nAugX]=size(AugX);

Mu(:,1) = ones(mAugX,1);
for i = 2 : size(Tree,1)
   parent = find(Tree(:,1) == Tree(i,4));
   AuxiliaryMu = EvalIms(YNodecx(:,parent),[Tree(i,5) Tree(i,6)]);
   Mu(:,i) = AuxiliaryMu.*Mu(:,parent);
end
Leaves = find(Tree(:,2)==0 & Tree(:,3)==0);

if Leaves == 1,   
    YFT = YNodecx;  
else
    YFT = sum((YNodecx(:,Leaves).*Mu(:,Leaves))')'./sum(Mu(:,Leaves)')';
end

Err = norm(Y-YFT)/sqrt(mAugX);