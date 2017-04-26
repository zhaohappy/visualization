#include "stdafx.h"
#include "bmp.h"
#include "lable.h"
#include <math.h>

bool BMP:: readBmp(char *bmpName) 
{
	int i;
    FILE *fp=fopen(bmpName,"rb");//�����ƶ���ʽ��ָ����ͼ���ļ�

    if(fp==0)
        return 0;

    //����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER

    fseek(fp, sizeof(BITMAPFILEHEADER),0);

    //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��

    BITMAPINFOHEADER head;  

    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ

    bmpWidth = head.biWidth;

    bmpHeight = head.biHeight;

    biBitCount = head.biBitCount;
   
	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256

    if(biBitCount==8)
    {

        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�

        pColorTable=new RGBQUAD[256];

        fread(pColorTable,sizeof(RGBQUAD),256,fp);

    }
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	if(pBmpBuf==NULL){     //���������ڴ沢����
		pBmpBuf=new unsigned char* [bmpHeight];
		for( i=0;i<bmpHeight;i++){
			pBmpBuf[i]=new unsigned char[lineByte];
			memset(pBmpBuf[i],0,sizeof(unsigned char)*lineByte);
		}
	}
	else{
		for( i=0;i<bmpHeight;i++){
			memset(pBmpBuf[i],0,sizeof(unsigned char)*lineByte);
		}
	}
	for(i=0;i<bmpHeight;i++){
		fread(pBmpBuf[i],1,lineByte,fp);
	}
	bmpToPix();
    fclose(fp);//�ر��ļ�
    return 1;//��ȡ�ļ��ɹ�
}

//-----------------------------------------------------------------------------------------
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool BMP:: saveBmp(char *bmpName, unsigned char **imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

    //���λͼ����ָ��Ϊ0����û�����ݴ��룬��������

    if(!imgBuf)
        return 0;

    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0

    int colorTablesize=0;

    if(biBitCount==8)
        colorTablesize=1024;

    //���洢ͼ������ÿ���ֽ���Ϊ4�ı���

    int lineByte=(width * biBitCount/8+3)/4*4;

    //�Զ�����д�ķ�ʽ���ļ�

    FILE *fp=fopen(bmpName,"wb");

    if(fp==0)
        return 0;

    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ

    BITMAPFILEHEADER fileHead;

    fileHead.bfType = 0x4D42;//bmp����

    //bfSize��ͼ���ļ�4����ɲ���֮��

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

    fileHead.bfReserved1 = 0;

    fileHead.bfReserved2 = 0;

    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��

    fileHead.bfOffBits=54+colorTablesize;

    //д�ļ�ͷ���ļ�

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ

    BITMAPINFOHEADER head; 

    head.biBitCount=biBitCount;

    head.biClrImportant=0;

    head.biClrUsed=0;

    head.biCompression=0;

    head.biHeight=height;

    head.biPlanes=1;

    head.biSize=40;

    head.biSizeImage=lineByte*height;

    head.biWidth=width;

    head.biXPelsPerMeter=0;

    head.biYPelsPerMeter=0;

    //дλͼ��Ϣͷ���ڴ�

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

    //����Ҷ�ͼ������ɫ��д���ļ� 

    if(biBitCount==8)
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

    //дλͼ���ݽ��ļ�

	for(int i=0;i<height;i++){
		fwrite(imgBuf[i], lineByte, 1, fp);
	}
    

    //�ر��ļ�

    fclose(fp);

    return 1;

}

int BMP:: getWidth()
{
	return  bmpWidth;
}
int BMP:: getHeight()
{
	return bmpHeight;
}
RGBQUAD * BMP:: getColorTable()
{
	return pColorTable;
}
int BMP:: getBitCount()
{
	return biBitCount;
}
unsigned char **  BMP:: getBmpData(){

	return pBmpBuf;
}

