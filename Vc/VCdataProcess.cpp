//  Created by LiangWenqiao on 14/10/1.
//  Copyright � 2014�� LiangWenqiao. All rights reserved.
//  VCdataProcess.cpp
//  ʵ�����价���⾶�����Ĵ���

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define Length 1024 //���󳤶�

void FindPike(const float *data,int *Pike,const float K);
//int FindMiddle(const float *data,const int *Pike,const float K); //�ԳƵ��ҷ�ֵ�İ취�Ѿ������ˣ���ʱ����
float SetK(const float *data);
//void FindFirst(const float *data,int *F1,int *F2,const int Middle,const float K,const int *Pike);//�ɰ汾����һ�����价������������ʱ����
void FindFirst(int *F1,int *F2,const int *Pike);
void CalculatLameda(const float *data,const int F1,const int F2,float *Dout,float *Din,const float K);

int main()
{   
	int start=GetTickCount();
	int i = 0; 
	int F1 =0;
	int F2 =0;            //��׼�߸���ĵ�һ���������λ��
	int Pike[20] = {0}; //Pike�ĵ�һ�����ֵΪ��
	int Middle = 0;
	float Dout = 0;
	float Din = 0;      //��׼�߸���ʱ�ĵ�һ�����价Din��Dout����
	float data[Length] = {0.0} ;
	FILE *fin;
	fin = fopen("C:\\data1.txt","r"); //��ȡ��õ������ļ���·��Ҫ��ָ������Ȼ���ܶ�ȡ�ļ�����
	for(i=0;i<Length;i++)
	{
		fscanf(fin,"%f",&data[i]); //����ļ���ÿһ�е�����
	}
	for(i=0;i<Length;i++)
		printf("%f\n",data[i]);      //������飬������ȫ�������ݣ���������ʾ��Χ�й�
	fclose(fin);
	float K = SetK(data); //��ֵ
	FindPike(data,Pike,K); //�����鸳ֵ��0��ʼ
	printf("��ֵK��ֵ��");
	printf("%f\n",K); 
	for(i=1;i<20;i++)
	 {
		 printf("��%d�����λ�ã�",i);
		 printf("%d\n",Pike[i]);
	}
   //Middle = FindMiddle(data,Pike,K);
   //printf("����㣺");
   //printf("%d\n",Middle);
   // FindFirst(data,&F1,&F2,Middle,K,Pike);
   FindFirst(&F1,&F2,Pike);
   printf("һ�����价��λ�ã�\n");
   printf("%d ��ֵ:%f\n",F1,data[F1]);
   printf("%d ��ֵ:%f\n",F2,data[F2]);
   CalculatLameda(data,F1,F2,&Dout,&Din,K);
   printf("�ھ���%f\n",Din);
   printf("�⾶��%f\n",Dout);
   int end=GetTickCount();
   printf("�������к�ʱ: %d ����",end-start); //��ʾ���к�ʱ������Դ����ٶȷ���
   getchar();
   return 0;
}

void FindPike(const float *data,int *Pike,const float K)
{
	int i ;
	int j ;
	int flag;             //���ֵ�ı��
	for(i=10;i<Length;i++)
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
		if(((flag==1) &&(data[i]>K))&&((i-*Pike)>=20))//�жϸ߷�㣬ͬʱ���ڵĸ߷���벻��С��20�����С�ھ��õ�һ����ֵ
		{   
			++Pike; //Ϊ�˼��㷽�㣬��һ������λ����0
			*Pike=i;
		}
	}
}

float SetK(const float *data) //�趨��ֵK
{
	float Sum = 0;
	float K = 0;
	for(int i = 0 ;i<Length ;i++)
	{
		Sum+=data[i];
	}
	K=Sum/Length;
   return K;
}

