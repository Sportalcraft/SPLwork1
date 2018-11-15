#ifndef BASEACTION_H_
#define BASEACTION_H_

#include "Action.h"
#include "Restaurant.h"
#include <vector>



BaseAction::BaseAction() : status(PENDING), errorMsg("")
{
}

BaseAction::BaseAction(const BaseAction & Other)
{
	copy(Other);
}

BaseAction::BaseAction(BaseAction && Other)
{
	move(std::move(Other));
}

BaseAction::~BaseAction()
{
}

BaseAction & BaseAction::operator=(const BaseAction & other)
{

	if (this != &other)
	{
		clear(); // delete all data
		copy(other); // get new data
	}

	return *this;
}

BaseAction & BaseAction::operator=(BaseAction && other)
{
	if (this != &other)
	{
		clear(); // delete all data
		move(std::move(other)); // get new data		
	}

	return *this;
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

	cout << "Error: +" + errorMsg;
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

std::string BaseAction::getPrmetersString() const
{
	return std::string();
}

void BaseAction::copy(const BaseAction & Other)
{
	errorMsg = Other.errorMsg;
	status = Other.status;
}

void BaseAction::move(BaseAction && Other)
{
	copy(Other); // no diffrent implimintation
}

void BaseAction::clear()
{
	errorMsg.clear();
}

OpenTable::OpenTable(int id, std::vector<Customer*>& customersList) :BaseAction(), tableId(id), customers(customersList)
{
}

OpenTable::OpenTable(const OpenTable & Other) : BaseAction(Other), tableId(Other.tableId)
{
	copy(Other);
}

OpenTable::OpenTable(OpenTable && Other) : BaseAction(Other), tableId(Other.tableId)
{
	move(std::move(Other));
}

OpenTable::~OpenTable()
{
	//delete customers
	for each (Customer* cus in customers)
		delete cus; 
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
			table->addCustomer(cus->clone());

		complete(); // action excecuted succesfully

	}
	catch (const std::exception&)
	{
		error("Table does not exist or is already open");
		restaurant.RemoveFutereCustomerIDs(static_cast<int>(customers.size())); // failed to add, so returning back woth the ids
	}

	//if (table != nullptr)
	//	delete table; // delete the table at the end
}

BaseAction * OpenTable::clone() const
{
	return new OpenTable(*this);
}

std::string OpenTable::toString() const
{
	return "open " + getPrmetersString() + getErrorToString();
}

std::string OpenTable::getPrmetersString() const
{
	std::string types[4] = { "VEG", "SPC", "BVG", "ALC" };
	
	string s = BaseAction::getPrmetersString() + std::to_string(tableId) + " ";
	for each (Customer* cus in customers)
		s += cus->toString();

	return s;
}

void OpenTable::copy(const OpenTable & Other)
{
	//copy customers
	for each (Customer* cus in Other.customers)
		customers.push_back(cus->clone());
}

void OpenTable::move(OpenTable && Other)
{
	//move customers
	for each (Customer* cus in Other.customers)
		customers.push_back(cus);

	//Delete old
	Other.customers.clear();
}

Order::Order(int id) : BaseAction(), tableId(id)
{
}

Order::Order(const Order & Other) : BaseAction(Other) , tableId(Other.tableId)
{
}

Order::Order(Order && Other) : BaseAction(Other), tableId(Other.tableId)
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

		if (!table->isOpen()) // table must be open
			throw std::exception("table is close!");

		table->order(restaurant.getMenu()); // already print to screen

		complete(); // action excecuted succesfully
	}
	catch (const std::exception&)
	{
		//Table no found
		error("Table does not exist or is not open");
	}
		
	//if(table != nullptr)
	//	delete table; // delete the table at the end
}

BaseAction * Order::clone() const
{
	return new Order(*this);
}

std::string Order::toString() const
{
	return "order " + getPrmetersString() + " " + getErrorToString();
}

std::string Order::getPrmetersString() const
{
	return BaseAction::getPrmetersString() + std::to_string(tableId);
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) :BaseAction(), srcTable(src), dstTable(dst), id(customerId)
{
}

