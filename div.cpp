#include "stdafx.h"
#include "div.h"
#include "lable.h"
#include<math.h>
#include<iostream>
using namespace std;
int getLabelForPoint(double lat,double lng,int * lable,int bmpWidth,int bmpHeight) //lat代表纬度，lng代表经度,lable为标号数组
{
     double startLat=31.1500000,endLat=31.3700000;
     double startLng=121.3100000,endLng=121.8400000;
	 int i=0,j=0;
     double pointLat=(endLat-startLat)*10000.0l/((bmpHeight)*1.0l);
     double pointLng=(endLng-startLng)*10000.0l/((bmpWidth)*1.0l);//扩大10000倍以减少误差
	 
	 i=floor((lng*10000.0l-startLng*10000.0l)/pointLng);
	 j=floor((lat*10000.0l-startLat*10000.0l)/pointLat);

	 if(i<0||i>=bmpWidth||j<0||j>=bmpHeight)
		 return -1;
	 else
		return lable[j*bmpWidth+i];
}