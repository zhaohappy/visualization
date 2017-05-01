#include "stdafx.h"
#include "sql.h"
#include <iostream>
using namespace std;
//����1����Ӷ�ADO��֧��
SQL::SQL(){
	 CoInitialize(NULL); //��ʼ��COM����       
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
	 CoInitialize(NULL); //��ʼ��COM����       
	 pMyConnect.CreateInstance(__uuidof(Connection));
	 pRst.CreateInstance(__uuidof(Recordset));
}
SQL::~SQL(){
	CoUninitialize(); //�ͷ�COM����
}
int SQL::openSql(){
	string sqlt="Provider=SQLOLEDB; Server=";
	sqlt+=server+","+port+";"+"database="+database+";"+"uid="+user+";"+"pwd="+password+";";
	 try           
    {              
        //����2����������Դ����
        /*�����ݿ⡰SQLServer����������Ҫ�����Լ�PC�����ݿ����� */             
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
        pRst->Close();     //�رռ�¼��               
        pMyConnect->Close();//�ر����ݿ�               
        pRst.Release();//�ͷż�¼������ָ��               
        pMyConnect.Release();//�ͷ����Ӷ���ָ��
    }
    catch(_com_error &e)           
    {            
		cout<<e.Description()<<endl; 
        cout<<"�ر�ʧ�ܣ�"<<endl;        
        return 0;           
    } 
	return 1;
}
int SQL::selectSql(string s){
	 try           
    {
		pRst = pMyConnect->Execute(s.c_str(),NULL,adCmdText);//ִ��SQL�� select * from gendat          
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
        cout<<"ִ�����ʧ�ܣ�"<<endl;       
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
		cout<<"ִ�����ʧ�ܣ�"<<endl;    
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