MoveCustomer::MoveCustomer(const MoveCustomer & Other) : BaseAction(Other), srcTable(Other.srcTable), dstTable(Other.srcTable), id(Other.srcTable)
{
}

MoveCustomer::MoveCustomer(MoveCustomer && Other) : BaseAction(Other), srcTable(Other.srcTable), dstTable(Other.srcTable), id(Other.srcTable)
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

	try
	{
		sorce = restaurant.getTable(srcTable);
		destenation = restaurant.getTable(dstTable);
		customer = sorce->getCustomer(id);
		
		destenation->addCustomer(customer->clone());		
		std::vector<OrderPair>& AllsorceOrders = sorce->getOrders(); // banana ?

		//moving orders
		for each (OrderPair pair in AllsorceOrders)
			if (pair.first == customer->getId()) // the order was made byour customer
				destenation->addOrder(pair);

		sorce->removeCustomer(id); // remive customer from src

		complete(); // action excecuted succesfully
	}
	catch (const std::exception&)
	{
		error("Cannot move customer");
	}

	//if (sorce != nullptr)
	//	delete sorce;

	//if (destenation != nullptr)
	//	delete destenation;

	if (customer != nullptr)
		delete customer;
}

BaseAction * MoveCustomer::clone() const
{
	return new MoveCustomer(*this);
}

std::string MoveCustomer::toString() const
{
	return "Move " + getPrmetersString() + " " + getErrorToString();
}

std::string MoveCustomer::getPrmetersString() const
{
	return BaseAction::getPrmetersString() + std::to_string(srcTable) + std::to_string(dstTable) + std::to_string(id);
}

Close::Close(int id) :BaseAction(), tableId(id)
{
}

Close::Close(const Close & Other) : BaseAction(Other), tableId(Other.tableId)
{
}

Close::Close(Close && Other) : BaseAction(Other), tableId(Other.tableId)
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
	//	delete table; // delete the table at the end
}

Close::~Close()
{
}

BaseAction * Close::clone() const
{
	return new Close(*this);
}

std::string Close::toString() const
{
	return "close " + getPrmetersString() + " " + getErrorToString();
}

std::string Close::getPrmetersString() const
{
	return BaseAction::getPrmetersString() + std::to_string(tableId);
}

CloseAll::CloseAll() : BaseAction()
{
}

CloseAll::CloseAll(const CloseAll & Other) : BaseAction(Other)
{
}

CloseAll::CloseAll(CloseAll && Other) : BaseAction(Other)
{
}

CloseAll::~CloseAll()
{
}

CloseAll & CloseAll::operator=(const CloseAll & other)
{
	 BaseAction::operator=(other);
	 return *this;
}

CloseAll & CloseAll::operator=(CloseAll && other)
{
	BaseAction::operator=(other);
	return *this;
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

BaseAction * CloseAll::clone() const
{
	return new CloseAll(*this);
}

std::string CloseAll::toString() const
{
	return "closeall " + getErrorToString();
}

PrintMenu::PrintMenu() : BaseAction()
{
}

PrintMenu::PrintMenu(const PrintMenu & Other) : BaseAction(Other)
{
}

PrintMenu::PrintMenu(PrintMenu && Other) : BaseAction(Other)
{
}

PrintMenu::~PrintMenu()
{
}

PrintMenu & PrintMenu::operator=(const PrintMenu & other)
{
	BaseAction::operator=(other);
	return *this;
}

PrintMenu & PrintMenu::operator=(PrintMenu && other)
{
	BaseAction::operator=(other);
	return *this;
}

void PrintMenu::act(Restaurant & restaurant)
{
	std::string types[4] = { "VEG", "SPC", "BVG", "ALC" };

	for each (Dish dish in restaurant.getMenu())	
		std::cout << dish.getName() + " " + types[dish.getType()] + " " + std::to_string(dish.getPrice()) << std::endl;
}

BaseAction * PrintMenu::clone() const
{
	return new PrintMenu(*this);
}

std::string PrintMenu::toString() const
{
	return "menu " + getErrorToString(); 
}

PrintTableStatus::PrintTableStatus(int id) : BaseAction(), tableId(id)
{
}

PrintTableStatus::PrintTableStatus(const PrintTableStatus & Other) : BaseAction(Other) , tableId(Other.tableId)
{
}

PrintTableStatus::PrintTableStatus(PrintTableStatus && Other) : BaseAction(Other), tableId(Other.tableId)
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
	//	delete table;

	if (status != nullptr)
		delete status;
}

