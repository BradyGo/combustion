function [ms]=EvalIms(y,p )
ms = 1./(1.+exp(-p(1)*(y-p(2))));