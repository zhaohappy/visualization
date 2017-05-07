#include"stdafx.h"
#include"query.h"
#include"sql.h"
#include"bmp.h"
#include"div.h"
#include<iostream>
#include<sstream>
#include<math.h>
//#include <Debug\msado15.tlh>
using namespace std;

const double EARTH_RADIUS=6378.004;
const double M_PI= 3.14159265358979323846;

int getNum(char c){

	int t;
	switch(c){
	case '0':
		t=0;
		break;
	case '1':
		t=1;
		break;
	case '2':
		t=2;
		break;
	case '3':
		t=3;
		break;
	case '4':
		t=4;
		break;
	case '5':
		t=5;
		break;
	case '6':
		t=6;
		break;
	case '7':
		t=7;
		break;
	case '8':
		t=8;
		break;
	case '9':
		t=9;
		break;
	}
	return t;
}
int getTime(string s,string e){

	string sa=s.substr(8,11);
	string ea=e.substr(8,11);

	int ss=0,es=0;
	int re;

	ss=24*3600*(getNum(sa[0])*10+getNum(sa[1]))+3600*(getNum(sa[3])*10+getNum(sa[4]))+60*(getNum(sa[6])*10+getNum(sa[7]))+getNum(sa[9])*10+getNum(sa[10]);

	es=24*3600*(getNum(ea[0])*10+getNum(ea[1]))+3600*(getNum(ea[3])*10+getNum(ea[4]))+60*(getNum(ea[6])*10+getNum(ea[7]))+getNum(ea[9])*10+getNum(ea[10]);

	//cout<<ss<<" "<<es<<endl;
	if((es-ss)%60==0)
		re= (es-ss)/60;
	else
		re= (es-ss)/60+1;
	//cout<<re<<endl;
	return re;
}

double red(double d){
	return d*M_PI/180.0;
}
double getDistence(double lat1,double lng1, double lat2,double lng2){
	double redLat1=red(lat1);
	double redLat2=red(lat2);
	double a=redLat1-redLat2;
	double b=red(lng1)-red(lng2);
	double s = 2 * asin(sqrt(pow(sin(a/2),2) +cos(redLat1)*cos(redLat2)*pow(sin(b/2),2)));
	s=s*EARTH_RADIUS;
	//s=(s*10000)/10000;
	return s;
}


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
string getStringByDouble(double d){
	char str[100];
	sprintf(str,"%.10lf",d);
	return str;
}
string getQuery(string s){
	string s1="select * from interval_li join ";
	string s2=" on interval_li.taxiid=";
	string s3=".taxiid and interval_li.start_time =";
	string s4=".vacant_starttime and interval_li.end_time=";
	string s5=".vacant_stoptime";
	return s1+s+s2+s+s3+s+s4+s+s5;
}

string getQueryALL(string s){
	string s1="select * from ";
	return s1+s;
}
int getTImeLable(string s,string e){
	int lable=0;
	int ss=0;
	string sa=s.substr(8,11);
	ss=60*(getNum(sa[3])*10+getNum(sa[4]))+(getNum(sa[6])*10+getNum(sa[7]));
	lable=ss/30;

	return lable;
}

