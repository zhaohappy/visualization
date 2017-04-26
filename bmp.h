#include "stdafx.h"
#include<math.h>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
//像素结构，包括rgba的值
  struct POIX{  
    unsigned char b;  
    unsigned char g;  
    unsigned char r;  
	unsigned char a;  
}; 

class BMP{
private:
	//以下该模块是完成BMP图像(彩色图像是24bit RGB各8bit)的像素获取
unsigned char **pBmpBuf;//读入图像数据的指针

int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针

int biBitCount;//图像类型，每像素位数

POIX **pix; //图片像素信息的指针

int * boolBmp;//图片的二值数据指针

int *lable;//存储各像素点的区域编号

public:
	bool readBmp(char *bmpName) ;//读取bmp文件数据
	bool saveBmp(char *bmpName, unsigned char **imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);//保存数据到图片
	int getWidth();//获取图片宽度
	int getHeight();//获取图片高度
	RGBQUAD * getColorTable();//获取图片调色板
	int getBitCount();//获取图片位宽度
	unsigned char ** getBmpData();//获取图片位图数据
    void bmpToBool(int f);//将图片转为二值图像，f为转换阈值
	void boolToBmp();//将二值数据转换为位图数据
	int * getBoolBmp();//获取二值数据
	void grayBmp();//将图片灰度化
	void grayToBool(int f);//灰度图片转二值
	void inverse();//将图片颜色取反
	void lableToBmp();//根据编号对图片进行上色
	void broaden(int n);//放大图片，n为放大倍数
	void pixToBmp();//将像素信息转为bmp数据格式
	void bmpToPix();//将bmp数据转换为像素数据
	int * getLable();
	~BMP();
	BMP();
};
