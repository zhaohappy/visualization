#include "stdafx.h"
#include "lable.h"
#include <iostream>
#include <string.h>

using namespace std;
//获取a,b,c,d中的非零最小值
int minLable(int a,int b,int c,int d,int l){
	int temp=l;
    if(a>0&&a<temp)
		temp=a;
	if(b>0&&b<temp)
		temp=b;
	if(c>0&&c<temp)
		temp=c;
	if(d>0&&d<temp)
		temp=d;
	return temp;
}
//获取划分区域数量
int getRegion(int * lable,int width,int height){
	int max=lable[0];
	int counter=0;
	int i,j,m,n;
	//获取区域编号的最大值
	for( i=0;i<height;i++){
		for( j=0;j<width;j++){
			if(lable[i*width+j]>max)
				max=lable[i*width+j];
		}
	}

	max++;//max加一

	int *flag=new int[max];
	memset(flag,0,sizeof(int)*max);
	for( i=0;i<height;i++){
		for( j=0;j<width;j++){
			flag[lable[i*width+j]]++;
		}
	}

    //将区域编号密集到低位
	for(i=0;i<max-1;i++){
		if(flag[i]==0){
			for(j=i+1;j<max-1;j++){
				if(flag[j]!=0)
					break;
			}
			for(m=0;m<height;m++){
				for(n=0;n<width;n++){
					if(lable[m*width+n]==j)
						lable[m*width+n]=i;
				}
			}
			flag[i]=flag[j];
			flag[j]=0;
		}
	}

	for(i=0;i<max;i++){
		if(flag[i]!=0){
			counter++;
		//	cout<<"区域 "<<i<<":"<<flag[i]<<endl;
		}
	}

	delete []flag;
	return counter;
}


int * Lable(int * data,int width,int height){

	cout<<"正在编号..."<<endl;

	int *lable=new int[width*height];

	memset(lable,0,sizeof(int)*width*height);

	int l=1,i,j;
    int x1,x2,x3,x4;
	int b1,b2,b3,b4;

	//left->right bottom->top 
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			//cout<<data[i*width+j];
			if(data[i*width+j]==0){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[i*width+j]=l++;
				else{
					lable[i*width+j]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//right->left bottom->top 
	for(i=0;i<height;i++){
		for(j=width-1;j>=0;j--){
			//cout<<data[i*width+j];
			if(data[i*width+j]==0){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[i*width+j]=l++;
				else{
					lable[i*width+j]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//left->right top->bottom 
	for(i=height-1;i>=0;i--){
		for(j=0;j<width;j++){
			//cout<<data[i*width+j];
			if(data[i*width+j]==0){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[i*width+j]=l++;
				else{
					lable[i*width+j]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//right->left top->bottom 
	for(i=height-1;i>=0;i--){
		for(j=width-1;j>=0;j--){
			//cout<<data[i*width+j];
			if(data[i*width+j]==0){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[i*width+j]=l++;
				else{
					lable[i*width+j]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	
    //bottom->top left->right
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			//cout<<data[i*width+j];
			if(data[j*width+i]==0){
				x1=j*width+i+1;
				x2=(j-1)*width+i;
				x3=j*width+i-1;
				x4=(j+1)*width+i;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[j*width+i]=l++;
				else{
					lable[j*width+i]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//bottom->top right->left
	for(i=0;i<width;i++){
		for(j=height-1;j>=0;j--){
			//cout<<data[i*width+j];
			if(data[j*width+i]==0){
				x1=j*width+i+1;
				x2=(j-1)*width+i;
				x3=j*width+i-1;
				x4=(j+1)*width+i;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[j*width+i]=l++;
				else{
					lable[j*width+i]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//top->bottom left->right
	for(i=width-1;i>=0;i--){
		for(j=0;j<height;j++){
			//cout<<data[i*width+j];
			if(data[j*width+i]==0){
				x1=j*width+i+1;
				x2=(j-1)*width+i;
				x3=j*width+i-1;
				x4=(j+1)*width+i;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[j*width+i]=l++;
				else{
					lable[j*width+i]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	//top->bottom right->left
	for(i=width-1;i>=0;i--){
		for(j=height-1;j>=0;j--){
			//cout<<data[i*width+j];
			if(data[j*width+i]==0){
				x1=j*width+i+1;
				x2=(j-1)*width+i;
				x3=j*width+i-1;
				x4=(j+1)*width+i;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[j*width+i]=l++;
				else{
					lable[j*width+i]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	} 
    //删除孤立像素点
	int x5,x6,x7,x8;
	int c1,c2,c3,c4;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			//cout<<data[i*width+j];
			if(data[i*width+j]==0){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0){
					x5=(i-1)*width+j-1;
					x6=(i-1)*width+j+1;
					x7=(i+1)*width+j-1;
					x8=(i+1)*width+j+1;
					if(x5<0||x5>=width*height)
						c1=0;
					else
						c1=lable[x5];
					if(x6<0||x6>=width*height)
						c2=0;
					else
						c2=lable[x6];
					if(x7<0||x7>=width*height)
						c3=0;
					else
						c3=lable[x7];
					if(x8<0||x8>=width*height)
						c4=0;
					else
						c4=lable[x8];

					lable[i*width+j]=minLable(c1,c2,c3,c4,l);
				}

			}

		}

	}
    //删除路径
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			//cout<<data[i*width+j];
			if(data[i*width+j]==1){
				x1=i*width+j+1;
				x2=(i-1)*width+j;
				x3=i*width+j-1;
				x4=(i+1)*width+j;

				if(x1<0||x1>=width*height)
					b1=0;
				else
					b1=lable[x1];
				if(x2<0||x2>=width*height)
					b2=0;
				else
					b2=lable[x2];
				if(x3<0||x3>=width*height)
					b3=0;
				else
					b3=lable[x3];
				if(x4<0||x4>=width*height)
					b4=0;
				else
					b4=lable[x4];

				if(b1==0&&b2==0&&b3==0&&b4==0)
					lable[i*width+j]=l++;
				else{
					lable[i*width+j]=minLable(b1,b2,b3,b4,l);
				}
			}

		}

	}
	cout<<"总区域数："<<getRegion(lable,width,height)<<endl;
    return lable;//返回编号数组
}