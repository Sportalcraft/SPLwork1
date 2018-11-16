#include "CustomerFactory.h"



CustomerFactory::CustomerFactory() : nextCustomerID(0)
{
}

CustomerFactory::CustomerFactory(const CustomerFactory & Other) : nextCustomerID(Other.nextCustomerID)
{
}

CustomerFactory::CustomerFactory(CustomerFactory && Other) : nextCustomerID(Other.nextCustomerID)
{
}


CustomerFactory::~CustomerFactory()
{
}

CustomerFactory & CustomerFactory::operator=(const CustomerFactory & Other)
{
	if (this != &Other)
		nextCustomerID = Other.nextCustomerID;

	return *this;
}

CustomerFactory & CustomerFactory::operator=(CustomerFactory && Other)
{
	if (this != &Other)
		nextCustomerID = Other.nextCustomerID;

	return *this;
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
