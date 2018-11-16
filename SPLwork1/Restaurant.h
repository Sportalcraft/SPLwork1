#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
#include "ActionFactory.h"


class Restaurant {
public:
	Restaurant();
	Restaurant(const std::string &configFilePath);
	Restaurant(const Restaurant& Other);
	Restaurant(Restaurant&& Other);
	~Restaurant();
	Restaurant& operator=(const Restaurant& Other);
	Restaurant& operator=(Restaurant&& Other);
	void start();
	int getNumOfTables() const;
	Table* getTable(int ind);
	const vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions	
	std::vector<Dish>& getMenu();
	void RemoveFutereCustomerIDs(int amount);

private:
	bool open;
	std::vector<Table*> tables;
	std::vector<Dish> menu;
	std::vector<BaseAction*> actionsLog;
	ActionFactory factory;

	void copy(const Restaurant & Other);
	void move(Restaurant&& Other);
	void clear();
};

#endif