int queryLable(int * lable,int bmpWidth,int bmpHeight){

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
	"displace_final_20150404",
	"displace_final_20150405",
	"displace_final_20150406",
	"displace_final_20150407",
	"displace_final_20150408",
	"displace_final_20150409",
	"displace_final_20150410"
	};
	for(int i=0;i<7;i++){
	string d=dataBase[i];
	string u="menglin";
	string p="lml123456";
	string s="127.0.0.1";
	string t="1433";
	SQL sql(d,u,p,s,t);
	SQL sql2(d,u,p,s,t);
	
	if(sql.openSql()==0||sql2.openSql()==0)
		continue;
	string query=getQuery(table[i]);
	if(!sql.selectSql(query))
		continue;
	cout<<"正在查询："<<dataBase[i]<<endl;
	_RecordsetPtr pRst=sql.getResult();
	if(pRst==NULL)
		return 0;
	if(lable==NULL)
		return 0; 
	//string taxi id,start_time,end_time,interval,
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
	//sql2.closeSql();
	}
	return 1; 
}
int queryDistence(){
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
		"displace_final_20150404",
		"displace_final_20150405",
		"displace_final_20150406",
		"displace_final_20150407",
		"displace_final_20150408",
		"displace_final_20150409",
		"displace_final_20150410"
	};
	for(int i=0;i<7;i++){
		string d=dataBase[i];
		string u="menglin";
		string p="lml123456";
		string s="127.0.0.1";
		string t="1433";
		SQL sql(d,u,p,s,t);
		SQL sql2(d,u,p,s,t);

		if(sql.openSql()==0||sql2.openSql()==0)
			continue;
		string query=getQuery(table[i]);
		if(!sql.selectSql(query))
			continue;
		cout<<"正在查询："<<dataBase[i]<<endl;
		_RecordsetPtr pRst=sql.getResult();
		if(pRst==NULL)
			return 0;
		//string taxi id,start_time,end_time,interval,
		string lng1,lat1,lng2,lat2,id,start_time,end_time,interval;
		double distence,speed;
		int time_lable;
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
			start_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("start_time")->Value);
			end_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("end_time")->Value);
			interval=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("interval")->Value);

			distence = getDistence(atof(lat1.c_str()),atof(lng1.c_str()),atof(lat2.c_str()),atof(lng1.c_str()))+getDistence(atof(lat1.c_str()),atof(lng1.c_str()),atof(lat1.c_str()),atof(lng2.c_str()));
			time_lable=getTImeLable(start_time,end_time);
			speed=distence/(atoi(interval.c_str()))*60.0;
			//distence = getDistence(atof(lat1.c_str()),atof(lng1.c_str()),atof(lat2.c_str()),atof(lng2.c_str()));
			string query2="update interval_li set displace="+getStringByDouble(distence)+",speed="+getStringByDouble(speed)+",lable_time="+getStringByInt(time_lable)+" where id="+id;

			sql2.updateSql(query2);
			cout<<setprecision(10)<<atof(lng1.c_str())<<","<<lat1<<","<<lng2<<","<<lat2<<",   "<<getStringByDouble(distence)<<endl;
			pRst->MoveNext();                        
		}           
		sql.closeSql();
		//sql2.closeSql();
	}
	return 1; 
}
int queryAll(int * lable,int bmpWidth,int bmpHeight){
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

	string table[16]={
		"displace_final_20150401",
		"displace_final_20150402",
		"displace_final_20150403",
		"displace_final_20150418",
		"displace_final_20150419",
		"displace_final_20150420",
		"displace_final_20150421",
		"displace_final_20150422",
		"displace_final_20150423",
		"displace_final_20150424",
		"displace_final_20150425",
		"displace_final_20150426",
		"displace_final_20150427",
		"displace_final_20150428",
		"displace_final_20150429",
		"displace_final_20150430"
	};
	string lng1,lat1,lng2,lat2,id;
	double distence,speed;
	string taxiid,start_time,end_time,vacant;
	int interval;
	int lable_time;
	int lable_start,lable_end;
	string sr="',";
	string sl="'";
	string u="menglin";
	string p="lml123456";
	string s="127.0.0.1";
	string t="1433";
	string query;
	_RecordsetPtr pRst;
	for(int i=0;i<16;i++){
		SQL sql(dataBase[i],u,p,s,t);
		//SQL sql2(dataBase[i],u,p,s,t);
		if(sql.openSql()==0)
			continue;
		if(!sql.selectSql(getQueryALL(table[i])))
			continue;
		cout<<"正在查询："<<dataBase[i]<<endl;
		 pRst=sql.getResult();
		if(pRst==NULL)
			return 0;
		while(!pRst->adoEOF)               
		{    
			vacant=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("vacant")->Value);
			if(vacant[0]=='1'){
				lng1=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lng1")->Value);
				lat1=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lat1")->Value);
				lng2=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lng2")->Value);
				lat2=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("lat2")->Value);
				taxiid=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("taxiid")->Value);
				start_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("vacant_starttime")->Value);
				end_time=getString((TCHAR *)(_bstr_t)pRst->GetFields()->GetItem("vacant_stoptime")->Value);

				interval=getTime(start_time,end_time);
				distence = getDistence(atof(lat1.c_str()),atof(lng1.c_str()),atof(lat2.c_str()),atof(lng1.c_str()))+getDistence(atof(lat1.c_str()),atof(lng1.c_str()),atof(lat1.c_str()),atof(lng2.c_str()));
				speed=distence/interval*60.0;
				lable_start=getLabelForPoint(atof(lat1.c_str()),atof(lng1.c_str()),lable,bmpWidth,bmpHeight);
				lable_end=getLabelForPoint(atof(lat2.c_str()),atof(lng2.c_str()),lable,bmpWidth,bmpHeight);
				lable_time=getTImeLable(start_time,end_time);
				query="insert into interval_li values("+sl+taxiid+sr+sl+start_time+sr+sl+end_time+sr+getStringByInt(interval)+","+getStringByDouble(distence)+","+getStringByDouble(speed)+","+getStringByInt(lable_start)+","+getStringByInt(lable_end)+","+getStringByInt(lable_time)+")";
				sql.updateSql(query);
				cout<<lng1<<","<<lat1<<","<<lng2<<","<<lat2<<",   "<<getStringByDouble(distence)<<endl;
			}
			pRst->MoveNext();                        
		}
		sql.closeSql();
		//sql2.closeSql();
	}
	return 1; 
}

