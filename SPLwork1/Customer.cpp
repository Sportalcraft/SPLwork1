#include "Customer.h"


Customer::~Customer()
{
	int a = 5;
}

Customer::Customer(std::string c_name, int c_id) : id(c_id)
{
}

std::string Customer::getName() const
{
	return std::string();
}

int Customer::getId() const
{
	return 0;
}

VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer( name, id)
{
}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish>& menu)
{
	return std::vector<int>();
}

Customer * VegetarianCustomer::clone() const
{
	return nullptr;
}

std::string VegetarianCustomer::toString() const
{
	return std::string();
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> CheapCustomer::order(const std::vector<Dish>& menu)
{
	return std::vector<int>();
}

Customer * CheapCustomer::clone() const
{
	return nullptr;
}

std::string CheapCustomer::toString() const
{
	return std::string();
}

SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> SpicyCustomer::order(const std::vector<Dish>& menu)
{
	return std::vector<int>();
}

Customer * SpicyCustomer::clone() const
{
	return nullptr;
}

std::string SpicyCustomer::toString() const
{
	return std::string();
}

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish>& menu)
{
	return std::vector<int>();
}

Customer * AlchoholicCustomer::clone() const
{
	return nullptr;
}

std::string AlchoholicCustomer::toString() const
{
	return std::string();
}