BaseAction * PrintTableStatus::clone() const
{
	return new PrintTableStatus(*this);
}

std::string PrintTableStatus::toString() const
{
	return "status " + getPrmetersString() + " " + getErrorToString();
}

std::string PrintTableStatus::getPrmetersString() const
{
	return BaseAction::getPrmetersString() + std::to_string(tableId);
}

PrintActionsLog::PrintActionsLog() : BaseAction()
{
}

PrintActionsLog::PrintActionsLog(const PrintActionsLog & Other) : BaseAction(Other)
{
}

PrintActionsLog::PrintActionsLog(PrintActionsLog && Other) : BaseAction(Other)
{
}

PrintActionsLog::~PrintActionsLog()
{
}

PrintActionsLog & PrintActionsLog::operator=(const PrintActionsLog & other)
{
	BaseAction::operator=(other);
	return *this;
}

PrintActionsLog & PrintActionsLog::operator=(PrintActionsLog && other)
{
	BaseAction::operator=(other);
	return *this;
}

void PrintActionsLog::act(Restaurant & restaurant)
{
	//print all actions
	for each (BaseAction* act in restaurant.getActionsLog())
		std::cout << act << std::endl; 
}

BaseAction * PrintActionsLog::clone() const
{
	return new PrintActionsLog(*this);
}

std::string PrintActionsLog::toString() const
{
	return "log  " + getErrorToString(); 
}

BackupRestaurant::BackupRestaurant() : BaseAction()
{
}

BackupRestaurant::BackupRestaurant(const BackupRestaurant & Other) : BaseAction(Other)
{
}

BackupRestaurant::BackupRestaurant(BackupRestaurant && Other) : BaseAction(Other)
{
}

BackupRestaurant::~BackupRestaurant()
{
}

BackupRestaurant & BackupRestaurant::operator=(const BackupRestaurant & other)
{
	BaseAction::operator=(other);
	return *this;
}

BackupRestaurant & BackupRestaurant::operator=(BackupRestaurant && other)
{
	BaseAction::operator=(other);
	return *this;
}

void BackupRestaurant::act(Restaurant & restaurant)
{
	extern Restaurant* backup;

	if (backup == nullptr)
		backup = new Restaurant(restaurant);
	else
		*backup = restaurant;
}

BaseAction * BackupRestaurant::clone() const
{
	return new BackupRestaurant(*this);
}

std::string BackupRestaurant::toString() const
{
	return "backup " + getErrorToString(); 
}

RestoreResturant::RestoreResturant() : BaseAction()
{
}

RestoreResturant::RestoreResturant(const RestoreResturant & Other) : BaseAction(Other)
{
}

RestoreResturant::RestoreResturant(RestoreResturant && Other) : BaseAction(Other)
{
}

RestoreResturant::~RestoreResturant()
{
}

RestoreResturant & RestoreResturant::operator=(const RestoreResturant & other)
{
	BaseAction::operator=(other);
	return *this;
}

RestoreResturant & RestoreResturant::operator=(RestoreResturant && other)
{
	BaseAction::operator=(other);
	return *this;
}

void RestoreResturant::act(Restaurant & restaurant)
{
	extern Restaurant* backup;
	
	if (backup == nullptr) // no backup
		error("No backup available");
	else
		restaurant = *backup; // restoring 
}

BaseAction * RestoreResturant::clone() const
{
	return new RestoreResturant(*this);
}

std::string RestoreResturant::toString() const
{
	return "restore " + getErrorToString();
}




#endif