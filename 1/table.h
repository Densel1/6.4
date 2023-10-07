#pragma once
#include <string>
#include <iostream>
#include <pqxx/pqxx>

class clientDB
{
public:
	clientDB() {
	
	};


	void createTable(pqxx::work& tx, std::string table, std::string s);


	void insertData(pqxx::work& tx, std::string id, std::string phoneNum, std::string sId, std::string sPhone);


	void insertData(pqxx::work& tx, std::string id, std::string name, std::string surename, std::string email, std::string phonenumber, std::string sId, std::string sName, std::string sSureName, std::string sEmail, std::vector<std::string> sPhone);


	void updateData(pqxx::work& tx, std::string table, std::string s);


	void deleteData(pqxx::work& tx, std::string table, std::string s);

	void findClient(pqxx::work& tx, std::string table, std::string col, std::string text);

private:
	std::string T[3];

};