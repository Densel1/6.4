#pragma once
#include <string>
#include <iostream>
#include <pqxx/pqxx>


static enum st{ name, surename, email, telephone }s_type;

class clientDB
{
public:
	clientDB() {
	
	};


	void createTable(pqxx::work& tx);


	void insertTel(pqxx::work& tx, std::string sId, std::string sPhone);


	void insertData(pqxx::work& tx, std::string sId, std::string sName, std::string sSureName, std::string sEmail, std::string sPhone = "");


	void updateData(pqxx::work& tx, std::string sId, std::string sName, std::string sSureName, std::string sEmail);

	void deleteTel(pqxx::work& tx, std::string s);

	void deleteData(pqxx::work& tx, std::string s);

	void findClient(pqxx::work& tx, st col, std::string text);

private:
	std::string table1Name = "Person";
	std::string table2Name = "Telephone";
	std::string table3Name = "P_Tel";
	std::string name = "name";
	std::string surename = "surname";
	std::string email = "email";
	std::string phoneNum = "phoneNum";
	std::string id = "id";

};