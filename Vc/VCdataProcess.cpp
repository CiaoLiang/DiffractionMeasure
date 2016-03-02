//  Created by LiangWenqiao on 14/10/1.
//  Copyright ı 2014Äê LiangWenqiao. All rights reserved.
//  VCdataProcess.cpp
//  ÊµÏÖÑÜÉä»·ÄÚÍâ¾¶²âÁ¿µÄ´úÂë

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define Length 1024 //µãÕó³¤¶È

void FindPike(const float *data,int *Pike,const float K);
//int FindMiddle(const float *data,const int *Pike,const float K); //¶Ô³ÆµãÕÒ·åÖµµÄ°ì·¨ÒÑ¾­ŞğÆúÁË£¬ÔİÊ±±£Áô
float SetK(const float *data);
//void FindFirst(const float *data,int *F1,int *F2,const int Middle,const float K,const int *Pike);//¾É°æ±¾µÄÕÒÒ»¼¶ÑÜÉä»·£¬ÒÑŞğÆú£¬ÔİÊ±±£Áô
void FindFirst(int *F1,int *F2,const int *Pike);
void CalculatLameda(const float *data,const int F1,const int F2,float *Dout,float *Din,const float K);

int main()
{   
	int start=GetTickCount();
	int i = 0; 
	int F1 =0;
	int F2 =0;            //±ê×¼¾ß¸ÉÉæµÄµÚÒ»¼¶ÑÜÉä¼â·åµÄÎ»ÖÃ
	int Pike[20] = {0}; //PikeµÄµÚÒ»¸ö¼â·åÖµÎªÁã
	int Middle = 0;
	float Dout = 0;
	float Din = 0;      //±ê×¼¾ß¸ÉÉæÊ±µÄµÚÒ»¼¶ÑÜÉä»·DinºÍDout¼ÆËã
	float data[Length] = {0.0} ;
	FILE *fin;
	fin = fopen("C:\\data1.txt","r"); //¶ÁÈ¡²âµÃµÄÊı¾İÎÄ¼ş£¬Â·¾¶ÒªÏÈÖ¸Ã÷£¬²»È»¿ÉÄÜ¶ÁÈ¡ÎÄ¼ş³ö´í
	for(i=0;i<Length;i++)
	{
		fscanf(fin,"%f",&data[i]); //»ñµÃÎÄ¼şµÄÃ¿Ò»ĞĞµÄÊı¾İ
	}
	for(i=0;i<Length;i++)
		printf("%f\n",data[i]);      //Êä³öÊı×é£¬²¢²»ÊÇÈ«²¿µÄÊı¾İ£¬¿ÉÄÜÓëÏÔÊ¾·¶Î§ÓĞ¹Ø
	fclose(fin);
	float K = SetK(data); //ãĞÖµ
	FindPike(data,Pike,K); //¶ÔÊı×é¸³Öµ´Ó0¿ªÊ¼
	printf("ãĞÖµKµÄÖµ£º");
	printf("%f\n",K); 
	for(i=1;i<20;i++)
	 {
		 printf("µÚ%d¸ö¼â·åÎ»ÖÃ£º",i);
		 printf("%d\n",Pike[i]);
	}
   //Middle = FindMiddle(data,Pike,K);
   //printf("ÖĞÑëµã£º");
   //printf("%d\n",Middle);
   // FindFirst(data,&F1,&F2,Middle,K,Pike);
   FindFirst(&F1,&F2,Pike);
   printf("Ò»¼¶ÑÜÉä»·µÄÎ»ÖÃ£º\n");
   printf("%d ·åÖµ:%f\n",F1,data[F1]);
   printf("%d ·åÖµ:%f\n",F2,data[F2]);
   CalculatLameda(data,F1,F2,&Dout,&Din,K);
   printf("ÄÚ¾¶£º%f\n",Din);
   printf("Íâ¾¶£º%f\n",Dout);
   int end=GetTickCount();
   printf("³ÌĞòÔËĞĞºÄÊ±: %d ºÁÃë",end-start); //ÏÔÊ¾ÔËĞĞºÄÊ±£¬·½±ã¶Ô´¦ÀíËÙ¶È·ÖÎö
   getchar();
   return 0;
}

void FindPike(const float *data,int *Pike,const float K)
{
	int i ;
	int j ;
	int flag;             //×î´óÖµµÄ±ê¼Ç
	for(i=10;i<Length;i++)
	{
		flag=1;
		for(j= -10;j<11;j++)
		{
			if(data[i]<data[i+j]) 
			{
				flag = 0; //Èç¹ûÔÚÇø¼äÖĞ²»ÊÇ×î´óµÄ£¬Ìø³ö
				break;
			}
		}
		if(((flag==1) &&(data[i]>K))&&((i-*Pike)>=20))//ÅĞ¶Ï¸ß·åµã£¬Í¬Ê±ÏàÁÚµÄ¸ß·å¾àÀë²»ÄÜĞ¡ÓÚ20£¬Èç¹ûĞ¡ÓÚ¾ÍÓÃµÚÒ»¸öµÄÖµ
		{   
			++Pike; //ÎªÁË¼ÆËã·½±ã£¬µÚÒ»¸ö¼â·åµÄÎ»ÖÃÊÇ0
			*Pike=i;
		}
	}
}

