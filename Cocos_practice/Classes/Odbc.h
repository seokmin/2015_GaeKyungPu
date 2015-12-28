#pragma once
#include "sql.h"
#include "sqlext.h"

class Odbc
{
public:
	static Odbc* _Inst;
	static Odbc* Odbc::GetInstance();

	std::string		Connect(wchar_t* odbcName, wchar_t* mysqlId, wchar_t* password);
	void			Disonnect();

	std::string		CheckDataExist(std::string tableName, std::string colName, std::string value);
	std::string		SelectData(std::string tableName, std::string colNames, bool whereCon, std::string whereCol, std::string value);
	bool			PushQuery(std::wstring query);
	
	void			ReadFileAndInsert(const char *path);
	void			CheckSuccess(int ret);
	
	const char*		CreateCSV(const char* filename, int num);
	void			SelectBookData();
	
	std::wstring	utf8_to_wstring(const std::string& str);
	std::string		wstring_to_utf8(const std::wstring& str);

private:
	Odbc();
	~Odbc();

	bool		_IsConnect = false;
	SQLHENV		_hEnv;
	SQLHDBC		_hDbc;
	SQLHSTMT	_hStmt;
};