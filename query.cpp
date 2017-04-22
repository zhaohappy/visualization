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
int querySQL(int * lable,int bmpWidth,int bmpHeight){
	string d="Taxi_shanghai4_1";
	string u="menglin";
	string p="lml123456";
	string s="127.0.0.1";
	string t="1433";
	SQL sql(d,u,p,s,t);
	SQL sql2(d,u,p,s,t);
	sql.openSql();
	sql2.openSql();

	string query="select * from interval_li join displace_20150404 on interval_li.taxiid=displace_20150404.taxiid and interval_li.start_time = displace_20150404.vacant_starttime";
	sql.selectSql(query);
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
			string query2="update interval_li set lable1="+getStringByInt(l1)+",lable2="+getStringByInt(l2)+"where id="+id;

			sql2.updateSql(query2);
			cout<<lng1<<","<<lat1<<","<<l1<<","<<lng2<<","<<lat2<<","<<l2<<endl;
            pRst->MoveNext();                        
      }           
	sql.closeSql();
	return 1; 
}
