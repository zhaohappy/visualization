#include "stdafx.h"
#include "dilation.h"
#include <malloc.h>
#include<string.h> 
//��ֵͼ�����ݸ�ʴ
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
                    //��������������һ��Ϊ0
                    //�򽫸õ���Ϊ0
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

//��ֵͼ������
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
                    //��������������һ��Ϊ255
                    //�򽫸õ���Ϊ255
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