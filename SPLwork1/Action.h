#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus {
	PENDING, COMPLETED, ERROR
};

//Forward declaration
class Restaurant;

class BaseAction {
public:
	BaseAction();
	virtual ~BaseAction();
	ActionStatus getStatus() const;
	virtual void act(Restaurant& restaurant) = 0;
	//virtual BaseAction* clone() const = 0;
	virtual std::string toString() const = 0;
protected:
	void complete();
	void error(std::string errorMsg);
	std::string getErrorMsg() const;
	std::string getErrorToString() const;
private:
	std::string errorMsg;
	ActionStatus status;
};


class OpenTable : public BaseAction {
public:
	OpenTable(int id, std::vector<Customer *> &customersList);
	virtual ~OpenTable();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
	const std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
	Order(int id);
	virtual ~Order();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class MoveCustomer : public BaseAction {
public:
	MoveCustomer(int src, int dst, int customerId);
	virtual ~MoveCustomer();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
	const int srcTable;
	const int dstTable;
	const int id;
};


class Close : public BaseAction {
public:
	Close(int id);

	void act(Restaurant &restaurant);
	virtual ~Close();
	//BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class CloseAll : public BaseAction {
public:
	CloseAll();
	virtual ~CloseAll();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
};


class PrintMenu : public BaseAction {
public:
	PrintMenu();
	virtual ~PrintMenu();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
};


class PrintTableStatus : public BaseAction {
public:
	PrintTableStatus(int id);
	virtual ~PrintTableStatus();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class PrintActionsLog : public BaseAction {
public:
	PrintActionsLog();
	virtual ~PrintActionsLog();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
};


class BackupRestaurant : public BaseAction {
public:
	BackupRestaurant();
	virtual ~BackupRestaurant();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
};


class RestoreResturant : public BaseAction {
public:
	RestoreResturant();
	virtual ~RestoreResturant();
	void act(Restaurant &restaurant);
	//BaseAction* clone() const;
	std::string toString() const;
private:
};


#endif