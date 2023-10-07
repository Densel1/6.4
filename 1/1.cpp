#include <iostream>
#include <string>
#include <vector>
#include "table.h"
#include <pqxx/pqxx>
#include <Windows.h>

using namespace std;


int main()
{

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	string table1Name = "Person";
	string table2Name = "Telephone";
	string table3Name = "P_Tel";
	string name = "name";
	string surename = "surname";
	string email = "email";
	string phoneNum = "phoneNum";
	string id = "id";

	try {
		clientDB db;

		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=clients "
			"user=postgres "
			"password=111888v");


		pqxx::work transaction{ c };
		db.createTable(transaction, table1Name, "id INTEGER PRIMARY KEY, " + name + " varchar not null, " + surename + " varchar not null, " + email + " varchar not null");
		db.createTable(transaction, table2Name, phoneNum + " integer primary key");
		db.createTable(transaction, table3Name, id + " integer references " + table1Name + "(id), " + phoneNum + " integer references " + table2Name + "(" + phoneNum + "), constraint pk primary key ("+ id + ", " + phoneNum +")");
		// vectors with phonenumbers
		vector<string> v{ "14567361","2346361","133461" };
		vector<string> v1;
		vector<string> v2{ "1456736","234636","13346" };

		db.insertData(transaction, id, name, surename, email, phoneNum, "1", "Petr", "Petrov", "petr@ya", v);
		db.insertData(transaction, id, name, surename, email, phoneNum, "2", "Sergey", "Sergeev", "sergey@ya", v1);
		db.insertData(transaction, id, name, surename, email, phoneNum, "4", "Ivan", "Ivanov", "ivan@ya", v2);

		db.updateData(transaction, table1Name, "SET name = 'Gregor' WHERE id = 1;");
		db.deleteData(transaction, table2Name, "WHERE phoneNum = '12324123'; ");
		db.deleteData(transaction, table3Name, "WHERE id = 4;");
		db.deleteData(transaction, table1Name, "WHERE id = 4;");

		db.findClient(transaction, table1Name, name, "Sergey");
		db.findClient(transaction, table3Name, phoneNum, "234636");


		transaction.commit();
		    cout << "..." << endl;
	}
	catch(const std::exception &e)
	{
		std::cout << "Exception happened: " << e.what() << std::endl;
	}



}