#include <iostream>
#include <vector>
#include <string>
#include "table.h"



void clientDB::createTable(pqxx::work& tx)
{

	tx.exec("create table if not exists " + table1Name + "(id INTEGER PRIMARY KEY, " + name + " varchar not null, " + surename + " varchar not null, " + email + " varchar not null)");
	tx.exec("create table if not exists " + table2Name + "(" + phoneNum + " integer primary key)");
	tx.exec("create table if not exists " + table3Name + "(" + id + " integer references " + table1Name + "(id), " + phoneNum + " integer references " + table2Name + "(" + phoneNum + "), constraint pk primary key ("+ id + ", " + phoneNum +"))");
}

void clientDB::insertTel(pqxx::work& tx,  std::string sId, std::string sPhone)
{
	tx.exec("insert into " + table2Name + '(' + phoneNum + ") " + " values('" + tx.esc(sPhone) + "'); ");
	tx.exec("insert into " + table3Name + "(id, " + phoneNum + ") " + " values('" + tx.esc(sId) + "', '" + tx.esc(sPhone) + "'); ");
}

void clientDB::insertData(pqxx::work& tx, std::string sId, std::string sName, std::string sSureName, std::string sEmail, std::string sPhone)
{
	tx.exec("insert into " + table1Name + '(' + id + ", " + name + ", " + surename + ", " + email + ") " + " values('" + tx.esc(sId) + "', '" + tx.esc(sName) + "', '" + tx.esc(sSureName) + "', '" + tx.esc(sEmail) + "'); ");
	if (!sPhone.empty())
	{
			insertTel(tx, sId, sPhone);
	}
}

void clientDB::updateData(pqxx::work& tx, std::string sId, std::string sName, std::string sSureName, std::string sEmail)
{
	tx.exec("update " + table1Name + " SET name = '" + tx.esc(sName) + "' WHERE id = " + tx.esc(sId) + "; ");
	tx.exec("update " + table1Name + " SET surname = '" + tx.esc(sSureName) + "' WHERE id = " + tx.esc(sId) + "; ");
	tx.exec("update " + table1Name + " SET email = '" + tx.esc(sEmail) + "' WHERE id = " + tx.esc(sId) + "; ");
}

void clientDB::deleteTel(pqxx::work& tx, std::string s)
{
	tx.exec("delete from " + table3Name + " WHERE phoneNum = " + tx.esc(s));
	tx.exec("delete from " + table2Name + " WHERE phoneNum = '" + tx.esc(s) + "';");
}

void clientDB::deleteData(pqxx::work& tx, std::string s)
{
	std::vector<std::string> str;
	for (auto [tel_] : tx.query <std::string>("select phoneNum from " + table3Name + " WHERE " + id + " = " + tx.esc(s)))
	{
		str.push_back(tel_);
	}

	tx.exec("delete from " + table3Name + " WHERE id = " + tx.esc(s));
	tx.exec("delete from " + table1Name + " WHERE id = " + tx.esc(s));
	for (auto v : str)
	{
		deleteTel(tx, v);
	}
}

void clientDB::findClient(pqxx::work& tx, st col, std::string text)
{
	int id = 0, tel = 0;
	std::string type;
	switch (col)
	{
	case 0:
		type = name;
		break;
	case 1:
		type = surename;
		break;
	case 2:
		type = email;
		break;
	case 3:
		type = phoneNum;
		break;
	default:
		std::cout << "wrong client type" << std::endl;
	}

	if (type != phoneNum)
	{
		for (auto [id, name, surename, email] : tx.query <int, std::string, std::string, std::string>("select * from " + table1Name + " WHERE " + type + " LIKE '" + tx.esc(text) + "'"))
		{
			std::cout << id << " " << name << " " << surename << " " << email << std::endl;
		}
	}
	else if (type == phoneNum)
	{
		for (auto [id_, tel_] : tx.query <int, int>("select * from " + table3Name + " WHERE " + type + " = " + tx.esc(text) ))
		{
			id = id_;
			tel = tel_;
		}
		for (auto [id, name, surename, email] : tx.query <int, std::string, std::string, std::string>("select * from " + table1Name + " WHERE id = " + std::to_string(id)))
		{
			std::cout << id << " " << name << " " << surename << " " << email << " " << tel << std::endl;
		}
	}
}


