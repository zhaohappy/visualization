#include "stdafx.h"
#include "dilation.h"
#include <malloc.h>
#include<string.h> 
//二值图像数据腐蚀
void erosion(int *data, int width, int height)
{
    int i, j, index, sum, flag; 
    sum = height * width * sizeof(int);
    int *tmpdata = (int*)malloc(sum);
    for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			tmpdata[i*width+j]=data[i*width+j];
		}
	}
    for(i = 2;i < height - 1;i++)
    {
        for(j = 2;j < width - 1;j++)
        {
            flag = 1;
            for(int m = i - 2;m < i + 2;m++)
            {
                for(int n = j - 2; n < j + 2;n++)
                {
                    //自身及领域中若有一个为0
                    //则将该点设为0
                    if(tmpdata[i * width + j] == 0
                        || tmpdata[m * width + n] == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                data[i * width + j] = 0;
            }
            else
            {
                data[i * width + j] = 1;
            }
        }
    }
    free(tmpdata);
}

//二值图像膨胀
void dilation(int* data, int width, int height)
{
    int i, j, index, sum, flag;
    sum = height * width * sizeof(int);
    int *tmpdata = (int*)malloc(sum);
    for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			tmpdata[i*width+j]=data[i*width+j];
		}
	}
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            flag = 1;
            for(int m = i-1 ;m < i + 2;m++)
            {
                for(int n = j-1 ; n < j + 2;n++)
                {
                    //自身及领域中若有一个为255
                    //则将该点设为255
                    if(tmpdata[i * width + j] == 1
                        || tmpdata[m * width + n] == 1)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                data[i * width + j] = 1;
            }
            else
            {
                data[i * width + j] = 0;
            }
        }
    }
    free(tmpdata);
}