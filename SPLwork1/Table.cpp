#include "Table.h"

#include <iostream>


Table::~Table()
{
	//delete customers
	for each (Customer* cus in customersList)
		delete cus;
}

Table::Table(int t_capacity)
{
	capacity = t_capacity;
	open = false;	
}

Table::Table(const Table& Other)
{
	copy(Other);
}

Table::Table(Table&& Other)
{
	move(std::move(Other));
}

Table & Table::operator=(const Table & other)
{
	if (this != &other)
	{
		clear(); // delete all data
		copy(other); // get new data
	}

	return *this;
}

Table & Table::operator=(Table&& other)
{
	if (this != &other)
	{
		clear(); // delete all data
		move(std::move(other)); // get new data		
	}

	return *this;
}

int Table::getCapacity() const
{
	return capacity;
}

void Table::addCustomer(Customer * customer)
{
	if(customersList.size() == capacity) // table is full
		throw std::exception("Table is full!");
	
	for each (Customer* cus in customersList)
		if (cus->getId() == customer->getId()) // alrady in the table
			throw std::exception("Already in the table!");
	
	customersList.push_back(customer->clone()); // must clone
}

void Table::removeCustomer(int id)
{
	int pos = 0;

	// remove customer
	for each (Customer* cus in customersList)
	{
		if (cus->getId() == id) // the positin of dessired customer was found
		{
			// the customer was found, need to delete it
			delete cus; // delete the custoner object
			customersList.erase(customersList.begin() + pos); //remove pointer reom vector
			break;
		}

		pos++;
	}

	//remove customer's orders	
	std::vector<OrderPair>& tOrders = getOrdersCopy(); // save copy
	orderList.clear(); // remove current orders

	for each (OrderPair pair in tOrders)
		if (pair.first != id) // order from diffrent custoner
			orderList.push_back(pair); // push the order back, it's not soppsed to be deleted
}

Customer * Table::getCustomer(int id)
{
	for each (Customer* cus in customersList)
	{
		if (cus->getId() == id) // we have a match!
			return cus->clone(); // must clone
	}

	throw std::exception("customer no found!"); // No match found
}

std::vector<Customer*>& Table::getCustomers()
{
	return customersList;
}

std::vector<OrderPair>& Table::getOrders()
{
	return orderList;
}

void Table::order(const std::vector<Dish>& menu)
{
	std::vector<int> cusorder;

	if (!open) // close table
		throw std::exception("The table is close!");

	for each (Customer* cus in customersList)
	{
		cusorder = cus->order(menu);

		for each (int dishID in cusorder)
			for (Dish dish : menu)
				if (dish.getId() == dishID)
				{
					orderList.push_back(OrderPair(cus->getId(), dish)); // push order
					
					std::cout << cus->getName() + " ordered " + dish.getName() << std::endl; //print order
				}
	}
}

void Table::openTable()
{	
	if (open) // already open
		throw std::exception("Table already open!");
	
	open = true;
}

void Table::closeTable()
{
	if (!open) // already close
		throw std::exception("Table already close!");

	open = false;	
	clear(); //remove existing data
}

int Table::getBill()
{
	int bill = 0;

	for each (OrderPair pair in orderList)
		bill += pair.second.getPrice(); // sum the price of all ordered dishes

	return bill;
}

bool Table::isOpen()
{
	return open;
}





void Table::copy(const Table & Other)
{
	capacity = Other.capacity;
	open = Other.open;

	//copy orders
	for each (OrderPair pair in Other.orderList)
		orderList.push_back(OrderPair(pair.first, pair.second)); // banana ?

	//copy customers
	for each (Customer* cus in Other.customersList)
		customersList.push_back(cus->clone());
}

void Table::move(Table && Other)
{
	capacity = Other.capacity;
	open = Other.open;
	
	//move orders
	for each (OrderPair pair in Other.orderList)
		orderList.push_back(OrderPair(pair.first, pair.second)); // banana ?

	customersList = Other.customersList;

	//Delete old
	Other.capacity = 0;
	Other.open = false;
	Other.orderList.clear();
	Other.customersList.clear();
}

void Table::clear()
{
	orderList.clear();

	//removing instances of customers
	for each (Customer*  cus in customersList)
		delete cus;

	customersList.clear();
}

std::vector<OrderPair> Table::getOrdersCopy()
{
	std::vector<OrderPair> copy;

	for each (OrderPair pair in orderList)
		copy.push_back(OrderPair(pair.first, pair.second)); // banana ?

	return copy;
}