float SetK(const float *data) //Éè¶¨ãĞÖµK
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

/*int FindMiddle(const float *data,const int *Pike,const float K) //¾É°æ±¾£¬ËÑÑ°ÖĞÑëµã
{
	int index ;//Éè¶¨³õÊ¼µÄËÑÑ°·¶Î§
	int Middle = 0;
	float FrontData = 0;
	float BehindData =0;
	float AbsData =0.0 ; //¾ø¶ÔÖµ
	float Temp = K*Length;
	for(int i = Pike[1]; i<Length ;i++)
	{
		if(data[i]<K) 
			{
				index = i; //¿¼ÂÇ°üÂçµÄÃæ»ıµÄ²»¶Ô³Æ¶È£¬ÊÇ·ñÒª¾ßÌå´¦Àí
				break;
		    }
	}

	for(i = index+1;i<Length;i++)
	{
		float FrontData = 0;   
		float BehindData =0 ; //¡Á¡Á¡Á×¢ÒâÑ­»·¿ªÊ¼ÏÈÖÃ0
		for(int j = index ; j<i ;j++)
		{
			FrontData += data[j];  //µãÇ°Ãæ»ı
		}
		for(j = i+1 ; j<Length ;j++)
		{
			BehindData += data[j]; //µãºóµÄÃæ»ı
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
			FrontData += data[j];  //µãÇ°Ãæ»ı
		}
		for(j = i+1 ; j<Length ;j++)
		{
			BehindData += data[j]; //µãºóµÄÃæ»ı
		}
		AbsData = ((FrontData - BehindData)>0)?(FrontData - BehindData):(BehindData - FrontData);//¾ø¶ÔÖµ
		if((AbsData-Temp)<1e-6)
		{
			Middle = i ;
		    break;
		}
	}
	printf("×î¶Ô³ÆµãÃæ»ı²îÖµ£º");
	printf("%f\n",Temp);
	printf("¿ªÊ¼ËÑÑ°µÄÎ»ÖÃ£º");
	printf("%d\n",index);
   return Middle;
}
*/
/*void FindFirst(const float *data,int *F1,int *F2,const int Middle,const float K,const int *Pike) //¾É°æ±¾µÄÕÒÒ»¼¶ÑÜÉä»·
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
		     *F2=Pike[i];                                  //ËÑÑ°µ½µÚÒ»¼¶ÑÜÉä¼â·å
		  }
	  }
	}
	else if(data[Middle]>K)
	{
		temp=Length;
		for(int i =1;i<19;i++)
		{
			AbsL=((Pike[i]-Middle)>0)?(Pike[i]-Middle):(Middle-Pike[i]);   //ÅĞ¶ÏµÚÒ»¼¶ÑÜÉä¼â·å
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

void CalculatLameda(const float *data,const int F1,const int F2,float *Dout,float *Din,const float K) //¼ÆËãÄÚ¾¶Íâ¾¶,×¢Òâ¸¡µãÊıÅĞ¶ÏµÄÎÊÌâ
{
	float D1 = 0;
	float D2 = 0;

	float middle1=0.5*(data[F1]+K);
	float middle2=0.5*(data[F2]+K);

	for(int i=F1;i<F2;i++)
	{
		
		if((data[i]>middle1)&&(data[i+1]<middle1))
		{
			D1 = i+(data[i]-middle1)/(data[i]-data[i+1]);  //´ÓF1´ÓF2ËÑÑ°
			break;
		}
	}
	for(i=F2 ;i>F1;i--)
	{
		if((middle2>data[i-1])&&(middle2<data[i]))
		{
			D2 = i+(middle2-data[i])/(data[i]-data[i-1]); //´ÓF2´ÓF1ËÑÑ°
			break;
		}
	}
	*Din = D2-D1;                                                 //¼ÆËãÄÚ¾¶

        for(i=F1;i>0;i--)
	{
		 if((middle1>data[i-1])&&(middle1<data[i]))
		{
			D1 = i+(middle1-data[i])/(data[i]-data[i-1]); //´Ó0µ½F1ËÑÑ°
			break;
		}
	}
	for(i=F2 ;i<Length;i++)
	{
		  if((data[i]>middle2)&&(data[i+1]<middle2))
		{
			D2 = i+(data[i]-middle2)/(data[i]-data[i+1]); //´ÓF2µ½1023ËÑÑ°
			break;
		}
	}
	*Dout = D2-D1;//Íâ¾¶
}