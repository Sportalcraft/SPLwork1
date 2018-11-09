#include "Table.h"


Table::~Table()
{
}

Table::Table(int t_capacity)
{
	capacity = t_capacity;
	open = true;	
}

Table::Table(const Table& Other)
{	
	capacity = Other.capacity;
	open = Other.open;

}

Table::Table(const Table&& Other)
{
}

Table * Table::operator=(const Table & other)
{
	return this;
}

Table * Table::operator=(const Table&& other)
{
	return this;
}

int Table::getCapacity() const
{
	return capacity;
}

void Table::addCustomer(Customer * customer)
{
}

void Table::removeCustomer(int id)
{
}

Customer * Table::getCustomer(int id)
{
	return nullptr;
}

std::vector<Customer*>& Table::getCustomers()
{
	// TODO: insert return statement here
	return customersList;
}

std::vector<OrderPair>& Table::getOrders()
{
	// TODO: insert return statement here
	return orderList;
}

void Table::order(const std::vector<Dish>& menu)
{
}

void Table::openTable()
{
}

void Table::closeTable()
{
}

int Table::getBill()
{
	return 0;
}

bool Table::isOpen()
{
	return false;
}
