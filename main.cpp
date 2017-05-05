#include "stdafx.h"
#include "bmp.h"
#include "dilation.h"
#include "thin.h"
#include<iostream>
#include <fstream>
#include <stdlib.h>
#include "lable.h"
#include "sql.h"
#include "div.h"
#include "query.h"
#include "count.h"
using namespace std;
void prinfUsage(){
	cout<<"usage error!"<<endl
			<<"-e <source bmp> <destination bmp> .....................................................erosion"<<endl
			<<"-d <source bmp> <destination bmp> .....................................................dilation"<<endl
			<<"-t <source bmp> <destination bmp> .......................................................thin"<<endl
			<<"-i <source bmp> <destination bmp> ........................................................inverse"<<endl
			<<"-g <source bmp> <destination bmp> .......................................................gray"<<endl
			<<"-l <source bmp> <destination bmp> .........................................................lable"<<endl
			<<"-c ..............................................................................................................................  .count speed"<<endl
			<<"-sl <source bmp> .................................................................................................lable to sql"<<endl
			<<"-sd ...............................................................................................................................distence to sql"<<endl
			<<"-sa <source bmp> ................................................................................................all to sql"<<endl
			<<"-u <times> <source bmp> <destination bmp> ......................................broaden"<<endl
			<<"-b <threshold> <source gray bmp> <destination bool bmp> .........gray to bool"<<endl;
}
int main(int argc,char * argv[]){	
	if(argc<2){
		prinfUsage();
		return 0;
	}
	int i;
	char flag[4];
	strcpy(flag,argv[1]);

	if(flag[1]=='c'){
		if(argc!=2){
			prinfUsage();
			return 0;
		}
		else{
			countDay();
			return 0;
		}
	}

	if(flag[1]=='s' && flag[2]=='l'){
		if(argc!=3){
			prinfUsage();
				return 0;
			}
		else{
			BMP bmp;
			if(!bmp.readBmp(argv[2]))
			{
				cout<<"open file failed! the file must be .bmp "<<endl;
				return 0;
			}
			cout<<"source bmp info: width: "<<bmp.getWidth()<<" height: "<<bmp.getHeight()<<" bitCount: "<<bmp.getBitCount()<<endl;
			bmp.bmpToBool(255);
		    bmp.lableToBmp();
			queryLable(bmp.getLable(),bmp.getWidth(),bmp.getHeight());
			return 0;
		}
	}
	if(flag[1]=='s' && flag[2]=='a'){
		if(argc!=3){
			prinfUsage();
			return 0;
		}
		else{
			BMP bmp;
			if(!bmp.readBmp(argv[2]))
			{
				cout<<"open file failed! the file must be .bmp "<<endl;
				return 0;
			}
			cout<<"source bmp info: width: "<<bmp.getWidth()<<" height: "<<bmp.getHeight()<<" bitCount: "<<bmp.getBitCount()<<endl;
			bmp.bmpToBool(255);
			bmp.lableToBmp();
			queryAll(bmp.getLable(),bmp.getWidth(),bmp.getHeight());
			return 0;
		}
	}
	if(flag[1]=='s' && flag[2]=='d'){
		if(argc!=2){
			prinfUsage();
			return 1;
		}
		else{
			queryDistence();
			return 0;
		}
	}
	if(flag[1]=='b'){
		if(argc!=5){
			prinfUsage();
			return 0;
		}
		else{

			BMP bmp;
		
			if(!bmp.readBmp(argv[3]))
			{
				cout<<"open file failed! the file must be .bmp "<<endl;
				return 0;
			}
			cout<<"source bmp info: width: "<<bmp.getWidth()<<" height: "<<bmp.getHeight()<<" bitCount: "<<bmp.getBitCount()<<endl;
			bmp.grayToBool(atoi(argv[2]));
			bmp.saveBmp(argv[4],bmp.getBmpData(),bmp.getWidth(),bmp.getHeight(),bmp.getBitCount(),bmp.getColorTable());
			return 0;
		}
	}
	 if(flag[1]=='u'){
			if(argc!=5){
			prinfUsage();
			return 0;
		}
		else{

			BMP bmp;
		
			if(!bmp.readBmp(argv[3]))
			{
				cout<<"open file failed! the file must be .bmp "<<endl;
				return 0;
			}
			cout<<"source bmp info: width: "<<bmp.getWidth()<<" height: "<<bmp.getHeight()<<" bitCount: "<<bmp.getBitCount()<<endl;
			bmp.broaden(atoi(argv[2]));
			bmp.saveBmp(argv[4],bmp.getBmpData(),bmp.getWidth(),bmp.getHeight(),bmp.getBitCount(),bmp.getColorTable());
			return 0;
		}
	}
	else{
		if(argc!=4){
			prinfUsage();
			return 0;
		}
		else{

		BMP bmp;
		
		if(!bmp.readBmp(argv[2]))
		{
				cout<<"open file failed! the file must be .bmp "<<endl;
				return 0;
		}
		
		cout<<"source bmp info: width: "<<bmp.getWidth()<<" height: "<<bmp.getHeight()<<" bitCount: "<<bmp.getBitCount()<<endl;
		switch(flag[1]){
		case 'e':
			bmp.bmpToBool(255);//bmp数据转二值图像
			erosion(bmp.getBoolBmp(),bmp.getWidth(),bmp.getHeight());
			bmp.boolToBmp();//二值图像数据转bmp 24位数据
			break;
		case 'd':
			bmp.bmpToBool(255);
			dilation(bmp.getBoolBmp(),bmp.getWidth(),bmp.getHeight());
			bmp.boolToBmp();//二值图像数据转bmp 24位数据
			break;
		case 't':
			bmp.bmpToBool(255);
			for( i=0;i<7;i++){
				if(i%2==0)
					thinBoolBmp(bmp.getBoolBmp(),bmp.getWidth(),bmp.getHeight(),1);
				else
				    thinBoolBmp(bmp.getBoolBmp(),bmp.getWidth(),bmp.getHeight(),0);
			}	
			bmp.boolToBmp();//二值图像数据转bmp 24位数据
			break;
		case 'g':
			bmp.grayBmp();
			break;
		case 'i':
			bmp.inverse();
			break;
		case 'l':
			bmp.bmpToBool(255);
		    bmp.lableToBmp();
			break;
		}
		bmp.saveBmp(argv[3],bmp.getBmpData(),bmp.getWidth(),bmp.getHeight(),bmp.getBitCount(),bmp.getColorTable());
	}
	//存储处理后的图片
}

	cout<<"succeed!"<<endl;
    return 0;
}