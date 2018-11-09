#include "Restaurant.h"



Restaurant::Restaurant()
{
}

Restaurant::Restaurant(const std::string & configFilePath)
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
	return nullptr;
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
