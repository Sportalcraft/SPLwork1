#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
using namespace std;

class Restaurant {
public:
	Restaurant();
	Restaurant(const string &configFilePath);
	void start();
	int getNumOfTables() const;
	Table* getTable(int ind);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
	vector<Dish>& getMenu();

private:
	bool open;
	vector<Table*> tables;
	vector<Dish> menu;
	vector<BaseAction*> actionsLog;
};

#endif