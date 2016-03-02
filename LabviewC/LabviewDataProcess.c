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
	int i,j;              //����ѭ���ĳ���,Labview.C�ڵ��У������ȶ����б������壬���򱨴�
	int F1=0;
	int F2=0;              //һ�����价��
	float K=0;             //��ֵK

	float data[1024]={0.0};//�Ѿ�������ݴ���data������,�����������
	float Sum=0;

    int Pike[20]={0};      //��ֵ������
	int flag;              //��Ѱ����ֵ�ı궨��

    int distance;
	int temp=0;
	int index=0;

	float D1 = 0; 
	float D2 = 0;                                   //��ʾ��
    float middle1=0;
	float middle2=0;

	if(((*arg1)->dimSize)!=1024)
		return noErr;      //������ݲ���1024��һά�����У���ֹ

	for(i=0;i<1024;i++)
	{
		data[i]=((*arg1)->elt[i]);
	}


	for(i=0;i<1024;i++)
	{
		Sum+=data[i];
	}
	K=Sum/1024;             //SetK����K��ֵ


  
    for(i=10;i<1014;i++)
	{
		flag=1;
		for(j= -10;j<11;j++)
		{
			if(data[i]<data[i+j]) 
			{
				flag = 0; //����������в������ģ�����
				break;
			}
		}
		if(((flag==1) &&(data[i]>K))&&((i-Pike[index])>=20))//�жϸ߷�㣬ͬʱ���ڸ߷���벻��С��20
		{   
			++index; //Ϊ�˷��㴦��,PIKE[0]=0���ڸñ�������Pike����ֵ
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
	}                                                //�жϵ�һ�����

  
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
	*Din = D2-D1;//�ھ�

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
	*Dout = D2-D1;//�⾶

    *FirstPike=Pike[1]+1;  //����ֵ

	return noErr;
} 