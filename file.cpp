#include "stdafx.h"
#include "file.h"
#include<fstream>
#include <iostream>
#include "include/json/json.h"
using namespace std;
#pragma comment(lib,"lib_json.lib")
void writeLable(char* path,int *lable,int width,int height){
	Json::Value jsonRoot;
	Json::Value jsonItem;
	int i,j;
	for( i=0;i<height;i++){
		for( j=0;j<width;j++){
			if(lable[i*width+j]!=0){
			jsonItem["x"] =j;
			jsonItem["y"] =i;
			jsonItem["lable"] = lable[i*width+j];
			jsonRoot.append(jsonItem);
			jsonItem.clear();
			}
		}
	}
	ofstream ofs;
	ofs.open(path);
	ofs<<jsonRoot.toStyledString();
	ofs.close();
}