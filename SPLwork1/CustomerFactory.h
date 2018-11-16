#ifndef CUSTOMERFACTORY_H_
#define CUSTOMERFACTORY_H_

#include "Customer.h"

class CustomerFactory
{
public:
	CustomerFactory();
	~CustomerFactory();

	Customer* getCustomer(string& customerString);
	void removeIDs(int amount);

private:
	int nextCustomerID;
};

#endif

