#include "stdafx.h"
#include<math.h>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
//���ؽṹ������rgba��ֵ
  struct POIX{  
    unsigned char b;  
    unsigned char g;  
    unsigned char r;  
	unsigned char a;  
}; 

class BMP{
private:
	//���¸�ģ�������BMPͼ��(��ɫͼ����24bit RGB��8bit)�����ػ�ȡ
unsigned char **pBmpBuf;//����ͼ�����ݵ�ָ��

int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
RGBQUAD *pColorTable;//��ɫ��ָ��

int biBitCount;//ͼ�����ͣ�ÿ����λ��

POIX **pix; //ͼƬ������Ϣ��ָ��

int * boolBmp;//ͼƬ�Ķ�ֵ����ָ��

int *lable;//�洢�����ص��������

public:
	bool readBmp(char *bmpName) ;//��ȡbmp�ļ�����
	bool saveBmp(char *bmpName, unsigned char **imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);//�������ݵ�ͼƬ
	int getWidth();//��ȡͼƬ���
	int getHeight();//��ȡͼƬ�߶�
	RGBQUAD * getColorTable();//��ȡͼƬ��ɫ��
	int getBitCount();//��ȡͼƬλ���
	unsigned char ** getBmpData();//��ȡͼƬλͼ����
    void bmpToBool(int f);//��ͼƬתΪ��ֵͼ��fΪת����ֵ
	void boolToBmp();//����ֵ����ת��Ϊλͼ����
	int * getBoolBmp();//��ȡ��ֵ����
	void grayBmp();//��ͼƬ�ҶȻ�
	void grayToBool(int f);//�Ҷ�ͼƬת��ֵ
	void inverse();//��ͼƬ��ɫȡ��
	void lableToBmp();//���ݱ�Ŷ�ͼƬ������ɫ
	void broaden(int n);//�Ŵ�ͼƬ��nΪ�Ŵ���
	void pixToBmp();//��������ϢתΪbmp���ݸ�ʽ
	void bmpToPix();//��bmp����ת��Ϊ��������
	int * getLable();
	~BMP();
	BMP();
};