void BMP::boolToBmp(){
	int i,j;
	for(i=0;i<bmpHeight;i++){
		for(j=0;j<bmpWidth;j++){
			if(boolBmp[i*bmpWidth+j]==0){		//0�����ɫ����
				pix[i][j].b=255;
				pix[i][j].g=255;
				pix[i][j].r=255;
			}
			else{							//1�����ɫ����
				pix[i][j].b=0;
				pix[i][j].g=0;
				pix[i][j].r=0;
			}
		}
	}

	pixToBmp();

}
int * BMP::getBoolBmp(){
	return boolBmp;
}
void BMP::bmpToBool(int f){
	boolBmp=new int[bmpWidth*bmpHeight];
    for(int i=0;i<bmpHeight;i++){
		for(int j=0;j<bmpWidth;j++){
			if(pix[i][j].b>=f&&pix[i][j].g>=f&&pix[i][j].r>=f)//�Ҷ�>f��Ϊ��ɫ������Ϊ��ɫ
				boolBmp[i*bmpWidth+j]=0;
			else
				boolBmp[i*bmpWidth+j]=1;
		}
	}
}
BMP::~BMP(){			//�������д���ڶ��е��ڴ�
	if(pBmpBuf!=NULL){
		for(int i=0;i<bmpHeight;i++){
			delete []pBmpBuf[i];
		}
		delete []pBmpBuf;
	}	
	if(pColorTable!=NULL)
		delete [] pColorTable;
	if(pix!=NULL){
		for(int i=0;i<bmpHeight;i++){
			delete []pix[i];
		}
		delete [] pix;
	}
	if(boolBmp!=NULL)
		delete [] boolBmp;
	if(lable!=NULL)
		delete []lable;
}
BMP::BMP(){		//��ʼ������ָ��
	pBmpBuf=NULL;
	pColorTable=NULL;
	pix=NULL;
	boolBmp=NULL;
	lable=NULL;
}
void BMP::grayBmp(){
	int y,i,k;
	biBitCount=8;//ͼ��λ������Ϊ8λ
	
//����Ҷ�ͼ������
	 for( i=0;i<bmpHeight;i++){
		for( k=0;k<bmpWidth;k++){
			y=int((float)pix[i][k].r*0.299+(float)pix[i][k].g*0.587+(float)pix[i][k].b*0.114);
			pix[i][k].b=(unsigned char) y;
		//	pix[i][k].g=(unsigned char) y;
		}
	}
//�����ɫ��
	 if(pColorTable==NULL){
		 pColorTable=new RGBQUAD[256];
		 for ( i = 0; i < 256; i++ )
			pColorTable[i].rgbRed = pColorTable[i].rgbGreen = pColorTable[i].rgbBlue = i;
	 }
	 else{
		for ( i = 0; i < 256; i++ )
			pColorTable[i].rgbRed = pColorTable[i].rgbGreen = pColorTable[i].rgbBlue = i;
	 }
	 pixToBmp();
}
void BMP::grayToBool(int f){
	int i;
	bmpToBool(f);//ͼ���ֵ��
	biBitCount=8;//ͼ��λ������Ϊ8λ
	//�����ɫ��
	 if(pColorTable==NULL){
		 pColorTable=new RGBQUAD[256];
		 for ( i = 0; i < 256; i++ )
			pColorTable[i].rgbRed = pColorTable[i].rgbGreen = pColorTable[i].rgbBlue = i;
	 }
	 else{
		for ( i = 0; i < 256; i++ )
			pColorTable[i].rgbRed = pColorTable[i].rgbGreen = pColorTable[i].rgbBlue = i;
	 }
	boolToBmp();
}
void BMP::inverse(){
	int i,j;
	//�������ص�rgbaȡ��
	for(i=0;i<bmpHeight;i++){
		for(j=0;j<bmpWidth;j++){
			pix[i][j].r=255-pix[i][j].r;
			pix[i][j].g=255-pix[i][j].g;
			pix[i][j].b=255-pix[i][j].b;
			pix[i][j].a=255-pix[i][j].a;
		}
	}

	pixToBmp();
}
void BMP::lableToBmp(){
	int i,j;
	int max=0;
	int len;
	int color;
	unsigned char c;
	lable=Lable(boolBmp,bmpWidth,bmpHeight);//��������б��

	for(i=0;i<bmpHeight;i++){			//��ȡ�����ŵ����ֵ
		for(j=0;j<bmpWidth;j++){
		  if(lable[i*bmpWidth+j]>max)
			  max=lable[i*bmpWidth+j];
		}
	}

	len = (pow((float)16,(int)6)-1)/max;       //������ɫ����
	for(i=0;i<bmpHeight;i++){
		for(j=0;j<bmpWidth;j++){
			color=lable[i*bmpWidth+j]*len;  //���㵱ǰ�����Ŷ�Ӧ����ɫ

			c=color&255;           //ȡ��8λ����Ϊblue����
			pix[i][j].b=c;
			color=color>>8;       //����8λ
			c=color&255;		 //ȡ��8λ����Ϊgreen����
			pix[i][j].g=c;		
			color=color>>8;     //����8λ
			c=color&255;		//ȡ��8λ����Ϊred����
			pix[i][j].r=c;    
		}
	}
	biBitCount=24;     //����λ����Ϊ24λ
	pixToBmp();

}
void BMP::pixToBmp(){
	int i,j,k;
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;//����ʵ��ͼ����

	if(pBmpBuf==NULL){     //���������ڴ沢����
		pBmpBuf=new unsigned char* [bmpHeight];
		for( i=0;i<bmpHeight;i++){
			pBmpBuf[i]=new unsigned char[lineByte];
			memset(pBmpBuf[i],0,sizeof(unsigned char)*lineByte);
		}
	}
	else{
		for( i=0;i<bmpHeight;i++){
			delete []pBmpBuf[i];
		}
		delete []pBmpBuf;
		pBmpBuf=new unsigned char* [bmpHeight];
		for( i=0;i<bmpHeight;i++){
			pBmpBuf[i]=new unsigned char[lineByte];
			memset(pBmpBuf[i],0,sizeof(unsigned char)*lineByte);
		}
		
	}//����λ���ת��
	for( i=0;i<bmpHeight;i++){
		if(biBitCount==32){
			for( j=0,k=0;k<bmpWidth;k++){
				pBmpBuf[i][j++]=pix[i][k].b;
				pBmpBuf[i][j++]=pix[i][k].g;
				pBmpBuf[i][j++]=pix[i][k].r;
				pBmpBuf[i][j++]=pix[i][k].a;
			 }
		 }
		if(biBitCount==24){
			for( j=0,k=0;k<bmpWidth;k++){
				pBmpBuf[i][j++]=pix[i][k].b;
				pBmpBuf[i][j++]=pix[i][k].g;
				pBmpBuf[i][j++]=pix[i][k].r;
			 }
		 }
		if(biBitCount==16){
			for( j=0,k=0;k<bmpWidth;k++){
				pBmpBuf[i][j++]=pix[i][k].b;
				pBmpBuf[i][j++]=pix[i][k].g;
			 }
		 }
		if(biBitCount==8){
			for( k=0;k<bmpWidth;k++){
				pBmpBuf[i][k]=pix[i][k].b;
			 }
		 }
	}
}
void BMP::broaden(int n){
	bmpWidth*=n;  //����ͼ��Ŵ��Ŀ�Ⱥ͸߶�
	bmpHeight*=n;

	POIX **temp;  //��ʱpixָ��
	int i,j,k,l;

	temp=new POIX*[bmpHeight]; //�����ڴ�
	for( i=0;i<bmpHeight;i++){
		temp[i]=new POIX[bmpWidth];
	}
	for(i=0;i<bmpHeight/n;i++){ //����ԭ�������飬����Ŵ������ؽ������
		for(j=0;j<bmpWidth/n;j++){
			for(k=0;k<n;k++){
				for(l=0;l<n;l++){
					temp[i*n+k][j*n+l].a=pix[i][j].a;
					temp[i*n+k][j*n+l].b=pix[i][j].b;
					temp[i*n+k][j*n+l].g=pix[i][j].g;
					temp[i*n+k][j*n+l].r=pix[i][j].r;
				}	
			}
		}
	}
	if(pix!=NULL){  //�ͷ�ԭpixָ����ڴ棬������ָ��temp
		for(int i=0;i<bmpHeight/n;i++){
			delete []pix[i];
		}
		delete [] pix;
	}
	pix=temp;
	temp=NULL;  //temp�ÿ�
	pixToBmp();
}

