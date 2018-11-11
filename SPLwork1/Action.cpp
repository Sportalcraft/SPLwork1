#ifndef BASEACTION_H_
#define BASEACTION_H_

#include "Action.h"
#include "Restaurant.h"
#include <vector>



BaseAction::BaseAction() : status(PENDING), errorMsg("")
{
}

BaseAction::~BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
	return status;
}

void BaseAction::complete()
{
	status = COMPLETED;
}

void BaseAction::error(std::string errorMsg)
{
	status = ERROR;
	this->errorMsg = errorMsg;
}

std::string BaseAction::getErrorMsg() const
{
	return errorMsg;
}

std::string BaseAction::getErrorToString() const
{
	if(getStatus() == COMPLETED)
		return "Completed";

	if (getStatus() == ERROR)
		return getErrorMsg();

	return std::string();
}

OpenTable::OpenTable(int id, std::vector<Customer*>& customersList) :BaseAction(), tableId(id), customers(customersList)
{
}

OpenTable::~OpenTable()
{
	//delete customers
	for each (Customer* cus in customers)
		delete& cus;
}

void OpenTable::act(Restaurant & restaurant)
{
	Table* table;

	try
	{
		table = restaurant.getTable(tableId);

		if (table->isOpen()) // table must be open
			throw std::exception("Table is close!");

		//Add customers
		for each (Customer* cus in customers)
			table->addCustomer(cus);

		complete(); // action excecuted succesfully

	}
	catch (const std::exception&)
	{
		error("Table does not exist or is already open");
	}

	//if (table != nullptr)
	//	delete& table; // delete the table at the end
}

//BaseAction * OpenTable::clone() const
//{
//	return nullptr;
//}

std::string OpenTable::toString() const
{
	std::string customersString = "";

	for each (Customer* cus in customers)
		customersString += cus->toString() + " ";
	
	return "open " + std::to_string(tableId) + " " + customersString + getErrorToString();
}

Order::Order(int id) : BaseAction(), tableId(id)
{
}

Order::~Order()
{
}

void Order::act(Restaurant & restaurant)
{
	Table* table;
	std::vector<OrderPair> order;

	try
	{
		table = restaurant.getTable(tableId);

		if (!table->isOpen()) // table must be opem
			throw std::exception("table is close!");

		table->order(restaurant.getMenu());
		order = table->getOrders(); // already print to screen

		complete(); // action excecuted succesfully
	}
	catch (const std::exception&)
	{
		//Table no found
		error("Table does not exist or is not open");
	}
		
	//if(table != nullptr)
	//	delete& table; // delete the table at the end
}

//BaseAction * Order::clone() const
//{
//	return nullptr;
//}

std::string Order::toString() const
{
	return "order " + getErrorToString();
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) :BaseAction(), srcTable(src), dstTable(dst), id(customerId)
{
}

MoveCustomer::~MoveCustomer()
{
}

void MoveCustomer::act(Restaurant & restaurant)
{
	std::vector<OrderPair> customerOrder;

	Table* sorce;
	Table* destenation;
	Customer* customer = nullptr;
	std::vector<OrderPair> customerOrders;

	try
	{
		sorce = restaurant.getTable(srcTable);
		destenation = restaurant.getTable(dstTable);
		customer = sorce->getCustomer(id);
		destenation->addCustomer(customer);
		customerOrders = sorce->getRemoveOrdersOfCustomer(id);
		sorce->removeCustomer(id);
		destenation->addOrders(customerOrders);

		complete(); // action excecuted succesfully
	}
	catch (const std::exception&)
	{
		error("Cannot move customer");
	}

	//if (sorce != nullptr)
	//	delete& sorce;

	//if (destenation != nullptr)
	//	delete& destenation;

	if (customer != nullptr)
		delete& customer;
}

//BaseAction * MoveCustomer::clone() const
//{
//	return nullptr;
//}

std::string MoveCustomer::toString() const
{
	return "Move " + std::to_string(srcTable) + " " + std::to_string(dstTable) + " " + std::to_string(id) + " " + getErrorToString();
}

Close::Close(int id) :BaseAction(), tableId(id)
{
}

void Close::act(Restaurant & restaurant)
{
	Table* table;
	int bill;

	try
	{
		table = restaurant.getTable(tableId);

		if (!table->isOpen()) // table must be open
			throw std::exception("table is close!");

		bill = table->getBill();
		table->closeTable();

		std::cout << std::string("Table ") +std::to_string(tableId) + " was closed. Bill " + std::to_string(bill) + "NIS" << std::endl;

		complete(); // action excecuted succesfully
	}
	catch (const std::exception&)
	{
		//Table no found
		error("Table does not exist or is not open");
	}

	//if(table != nullptr)
	//	delete& table; // delete the table at the end
}