/*int FindMiddle(const float *data,const int *Pike,const float K) //�ɰ汾����Ѱ�����
{
	int index ;//�趨��ʼ����Ѱ��Χ
	int Middle = 0;
	float FrontData = 0;
	float BehindData =0;
	float AbsData =0.0 ; //����ֵ
	float Temp = K*Length;
	for(int i = Pike[1]; i<Length ;i++)
	{
		if(data[i]<K) 
			{
				index = i; //���ǰ��������Ĳ��Գƶȣ��Ƿ�Ҫ���崦��
				break;
		    }
	}

	for(i = index+1;i<Length;i++)
	{
		float FrontData = 0;   
		float BehindData =0 ; //������ע��ѭ����ʼ����0
		for(int j = index ; j<i ;j++)
		{
			FrontData += data[j];  //��ǰ���
		}
		for(j = i+1 ; j<Length ;j++)
		{
			BehindData += data[j]; //�������
		}
		AbsData = ((FrontData - BehindData)>0)?(FrontData - BehindData):(BehindData - FrontData);
        Temp =(Temp<AbsData)?Temp:AbsData;
	}
		
	for(i =index+1;i<Length;i++)
	{
		float FrontData = 0;
		float BehindData =0 ;
		for(int j = index ; j<i ;j++)
		{
			FrontData += data[j];  //��ǰ���
		}
		for(j = i+1 ; j<Length ;j++)
		{
			BehindData += data[j]; //�������
		}
		AbsData = ((FrontData - BehindData)>0)?(FrontData - BehindData):(BehindData - FrontData);//����ֵ
		if((AbsData-Temp)<1e-6)
		{
			Middle = i ;
		    break;
		}
	}
	printf("��ԳƵ������ֵ��");
	printf("%f\n",Temp);
	printf("��ʼ��Ѱ��λ�ã�");
	printf("%d\n",index);
   return Middle;
}
*/
/*void FindFirst(const float *data,int *F1,int *F2,const int Middle,const float K,const int *Pike) //�ɰ汾����һ�����价
{
        int temp=0;
	int AbsL=0;
	if(data[Middle]<K)
	{
	  for(int i = 2;i<19 ;i++)
	  {
	      temp=(temp>(Pike[i]-Pike[i-1]))?temp:(Pike[i]-Pike[i-1]);
	  }
	   for(i = 2;i<19 ;i++)
	  {
	      if(temp==(Pike[i]-Pike[i-1]))
		  {
		     *F1=Pike[i-1];
		     *F2=Pike[i];                                  //��Ѱ����һ��������
		  }
	  }
	}
	else if(data[Middle]>K)
	{
		temp=Length;
		for(int i =1;i<19;i++)
		{
			AbsL=((Pike[i]-Middle)>0)?(Pike[i]-Middle):(Middle-Pike[i]);   //�жϵ�һ��������
			temp=(temp<AbsL)?temp:AbsL;
		}
		for(i =1;i<19;i++)
		{
			AbsL=((Pike[i]-Middle)>0)?(Pike[i]-Middle):(Middle-Pike[i]);
			if(temp==AbsL)
			{
				*F1=Pike[i-1];
				*F2=Pike[i+1];
			}
		}
	}
}*/
void FindFirst(int *F1,int *F2,const int *Pike)
{
	int distance;
	int temp=0;
	for(int i=2;Pike[i]>0;i++)
	{
		distance=(Pike[i+2]-Pike[i]);
        temp = (temp<distance)?distance:temp;
	}
	for(i=2;Pike[i]>0;i++)
	{
		distance=(Pike[i+2]-Pike[i]);
        if(distance==temp)
		{
			*F1=Pike[i];
			*F2=Pike[i+2];
			break;
		}
	}
}

void CalculatLameda(const float *data,const int F1,const int F2,float *Dout,float *Din,const float K) //�����ھ��⾶,ע�⸡�����жϵ�����
{
	float D1 = 0;
	float D2 = 0;

	float middle1=0.5*(data[F1]+K);
	float middle2=0.5*(data[F2]+K);

	for(int i=F1;i<F2;i++)
	{
		
		if((data[i]>middle1)&&(data[i+1]<middle1))
		{
			D1 = i+(data[i]-middle1)/(data[i]-data[i+1]);  //��F1��F2��Ѱ
			break;
		}
	}
	for(i=F2 ;i>F1;i--)
	{
		if((middle2>data[i-1])&&(middle2<data[i]))
		{
			D2 = i+(middle2-data[i])/(data[i]-data[i-1]); //��F2��F1��Ѱ
			break;
		}
	}
	*Din = D2-D1;                                                 //�����ھ�

        for(i=F1;i>0;i--)
	{
		 if((middle1>data[i-1])&&(middle1<data[i]))
		{
			D1 = i+(middle1-data[i])/(data[i]-data[i-1]); //��0��F1��Ѱ
			break;
		}
	}
	for(i=F2 ;i<Length;i++)
	{
		  if((data[i]>middle2)&&(data[i+1]<middle2))
		{
			D2 = i+(data[i]-middle2)/(data[i]-data[i+1]); //��F2��1023��Ѱ
			break;
		}
	}
	*Dout = D2-D1;//�⾶
}