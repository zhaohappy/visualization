#include <string>  
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")  
class SQL{

private:
	string database;
	string user;
	string password;
	string server;
	string port;
	_ConnectionPtr pMyConnect;//定义连接对象并实例化对象 
    _RecordsetPtr pRst;//定义记录集对象并实例化对象 
public:
	SQL();
	~SQL();
	int openSql();
	void closeSql();
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