Close::~Close()
{
}

//BaseAction * Close::clone() const
//{
//	return nullptr;
//}

std::string Close::toString() const
{
	return "close " + std::to_string(tableId) + " " + getErrorToString();
}

CloseAll::CloseAll() : BaseAction()
{
}

CloseAll::~CloseAll()
{
}

void CloseAll::act(Restaurant & restaurant)
{
	int numOfTables = restaurant.getNumOfTables();

	for (int i = 0; i < numOfTables; i++)
	{
		Close closeAc(i);
		closeAc.act(restaurant);
	}

	complete();
}

//BaseAction * CloseAll::clone() const
//{
//	return nullptr;
//}

std::string CloseAll::toString() const
{
	return "closeall " + getErrorToString();
}

PrintMenu::PrintMenu() : BaseAction()
{
}

PrintMenu::~PrintMenu()
{
}

void PrintMenu::act(Restaurant & restaurant)
{
	std::string types[4] = { "VEG", "SPC", "BVG", "ALC" };

	for each (Dish dish in restaurant.getMenu())	
		std::cout << dish.getName() + " " + types[dish.getType()] + " " + std::to_string(dish.getPrice()) << std::endl;
}

//BaseAction * PrintMenu::clone() const
//{
//	return nullptr;
//}

std::string PrintMenu::toString() const
{
	return "menu " + getErrorToString();
}

PrintTableStatus::PrintTableStatus(int id) : BaseAction(), tableId(id)
{
}

PrintTableStatus::~PrintTableStatus()
{
}

void PrintTableStatus::act(Restaurant & restaurant)
{
	Table* table;
	std::string* status = nullptr;

	try
	{
		table = restaurant.getTable(tableId);

		if (table->isOpen())
			status = new std::string("Open");
		else
			status = new std::string("closed");

		//print statuse
		std::cout << "Table " + std::to_string(tableId) + " status: " + *status << std::endl;

		if (table->isOpen()) // there is customers in it
		{
			//print customers
			for each (Customer* cus in table->getCustomers())
				std::cout << std::to_string(cus->getId()) + " " + cus->getName() << std::endl;

			//print orders
			for each (OrderPair pair in table->getOrders())
				std::cout << pair.second.getName() + " " + std::to_string(pair.second.getPrice()) + "NIS " + std::to_string(pair.first) << std::endl;

			//print bill
			std::cout << "Current bill: " + table->getBill() + std::string("NIS") << std::endl;
		}

	}
	catch (const std::exception&) {}

	//if (table != nullptr)
	//	delete& table;

	if (status != nullptr)
		delete& status;
}

//BaseAction * PrintTableStatus::clone() const
//{
//	return nullptr;
//}

std::string PrintTableStatus::toString() const
{
	return "status " + std::to_string(tableId) + " " + getErrorToString();
}

PrintActionsLog::PrintActionsLog() : BaseAction()
{
}

PrintActionsLog::~PrintActionsLog()
{
}

void PrintActionsLog::act(Restaurant & restaurant)
{
	//print all actions
	for each (BaseAction* act in restaurant.getActionsLog())
		std::cout << act << std::endl;
}

//BaseAction * PrintActionsLog::clone() const
//{
//	return nullptr;
//}

std::string PrintActionsLog::toString() const
{
	return "log  " + getErrorToString();
}

BackupRestaurant::BackupRestaurant() : BaseAction()
{
}

BackupRestaurant::~BackupRestaurant()
{
}

void BackupRestaurant::act(Restaurant & restaurant)
{
	extern Restaurant* backup;

	if (backup == nullptr)
		backup = new Restaurant(restaurant);
	else
		*backup = restaurant;
}

//BaseAction * BackupRestaurant::clone() const
//{
//	return nullptr;
//}

std::string BackupRestaurant::toString() const
{
	return "backup " + getErrorToString();
}

RestoreResturant::RestoreResturant() : BaseAction()
{
}

RestoreResturant::~RestoreResturant()
{
}

void RestoreResturant::act(Restaurant & restaurant)
{
	extern Restaurant* backup;
	
	if (backup == nullptr) // no backup
		error("No backup available");
	else
		restaurant = *backup; // restoring
}

//BaseAction * RestoreResturant::clone() const
//{
//	return nullptr;
//}

std::string RestoreResturant::toString() const
{
	return "restore " + getErrorToString();
}




#endif