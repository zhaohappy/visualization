#include<iostream>
using namespace std;
void thinBoolBmp(int * data,int width,int height, bool f)//完成一次迭代
{
	 int count=0;
	 int b[5]={0};
	 int x[9]={0};

	 int h1=0;//代表X(H),等于1代表条件1满足
	 int n1=0,n2=0;
	 int h2=0,h3=0,h4=0;//分别代表其他条件是否满足
      for(int i=0;i<height;i++)//子区域1的迭代
	  {
		   for(int j=0;j<width;j++)
		   {
			   
               count=width*i+j;
			   if(data[count]==0){
                  continue; 
			   }
			   if((i-1)<0||(j-1)<0||(i+1)>=height||(j+1)>=width)
               {
				   continue;
			   }
               for(int v=0;v<5;v++)//初始化b[v]
			   {
                    b[v]=0;
			   }
			 
			    x[1]=data[(i-1)*width+j-1];
                x[2]=data[(i-1)*width+j];
				x[3]=data[(i-1)*width+j+1];
                x[4]=data[i*width+j+1];
				x[5]=data[(i+1)*width+j+1];
                x[6]=data[(i+1)*width+j];
				x[7]=data[(i+1)*width+j-1];
                x[8]=data[i*width+j-1];

			   for(int l=1;l<4;l++)
				 {
					if(x[2*l]==0&&(x[2*l+2]==1||x[2*l+1]==1))
					{
					    b[l]=1;
					}   
				 }
               if(x[8]==0&&(x[2]==1||x[1]==1))
			   {
				   b[4]=1;
			   } 
			   for(int k=1;k<5;k++)//计算出h1的值
			   {
				   h1+=b[k];
			   }
				for(k=1;k<5;k++)
				{
                    if(x[2*k-1]==1||x[2*k]==1)
					{
						 n1+=1;
					 }
				} 
				for(k=1;k<4;k++)
				{
                   if(x[2*k]==1||x[2*k+1]==1)
				   {
					  n2+=1;
				   }
				}
                if(x[8]==1||x[1]==1)  {n2+=1; }

				if(n1>n2) {n1=n2;}//选两者比较小的
				if(n1>=2&&n1<=3){ h2=1;} //计算h2的值
				if(f){
					 if(((x[2]||x[3]||(!x[5]))&&x[4])==0){
                      h3=1;
					}
				}
				else{
                  if(((x[6]||x[7]||(!x[1]))&&x[8])==0)
				  {
                      h3=1;
				  }
				}
				  if(h1==1&&h2==1&&h3==1)//最后判定是否要删除这个点
				  {
					// cout<<i<<" "<<j<<endl;
                     data[i*width+j]=0;
				  } 	  

			  
			      n1=0;
			      n2=0;
			      h1=0;
			      h2=0;
			      h3=0;
			      h4=0;
		   }
             
	}
}
