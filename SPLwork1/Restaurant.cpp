#include "Restaurant.h"



Restaurant::Restaurant()
{
}

Restaurant::Restaurant(const std::string & configFilePath)
{
}

Restaurant::Restaurant(const Restaurant & restaurant)
{
}

Restaurant * Restaurant::operator=(const Restaurant & restaurant)
{
	return nullptr;
}

Restaurant * Restaurant::operator=(Restaurant && restaurant)
{
	return nullptr;
}

Restaurant::Restaurant(Restaurant && restaurant)
{
}

Restaurant::~Restaurant()
{
}

void Restaurant::start()
{
}

int Restaurant::getNumOfTables() const
{
	return 0;
}

Table * Restaurant::getTable(int ind)
{
	return tables[ind]; // no cloning!
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const
{
	// TODO: insert return statement here
	return actionsLog;
}

std::vector<Dish>& Restaurant::getMenu()
{
	// TODO: insert return statement here
	return menu;
}
