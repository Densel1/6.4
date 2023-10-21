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

	try {
		clientDB db;

		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=clients "
			"user=postgres "
			"password=111888v");

		pqxx::work transaction{ c };
		db.createTable(transaction);


    	db.insertData(transaction, "1", "Petr", "Petrov", "petr@ya", "14567361");
		db.insertData(transaction, "2", "Sergey", "Sergeev", "sergey@ya", "4657927");
		db.insertData(transaction, "4", "Ivan", "Ivanov", "ivan@ya", "57598756");
		db.insertData(transaction, "5", "Ivan", "Ivanov", "ivan@ya", "76746554");
		db.insertTel(transaction, "5", "3356683");
		db.insertData(transaction, "6", "Mihail", "Mihailov", "mixa@ya");


		db.updateData(transaction, "5", "Gregor", "Ivanov", "ivan@ya");
		db.deleteTel(transaction, "76746554");
		db.deleteData(transaction, "2");
		db.deleteData(transaction, "4");
		db.deleteTel(transaction, "3356683");
		db.deleteData(transaction, "1");

		db.findClient(transaction, name, "Mihail");
		db.findClient(transaction, telephone, "2346361");



		transaction.commit();
		    cout << "..." << endl;
	}
	catch(const std::exception &e)
	{
		std::cout << "Exception happened: " << e.what() << std::endl;
	}

	return 0;

}