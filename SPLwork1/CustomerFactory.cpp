#include "CustomerFactory.h"



CustomerFactory::CustomerFactory() : nextCustomerID(0)
{
}


CustomerFactory::~CustomerFactory()
{
}

Customer * CustomerFactory::getCustomer(string& customerString)
{
	std::string name;
	std::string kind;
	Customer* ans = nullptr;
	
	int i = 0;

	for (; i < customerString.size() && customerString[i] != ','; i++)
		name += customerString[i];

	i++; // skeep the ","

	for (; i < customerString.size(); i++)
		kind += customerString[i];

	if (kind == "veg")
		ans = new  VegetarianCustomer(name, nextCustomerID);

	if (kind == "chp")
		ans = new  CheapCustomer(name, nextCustomerID);

	if (kind == "alc")
		ans = new AlchoholicCustomer(name, nextCustomerID);

	if (kind == "spc")
		ans = new  SpicyCustomer(name, nextCustomerID);

	if (ans == nullptr) // no customer cteated
		throw std::exception("wrong syntax in customer factory!");

	nextCustomerID++; // reising the next id

	return ans;
}

void CustomerFactory::removeIDs(int amount)
{
	if (nextCustomerID - amount < 0)
		throw std::exception("removing too much IDs!");

		nextCustomerID = nextCustomerID - amount;
}
