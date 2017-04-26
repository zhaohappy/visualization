#include "stdafx.h"
#include "sql.h"
#include <iostream>
using namespace std;
//步骤1：添加对ADO的支持
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

	string sa=s.substr(11,8);
	string ea=e.substr(11,8);

	int ss=0,es=0;
	
	ss=3600*(getNum(sa[0])*10+getNum(sa[1]))+60*(getNum(sa[3])*10+getNum(sa[4]))+getNum(sa[6])*10+getNum(sa[7]);

	es=3600*(getNum(ea[0])*10+getNum(ea[1]))+60*(getNum(ea[3])*10+getNum(ea[4]))+getNum(ea[6])*10+getNum(ea[7]);

	if((es-ss)%60)
		return (es-ss)/60;
	else
		return (int)((es-ss)/60)+1;
}

SQL::SQL(){
	 CoInitialize(NULL); //初始化COM环境       
	 pMyConnect.CreateInstance(__uuidof(Connection));
	 pRst.CreateInstance(__uuidof(Recordset));
}
SQL::SQL(string d,string u,string p,string s,string t){
	database=d;
	user=u;
	password=p;
	server=s;
	port=t;
	isRst=false;
	 CoInitialize(NULL); //初始化COM环境       
	 pMyConnect.CreateInstance(__uuidof(Connection));
	 pRst.CreateInstance(__uuidof(Recordset));
}
SQL::~SQL(){
	CoUninitialize(); //释放COM环境
}
int SQL::openSql(){
	string sqlt="Provider=SQLOLEDB; Server=";
	sqlt+=server+","+port+";"+"database="+database+";"+"uid="+user+";"+"pwd="+password+";";
	 try           
    {              
        //步骤2：创建数据源连接
        /*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */             
		pMyConnect->Open(sqlt.c_str(),"","",adModeUnknown);           
    } 
    catch (_com_error &e)           
    {               
         cout<<"Initiate failed!"<<endl;               
         cout<<e.Description()<<endl;               
         //cout<<e.HelpFile()<<endl;               
         return 0;           
    }           
    cout<<"Connect succeed!"<<endl;   
	return 1;
}
int SQL::closeSql(){
	try           
    {               
        pRst->Close();     //关闭记录集               
        pMyConnect->Close();//关闭数据库               
        pRst.Release();//释放记录集对象指针               
        pMyConnect.Release();//释放连接对象指针
    }
    catch(_com_error &e)           
    {            
		cout<<e.Description()<<endl; 
        cout<<"关闭失败！"<<endl;        
        return 0;           
    } 
	return 1;
}
int SQL::selectSql(string s){
	 try           
    {
		pRst = pMyConnect->Execute(s.c_str(),NULL,adCmdText);//执行SQL： select * from gendat          
        if(!pRst->BOF) 
        {
            pRst->MoveFirst(); 
			isRst=true;
        }               
        else
        {                    
            cout<<"Data is empty!"<<endl;                     
			isRst=false;      
        }               
          
    }
    catch(_com_error &e)           
    {  
		isRst=false;
		cout<<e.Description()<<endl; 
        cout<<"执行语句失败！"<<endl;       
        return 0;          
    }  
	return 1;
}
int SQL::updateSql(string s){

	try{
		pMyConnect->Execute(s.c_str(),NULL,adCmdText);
	}
	catch(_com_error &e)
	{          
		cout<<e.Description()<<endl; 
		cout<<"执行语句失败！"<<endl;    
		return 0;          
	}  
	return 1;
}
_RecordsetPtr SQL::getResult(){
	if(isRst)
		return pRst;
	else
		return NULL;
}
string SQL::getDataBase(){
  return database;
}
string SQL::getUser(){
  return user;
}
string SQL::getPassWord(){
  return password;
}
string SQL::getServer(){
  return server;
}
string SQL::getPort(){
  return port;
}
void SQL::setDataBase(string s){
	database=s;
}
void SQL::setUser(string s){
	user=s;
}
void SQL::setPassWord(string s){
	password=s;
}
void SQL::setServer(string s){
	server=s;
}
void SQL::setPort(string s){
	port=s;
}
