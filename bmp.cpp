#include "stdafx.h"
#include "bmp.h"
#include "lable.h"
#include <math.h>

bool BMP:: readBmp(char *bmpName) 
{
	int i;
    FILE *fp=fopen(bmpName,"rb");//二进制读方式打开指定的图像文件

    if(fp==0)
        return 0;

    //跳过位图文件头结构BITMAPFILEHEADER

    fseek(fp, sizeof(BITMAPFILEHEADER),0);

    //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中

    BITMAPINFOHEADER head;  

    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	//获取图像宽、高、每像素所占位数等信息

    bmpWidth = head.biWidth;

    bmpHeight = head.biHeight;

    biBitCount = head.biBitCount;
   
	//灰度图像有颜色表，且颜色表表项为256

    if(biBitCount==8)
    {

        //申请颜色表所需要的空间，读颜色表进内存

        pColorTable=new RGBQUAD[256];

        fread(pColorTable,sizeof(RGBQUAD),256,fp);

    }
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	if(pBmpBuf==NULL){     //分配数据内存并置零
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
    fclose(fp);//关闭文件
    return 1;//读取文件成功
}

//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool BMP:: saveBmp(char *bmpName, unsigned char **imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

    //如果位图数据指针为0，则没有数据传入，函数返回

    if(!imgBuf)
        return 0;

    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0

    int colorTablesize=0;

    if(biBitCount==8)
        colorTablesize=1024;

    //待存储图像数据每行字节数为4的倍数

    int lineByte=(width * biBitCount/8+3)/4*4;

    //以二进制写的方式打开文件

    FILE *fp=fopen(bmpName,"wb");

    if(fp==0)
        return 0;

    //申请位图文件头结构变量，填写文件头信息

    BITMAPFILEHEADER fileHead;

    fileHead.bfType = 0x4D42;//bmp类型

    //bfSize是图像文件4个组成部分之和

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

    fileHead.bfReserved1 = 0;

    fileHead.bfReserved2 = 0;

    //bfOffBits是图像文件前3个部分所需空间之和

    fileHead.bfOffBits=54+colorTablesize;

    //写文件头进文件

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

    //申请位图信息头结构变量，填写信息头信息

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

    //写位图信息头进内存

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

    //如果灰度图像，有颜色表，写入文件 

    if(biBitCount==8)
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

    //写位图数据进文件

	for(int i=0;i<height;i++){
		fwrite(imgBuf[i], lineByte, 1, fp);
	}
    

    //关闭文件

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
			if(boolBmp[i*bmpWidth+j]==0){		//0代表白色背景
				pix[i][j].b=255;
				pix[i][j].g=255;
				pix[i][j].r=255;
			}
			else{							//1代表黑色像素
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
			if(pix[i][j].b>=f&&pix[i][j].g>=f&&pix[i][j].r>=f)//灰度>f的为白色，否则为黑色
				boolBmp[i*bmpWidth+j]=0;
			else
				boolBmp[i*bmpWidth+j]=1;
		}
	}
}
BMP::~BMP(){			//清理所有存放在堆中的内存
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
BMP::BMP(){		//初始化所有指针
	pBmpBuf=NULL;
	pColorTable=NULL;
	pix=NULL;
	boolBmp=NULL;
	lable=NULL;
}
void BMP::grayBmp(){
	int y,i,k;
	biBitCount=8;//图像位数更改为8位
	
//计算灰度图像数据
	 for( i=0;i<bmpHeight;i++){
		for( k=0;k<bmpWidth;k++){
			y=int((float)pix[i][k].r*0.299+(float)pix[i][k].g*0.587+(float)pix[i][k].b*0.114);
			pix[i][k].b=(unsigned char) y;
		//	pix[i][k].g=(unsigned char) y;
		}
	}
//处理调色板
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
	bmpToBool(f);//图像二值化
	biBitCount=8;//图像位数更改为8位
	//处理调色板
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
	//将各像素的rgba取反
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
	lable=Lable(boolBmp,bmpWidth,bmpHeight);//对区域进行编号

	for(i=0;i<bmpHeight;i++){			//获取区域编号的最大值
		for(j=0;j<bmpWidth;j++){
		  if(lable[i*bmpWidth+j]>max)
			  max=lable[i*bmpWidth+j];
		}
	}

	len = (pow((float)16,(int)6)-1)/max;       //计算颜色步长
	for(i=0;i<bmpHeight;i++){
		for(j=0;j<bmpWidth;j++){
			color=lable[i*bmpWidth+j]*len;  //计算当前区域编号对应的颜色

			c=color&255;           //取低8位数据为blue分量
			pix[i][j].b=c;
			color=color>>8;       //右移8位
			c=color&255;		 //取低8位数据为green分量
			pix[i][j].g=c;		
			color=color>>8;     //右移8位
			c=color&255;		//取低8位数据为red分量
			pix[i][j].r=c;    
		}
	}
	biBitCount=24;     //设置位长度为24位
	pixToBmp();

}
void BMP::pixToBmp(){
	int i,j,k;
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;//计算实际图像宽度

	if(pBmpBuf==NULL){     //分配数据内存并置零
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
		
	}//根据位宽度转换
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
	bmpWidth*=n;  //更改图像放大后的宽度和高度
	bmpHeight*=n;

	POIX **temp;  //临时pix指针
	int i,j,k,l;

	temp=new POIX*[bmpHeight]; //分配内存
	for( i=0;i<bmpHeight;i++){
		temp[i]=new POIX[bmpWidth];
	}
	for(i=0;i<bmpHeight/n;i++){ //遍历原像素数组，对其放大后的像素进行填充
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
	if(pix!=NULL){  //释放原pix指向的内存，并重新指向temp
		for(int i=0;i<bmpHeight/n;i++){
			delete []pix[i];
		}
		delete [] pix;
	}
	pix=temp;
	temp=NULL;  //temp置空
	pixToBmp();
}

void BMP::bmpToPix(){
	//申请位图数据所需要的空间，读位图数据进内存

	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
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