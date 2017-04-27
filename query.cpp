#include"stdafx.h"
#include"query.h"
#include"sql.h"
#include"bmp.h"
#include"div.h"
#include<iostream>
#include <sstream>
using namespace std;



string getString(TCHAR *STR){
	 int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);

	char* chRtn =new char[iLen*sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	string str(chRtn);

	return str;
}
string getStringByInt(int n){
	stringstream newstr;
	newstr<<n;
	return newstr.str();
}

string getQuery(string s){
	string s1="select * from interval_li join ";
	string s2=" on interval_li.taxiid=";
	string s3=".taxiid and interval_li.start_time =";
	string s4=".vacant_starttime and interval_li.end_time=";
	string s5=".vacant_stoptime";
	return s1+s+s2+s+s3+s+s4+s+s5;
}

int querySQL(int * lable,int bmpWidth,int bmpHeight){

	string dataBase[7]={
	"Taxi_shanghai4_1",
	"Taxi_shanghai5_1",
	"Taxi_shanghai6_1",
	"Taxi_shanghai7_1",
	"Taxi_shanghai8_1",
	"Taxi_shanghai9_1",
	"Taxi_shanghai10_1"
	};

	string table[7]={
	"displace_20150404",
	"displace_20150405",
	"displace_20150406",
	"displace_20150407",
	"displace_20150408",
	"displace_20150409",
	"displace_20150410"
	};

	string u="menglin";
	string p="lml123456";
	string s="127.0.0.1";
	string t="1433";
	SQL sql;
	SQL sql2;
	sql.setPassWord(p);
	sql.setPort(t);
	sql.setServer(s);
	sql.setUser(u);
	sql2.setPassWord(p);
	sql2.setPort(t);
	sql2.setServer(s);
	sql2.setUser(u);

	for(int i=0;i<7;i++){
	string d=dataBase[i];

	sql.setDataBase(d);
	sql2.setDataBase(d);

	if(sql.openSql()==0||sql2.openSql()==0)
		continue;
	string query=getQuery(table[i]);
	if(!sql.selectSql(query))
		continue;

	cout<<"ÕýÔÚ²éÑ¯£º"<<dataBase[i]<<endl;

	_RecordsetPtr pRst=sql.getResult();
	if(pRst==NULL)
		return 0;
	if(lable==NULL)
		return 0;
	//string taxiid,start_time,end_time,interval,
	string lng1,lat1,lng2,lat2,id;
	int l1,l2;
	while(!pRst->adoEOF)               
     {    
            //taxiid=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("taxiid")->Value);
			//start_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("start_time")->Value);
			//end_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("end_time")->Value);
			id=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("id")->Value);
			lng1=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lng1")->Value);
			lat1=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lat1")->Value);
			lng2=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lng2")->Value);
			lat2=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lat2")->Value);
			l1=getLabelForPoint(atof(lat1.c_str()),atof(lng1.c_str()),lable,bmpWidth,bmpHeight);
			l2=getLabelForPoint(atof(lat2.c_str()),atof(lng2.c_str()),lable,bmpWidth,bmpHeight);
			string query2="update interval_li set lable_start="+getStringByInt(l1)+",lable_end="+getStringByInt(l2)+"where id="+id;

			sql2.updateSql(query2);
			cout<<lng1<<","<<lat1<<","<<l1<<","<<lng2<<","<<lat2<<","<<l2<<endl;
            pRst->MoveNext();                        
      }           
	sql.closeSql();
	sql2.closeSql();
	}
	return 1; 
}
