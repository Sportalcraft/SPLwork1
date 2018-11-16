#ifndef ACTIONFACTORY_H_
#define ACTIONFACTORY_H_


#include "Action.h"
#include "CustomerFactory.h"

class ActionFactory
{
public:
	ActionFactory();
	~ActionFactory();
	BaseAction* getAction(string& actionString);
private:
	CustomerFactory customerFactory;
	
	OpenTable* getOpenTable(vector<std::string>& actionString) ;
	Order* getOrder(vector<std::string>& actionString) const;
	MoveCustomer* getMoveCustomer(vector<std::string>& actionString) const;
	Close* getClose(vector<std::string>& actionString) const;
	CloseAll* getCloseAll(vector<std::string>& actionString) const;
	PrintMenu* getPrintMenu(vector<std::string>& actionString) const;
	PrintTableStatus* getPrintTableStatus(vector<std::string>& actionString) const;
	PrintActionsLog* getPrintActionsLog(vector<std::string>& actionString) const;
	BackupRestaurant* getBackupRestaurant(vector<std::string>& actionString) const;
	RestoreResturant* getRestoreResturant(vector<std::string>& actionString) const;
};


#endif

