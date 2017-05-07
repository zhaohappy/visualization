#include"stdafx.h"
#include"count.h"
#include"sql.h"
#include<iostream>
#include<sstream>
#include<math.h>
#include <fstream>
using namespace std;

string getStringByDouble2(double d){
	char str[100];
	sprintf(str,"%.10lf",d);
	return str;
}
string getString2(TCHAR *STR){
	int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);

	char* chRtn =new char[iLen*sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	string str(chRtn);

	return str;
}
string getStringByInt2(int n){
	stringstream newstr;
	newstr<<n;
	return newstr.str();
}
int countDay(){
	int i,j;
	string dataBase[16]={
		"Taxi_shanghai1_1",
		"Taxi_shanghai2_1",
		"Taxi_shanghai3_1",
		"Taxi_shanghai18_1",
		"Taxi_shanghai19_1",
		"Taxi_shanghai20_1",
		"Taxi_shanghai21_1",
		"Taxi_shanghai22_1",
		"Taxi_shanghai23_1",
		"Taxi_shanghai24_1",
		"Taxi_shanghai25_1",
		"Taxi_shanghai26_1",
		"Taxi_shanghai27_1",
		"Taxi_shanghai28_1",
		"Taxi_shanghai29_1",
		"Taxi_shanghai30_1"
	};
	for( i=0;i<16;i++){
		string filename="D:\\Menglin Li\\count\\"+dataBase[i]+"_speed"+".txt";
		FILE * fp=fopen(filename.c_str(),"w");

		string d=dataBase[i];
		string u="menglin";
		string p="lml123456";
		string s="127.0.0.1";
		string t="1433";
		
		double speed[48]={0.0};
		cout<<"ÕýÔÚ²éÑ¯£º"<<dataBase[i]<<endl;
		for( j=0;j<48;j++){
			SQL sql(d,u,p,s,t);
			if(sql.openSql()==0)
				continue;
			string query="select avg(speed) as speed from interval_li where lable_start >=0 and lable_end >=0 and lable_start != lable_end and speed>0.5 and lable_time="+getStringByInt2(j);
			if(!sql.selectSql(query))
				continue;
			_RecordsetPtr pRst=sql.getResult();
			if(pRst==NULL)
				return 0;
		   string sp;
			while(!pRst->adoEOF)               
			{    
				
				sp=getString2((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("speed")->Value);
			   pRst->MoveNext();                        
			}   
			speed[j]=atof(sp.c_str());
			sql.closeSql();
		}
		if(fp==0)
		{
			cout<<"open file error!"<<endl;
			break;
		}
		for(j=0;j<48;j++){
			string temp=getStringByInt2(j)+"	"+getStringByDouble2(speed[j])+"\n";
			fwrite(temp.c_str(),sizeof(char),temp.length(),fp);
		}
		fclose(fp);
	
	}
	return 1; 
}