void BMP::bmpToPix(){
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�

	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;

	pix=new POIX*[bmpHeight];
		for(int m=0;m<bmpHeight;m++){
			pix[m]=new POIX[bmpWidth];
		}
   // unsigned char * rBmpBuf=new unsigned char[lineByte];
    unsigned char *tmpdata =new unsigned char[bmpWidth * biBitCount/8];
    for(int i=0;i<bmpHeight;i++){
		memcpy((char*)tmpdata, (char*)pBmpBuf[i], bmpWidth * biBitCount/8);
		if(biBitCount==24){
			for(int j=0,k=0;k<bmpWidth;k++){
			pix[i][k].b=tmpdata[j++];
			pix[i][k].g=tmpdata[j++];
			pix[i][k].r=tmpdata[j++];
			}
		}
		if(biBitCount==8){
			for(int k=0;k<bmpWidth;k++){
			pix[i][k].b=tmpdata[k];
			pix[i][k].g=tmpdata[k];
			pix[i][k].r=tmpdata[k];
			}
		}
		if(biBitCount==16){
			for(int j=0, k=0;k<bmpWidth;k++){
			pix[i][k].b=tmpdata[j++];
			pix[i][k].g=tmpdata[j++];
			pix[i][k].r=tmpdata[j];
			}
		}
		if(biBitCount==32){
			for(int j=0, k=0;k<bmpWidth;k++){
			pix[i][k].b=tmpdata[j++];
			pix[i][k].g=tmpdata[j++];
			pix[i][k].r=tmpdata[j++];
			pix[i][k].a=tmpdata[j++];
			}
		}
		
	}
   // delete []rBmpBuf;
	delete []tmpdata;
}
int * BMP::getLable(){
	return lable;
}