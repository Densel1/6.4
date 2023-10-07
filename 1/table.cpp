#include <iostream>
#include <vector>
#include <string>
#include "table.h"



void clientDB::createTable(pqxx::work& tx, std::string table, std::string s)
{
	static int i;
	T[i] = table;
	i++;
	tx.exec("create table if not exists " + table + "(" + s + ")");
}

void clientDB::insertData(pqxx::work& tx, std::string id, std::string phoneNum, std::string sId, std::string sPhone)
{
	tx.exec("insert into " + T[1] + '(' + phoneNum + ") " + " values('" + sPhone + "'); ");
	tx.exec("insert into " + T[2] + "(id, " + phoneNum + ") " + " values('" + sId + "', '" + sPhone + "'); ");
}

void clientDB::insertData(pqxx::work& tx, std::string id, std::string name, std::string surename, std::string email, std::string phonenumber, std::string sId, std::string sName, std::string sSureName, std::string sEmail, std::vector<std::string> sPhone)
{
	tx.exec("insert into " + T[0] + '(' + id + ", " + name + ", " + surename + ", " + email + ") " + " values('" + sId + "', '" + sName + "', '" + sSureName + "', '" + sEmail + "'); ");
	if (!sPhone.empty())
	{
		for (auto& m : sPhone) {
			insertData(tx, id, phonenumber, sId, m);
		}
	}
}

void clientDB::updateData(pqxx::work& tx, std::string table, std::string s)
{
	tx.exec("update " + table + " " + s);
}

void clientDB::deleteData(pqxx::work& tx, std::string table, std::string s)
{
	tx.exec("delete from " + table + " " + s);
}

void clientDB::findClient(pqxx::work& tx, std::string table, std::string col, std::string text)
{
	int id = 0, tel = 0;
	if (table == T[0])
	{
		for (auto [id, name, surename, email] : tx.query <int, std::string, std::string, std::string>("select * from " + T[0] + " WHERE " + col + " LIKE '" + text + "'"))
		{
			std::cout << id << " " << name << " " << surename << " " << email << std::endl;
		}
	}
	else if (table == T[2])
	{
		for (auto [id_, tel_] : tx.query <int, int>("select * from " + T[2] + " WHERE " + col + " = " + text ))
		{
			id = id_;
			tel = tel_;
		}
		for (auto [id, name, surename, email] : tx.query <int, std::string, std::string, std::string>("select * from " + T[0] + " WHERE id = " + std::to_string(id)))
		{
			std::cout << id << " " << name << " " << surename << " " << email << " " << tel << std::endl;
		}
	}
}


