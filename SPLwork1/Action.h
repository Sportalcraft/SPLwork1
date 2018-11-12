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
	BaseAction(const BaseAction& Other);
	BaseAction(BaseAction&& Other);
	virtual ~BaseAction();
	BaseAction* operator=(const BaseAction& other);
	BaseAction* operator=(BaseAction&& other);
	ActionStatus getStatus() const;
	virtual void act(Restaurant& restaurant) = 0;
	virtual BaseAction* clone() const = 0;
	virtual std::string toString() const = 0;
protected:
	void complete();
	void error(std::string errorMsg);
	std::string getErrorMsg() const;
	std::string getErrorToString() const;
private:
	std::string errorMsg;
	ActionStatus status;
	void copy(const BaseAction & Other);
	void move(BaseAction&& Other);
	void clear();
};


class OpenTable : public BaseAction {
public:
	OpenTable(int id, std::vector<Customer *> &customersList);
	OpenTable(const OpenTable& Other);
	OpenTable(OpenTable&& Other);
	virtual ~OpenTable();
	//OpenTable* operator=(const OpenTable& other);
	//OpenTable* operator=(const OpenTable&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
	std::vector<Customer *> customers;

	void copy(const OpenTable & Other);
	void move(OpenTable&& Other);
};


class Order : public BaseAction {
public:
	Order(int id);
	Order(const Order& Other);
	Order(Order&& Other);
	virtual ~Order();
	//Order* operator=(const Order& other);
	//Order* operator=(const Order&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class MoveCustomer : public BaseAction {
public:
	MoveCustomer(int src, int dst, int customerId);
	MoveCustomer(const MoveCustomer& Other);
	MoveCustomer(MoveCustomer&& Other);
	virtual ~MoveCustomer();
	//MoveCustomer* operator=(const MoveCustomer& other);
	//MoveCustomer* operator=(const MoveCustomer&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
	const int srcTable;
	const int dstTable;
	const int id;
};


class Close : public BaseAction {
public:
	Close(int id);
	Close(const Close& Other);
	Close(Close&& Other);
	virtual ~Close();
	//Close* operator=(const Close& other);
	//Close* operator=(const Close&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class CloseAll : public BaseAction {
public:
	CloseAll();
	CloseAll(const CloseAll& Other);
	CloseAll(CloseAll&& Other);
	virtual ~CloseAll();
	CloseAll* operator=(const CloseAll& other);
	CloseAll* operator=(CloseAll&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
};


class PrintMenu : public BaseAction {
public:
	PrintMenu();
	PrintMenu(const PrintMenu& Other);
	PrintMenu(PrintMenu&& Other);
	virtual ~PrintMenu();
	PrintMenu* operator=(const PrintMenu& other);
	PrintMenu* operator=(PrintMenu&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
};


class PrintTableStatus : public BaseAction {
public:
	PrintTableStatus(int id);
	PrintTableStatus(const PrintTableStatus& Other);
	PrintTableStatus(PrintTableStatus&& Other);
	virtual ~PrintTableStatus();
	//PrintTableStatus* operator=(const PrintTableStatus& other);
	//PrintTableStatus* operator=(PrintTableStatus&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
	const int tableId;
};


class PrintActionsLog : public BaseAction {
public:
	PrintActionsLog();
	PrintActionsLog(const PrintActionsLog& Other);
	PrintActionsLog(PrintActionsLog&& Other);
	virtual ~PrintActionsLog();
	PrintActionsLog* operator=(const PrintActionsLog& other);
	PrintActionsLog* operator=(PrintActionsLog&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
};


class BackupRestaurant : public BaseAction {
public:
	BackupRestaurant();
	BackupRestaurant(const BackupRestaurant& Other);
	BackupRestaurant(BackupRestaurant&& Other);
	virtual ~BackupRestaurant();
	BackupRestaurant* operator=(const BackupRestaurant& other);
	BackupRestaurant* operator=(BackupRestaurant&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
};


class RestoreResturant : public BaseAction {
public:
	RestoreResturant();
	RestoreResturant(const RestoreResturant& Other);
	RestoreResturant(RestoreResturant&& Other);
	virtual ~RestoreResturant();
	RestoreResturant* operator=(const RestoreResturant& other);
	RestoreResturant* operator=(RestoreResturant&& other);
	void act(Restaurant &restaurant);
	BaseAction* clone() const;
	std::string toString() const;
private:
};


#endif