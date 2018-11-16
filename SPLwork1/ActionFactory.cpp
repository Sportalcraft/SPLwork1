#include "ActionFactory.h"

#include <sstream>


ActionFactory::ActionFactory() : customerFactory()
{
}


ActionFactory::~ActionFactory()
{
}


BaseAction * ActionFactory::getAction(string& actionString)
{
	string keyword;
	std::vector<std::string> splited;
	std::istringstream iss(actionString);

	for (std::string s; iss >> s; )
		splited.push_back(s);

	keyword = splited[0];

	if (keyword == "open")
		return getOpenTable(splited);

	if (keyword == "order")
		return getOrder(splited);

	if (keyword == "move")
		return getMoveCustomer(splited);

	if (keyword == "close")
		return getClose(splited);

	if (keyword == "closeall")
		return getCloseAll(splited);

	if (keyword == "menu")
		return getPrintMenu(splited);

	if (keyword == "status")
		return getPrintTableStatus(splited);

	if (keyword == "log")
		return getPrintActionsLog(splited);
	
	if (keyword == "backup")
		return getBackupRestaurant(splited);

	if (keyword == "restore")
		return getRestoreResturant(splited);

	throw std::exception("wrong syntax!");
}

OpenTable * ActionFactory::getOpenTable(vector<std::string> & actionString)
{
	if (actionString[0] != "open")
		throw std::exception("wrong method invoked in the factory!");

	const int tanbleId = atoi(actionString[1].c_str());
	vector<Customer*> customers;

	//add customers
	for (int i = 2; i < actionString.size(); i++)
		customers.push_back(customerFactory.getCustomer(actionString[i]));

	return new OpenTable(tanbleId, customers);
}

Order * ActionFactory::getOrder(vector<std::string> & actionString) const
{
	if (actionString[0] != "order")
		throw std::exception("wrong method invoked in the factory!");

	const int tanbleId = atoi(actionString[1].c_str());

	return new Order(tanbleId);
}

MoveCustomer * ActionFactory::getMoveCustomer(vector<std::string> & actionString) const
{
	if (actionString[0] != "move")
		throw std::exception("wrong method invoked in the factory!");

	const int origen = atoi(actionString[1].c_str());
	const int dest = atoi(actionString[2].c_str());
	const int customerId = atoi(actionString[3].c_str());

	return new MoveCustomer(origen, dest, customerId);
}

Close * ActionFactory::getClose(vector<std::string> & actionString) const
{
	if (actionString[0] != "close")
		throw std::exception("wrong method invoked in the factory!");

	const int tanbleId = atoi(actionString[1].c_str());

	return new Close(tanbleId);
}

CloseAll * ActionFactory::getCloseAll(vector<std::string> & actionString) const
{
	if (actionString[0] != "closeall")
		throw std::exception("wrong method invoked in the factory!");

	return new CloseAll();
}

PrintMenu * ActionFactory::getPrintMenu(vector<std::string> & actionString) const
{
	if (actionString[0] != "menu")
		throw std::exception("wrong method invoked in the factory!");

	return new PrintMenu();
}

PrintTableStatus * ActionFactory::getPrintTableStatus(vector<std::string> & actionString) const
{
	if (actionString[0] != "status")
		throw std::exception("wrong method invoked in the factory!");

	const int tanbleId = atoi(actionString[1].c_str());

	return new PrintTableStatus(tanbleId);
}

PrintActionsLog * ActionFactory::getPrintActionsLog(vector<std::string> & actionString) const
{
	if (actionString[0] != "log")
		throw std::exception("wrong method invoked in the factory!");

	return new PrintActionsLog();
}

BackupRestaurant * ActionFactory::getBackupRestaurant(vector<std::string> & actionString) const
{
	if (actionString[0] != "backup")
		throw std::exception("wrong method invoked in the factory!");

	return new BackupRestaurant();
}

RestoreResturant * ActionFactory::getRestoreResturant(vector<std::string> & actionString) const
{
	if (actionString[0] != "restore")
		throw std::exception("wrong method invoked in the factory!");

	return new RestoreResturant();
}
