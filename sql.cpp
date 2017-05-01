#include "stdafx.h"
#include "sql.h"
#include <iostream>
using namespace std;
//步骤1：添加对ADO的支持
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
