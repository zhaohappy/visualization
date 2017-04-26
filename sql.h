#include "stdafx.h"
#include <string>
using namespace std;

class SQL{
private:
	string database;
	string user;
	string password;
	string server;
	string port;
	_ConnectionPtr  pMyConnect;//�������Ӷ���ʵ�������� 
    _RecordsetPtr pRst;//�����¼������ʵ�������� 
	bool isRst;
public:
	SQL();
	SQL(string d,string u,string p,string s,string t);
	~SQL();
	int openSql();
	int closeSql();
	_RecordsetPtr getResult();
	int selectSql(string s);
	int updateSql(string s);
	void setDataBase(string s);
	void setUser(string s);
	void setPassWord(string s);
	void setServer(string s);
	void setPort(string s);
	string getDataBase();
	string getPassWord();
	string getUser();
	string getServer();
	string getPort();
};