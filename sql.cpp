#include<iostream>
#include "sql.h"
//����1�����Ӷ�ADO��֧��
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
	 CoInitialize(NULL); //��ʼ��COM����           
     pMyConnect(__uuidof(Connection));//�������Ӷ���ʵ�������� 
     pRst(__uuidof(Recordset));//�����¼������ʵ��������  

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
        pMyConnect->Open(sqlt,"","",adModeUnknown);           
    } 
    catch (_com_error &e)           
    {               
         cout<<"Initiate failed!"<<endl;               
         //cout<<e.Description()<<endl;               
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
        cout<<"�ر�ʧ�ܣ�"<<endl;        
        return 0;           
    } 
	return 1;
}
int SQL::selectSql(string s){
	 try           
    {
        pRst = pMyConnect->Execute(_bstr_t(s),NULL,adCmdText);//ִ��SQL�� select * from gendat          
        if(!pRst->BOF) 
        {
            pRst->MoveFirst(); 
        }               
        else
        {                    
            cout<<"Data is empty!"<<endl;                     
            return 0;                
        }               
          
    }
    catch(_com_error &e)           
    {               
        cout<<"ִ�����ʧ�ܣ�"<<endl;       
        return 0;          
    }  
}
int SQL::updateSql(string s){

	try{
			pMyConnect->Execute(_bstr_t(s),NULL,adCmdText);
	}
	catch(_com_error &e)
	{               
		cout<<"ִ�����ʧ�ܣ�"<<endl;    
		return 0;          
	}  
	return 1;
}
_RecordsetPtr sql::getResult(){

	return pRst;

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