// Ctestdll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include "mclmcr.h"

#include "matrix.h"

#include "mclcppclass.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{

	if(!optInitialize())
	{
		cout<<"init error"<<endl;
	}
	
	// 为变量分配内存空间，可以查帮助mwArray
	mwArray a(1,1,mxDOUBLE_CLASS);
    mwArray b(1,1,mxDOUBLE_CLASS);
	a(1,1)=20;
    b(1,1)=30;
	mwArray x(1,1,mxDOUBLE_CLASS);

	main(1,x,a,b);

	double *i=new double;
	 x.GetData(i,1);
	 cout<<"x="<<*i<<endl; 


	/*
	mwArray a(1,1,mxDOUBLE_CLASS);
    mwArray b(1,1,mxDOUBLE_CLASS);
    a(1,1)=20;
    b(1,1)=30;
    mwArray x(1,1,mxDOUBLE_CLASS);
    mwArray y(1,1,mxDOUBLE_CLASS);
    //输出参数个数,输出参数,输入参数。
    add(2,x,y,a,b);
    double *i=new double;
    double *j=new double ;
    x.GetData(i,1);
    y.GetData(j,1);    
    cout<<"x="<<*i<<"  y="<<*j<<endl; 
    getchar();
	*/

	return 0;
}

