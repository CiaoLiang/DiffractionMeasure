/* CIN source file */

#include "extcode.h"

/* Typedefs */

typedef struct {
	int32 dimSize;
	float64 elt[1];
	} TD1;
typedef TD1 **TD1Hdl;

MgErr CINRun(TD1Hdl arg1, int32 *FirstPike, float32 *Din, float32 *Dout);

MgErr CINRun(TD1Hdl arg1, int32 *FirstPike, float32 *Din, float32 *Dout)
	{
	int i,j;              //用于循环的常量,Labview.C节点中，必须先对所有变量定义，否则报错
	int F1=0;
	int F2=0;              //一级衍射环峰
	float K=0;             //阈值K

	float data[1024]={0.0};//把句柄中数据存在data数组中,方便后续操作
	float Sum=0;

    int Pike[20]={0};      //峰值的数据
	int flag;              //搜寻尖峰的值的标定符

    int distance;
	int temp=0;
	int index=0;

	float D1 = 0; 
	float D2 = 0;                                   //标示点
    float middle1=0;
	float middle2=0;

	if(((*arg1)->dimSize)!=1024)
		return noErr;      //如果数据不是1024个一维的阵列，终止

	for(i=0;i<1024;i++)
	{
		data[i]=((*arg1)->elt[i]);
	}


	for(i=0;i<1024;i++)
	{
		Sum+=data[i];
	}
	K=Sum/1024;             //SetK设置K的值


  
    for(i=10;i<1014;i++)
	{
		flag=1;
		for(j= -10;j<11;j++)
		{
			if(data[i]<data[i+j]) 
			{
				flag = 0; //如果在区间中不是最大的，跳出
				break;
			}
		}
		if(((flag==1) &&(data[i]>K))&&((i-Pike[index])>=20))//判断高峰点，同时相邻高峰距离不能小于20
		{   
			++index; //为了方便处理,PIKE[0]=0，在该编译器中Pike是左值
			Pike[index]=i;
		}
	}


	for(i=2;Pike[i]>0;i++)
	{
		distance=(Pike[i+2]-Pike[i]);
        temp = (temp<distance)?distance:temp;
	}
	for(i=2;Pike[i]>0;i++)
	{
		distance=(Pike[i+2]-Pike[i]);
        if(distance==temp)
		{
			F1=Pike[i];
			F2=Pike[i+2];
			break;
		}
	}                                                //判断第一级尖峰

  
	middle1=0.5*(data[F1]+K);
    middle2=0.5*(data[F2]+K); 
	for(i=F1;i<F2;i++)
	{
		
		if((data[i]>middle1)&&(data[i+1]<middle1))
		{
			D1 = i+(data[i]-middle1)/(data[i]-data[i+1]);
			break;
		}
	}
	for(i=F2 ;i>F1;i--)
	{
		if((middle2>data[i-1])&&(middle2<data[i]))
		{
			D2 = i+(middle2-data[i])/(data[i]-data[i-1]);
			break;
		}
	}
	*Din = D2-D1;//内径

   for(i=F1;i>0;i--)
	{
		 if((middle1>data[i-1])&&(middle1<data[i]))
		{
			D1 = i+(middle1-data[i])/(data[i]-data[i-1]);
			break;
		}
	}
	for(i=F2 ;i<1023;i++)
	{
		  if((data[i]>middle2)&&(data[i+1]<middle2))
		{
			D2 = i+(data[i]-middle2)/(data[i]-data[i+1]);
			break;
		}
	}
	*Dout = D2-D1;//外径

    *FirstPike=Pike[1]+1;  //初测值

	return noErr;
} 