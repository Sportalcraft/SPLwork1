#include "Customer.h"


Customer::~Customer()
{
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

std::string AlchoholicCustomer::toString() const
{
	return std::string();
}
