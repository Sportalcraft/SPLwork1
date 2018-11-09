#include "Action.h"



BaseAction::BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
	return ActionStatus();
}

void BaseAction::complete()
{
}

void BaseAction::error(std::string errorMsg)
{
}

std::string BaseAction::getErrorMsg() const
{
	return std::string();
}

OpenTable::OpenTable(int id, std::vector<Customer*>& customersList) : tableId(id)
{
}

void OpenTable::act(Restaurant & restaurant)
{
}

std::string OpenTable::toString() const
{
	return std::string();
}

Order::Order(int id) : tableId(id)
{
}

void Order::act(Restaurant & restaurant)
{
}

std::string Order::toString() const
{
	return std::string();
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTable(src), dstTable(dst), id(customerId)
{
}

void MoveCustomer::act(Restaurant & restaurant)
{
}

std::string MoveCustomer::toString() const
{
	return std::string();
}

Close::Close(int id) : tableId(id)
{
}

void Close::act(Restaurant & restaurant)
{
}

std::string Close::toString() const
{
	return std::string();
}

CloseAll::CloseAll()
{
}

void CloseAll::act(Restaurant & restaurant)
{
}

std::string CloseAll::toString() const
{
	return std::string();
}

PrintMenu::PrintMenu()
{
}

void PrintMenu::act(Restaurant & restaurant)
{
}

std::string PrintMenu::toString() const
{
	return std::string();
}

PrintTableStatus::PrintTableStatus(int id) : tableId(id)
{
}

void PrintTableStatus::act(Restaurant & restaurant)
{
}

std::string PrintTableStatus::toString() const
{
	return std::string();
}

PrintActionsLog::PrintActionsLog()
{
}

void PrintActionsLog::act(Restaurant & restaurant)
{
}

std::string PrintActionsLog::toString() const
{
	return std::string();
}

BackupRestaurant::BackupRestaurant()
{
}

void BackupRestaurant::act(Restaurant & restaurant)
{
}

std::string BackupRestaurant::toString() const
{
	return std::string();
}

RestoreResturant::RestoreResturant()
{
}

void RestoreResturant::act(Restaurant & restaurant)
{
}

std::string RestoreResturant::toString() const
{
	return std::string();
}
