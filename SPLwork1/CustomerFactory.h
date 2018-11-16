#ifndef CUSTOMERFACTORY_H_
#define CUSTOMERFACTORY_H_

#include "Customer.h"

class CustomerFactory
{
public:
	CustomerFactory();
	CustomerFactory(const CustomerFactory& Other);
	CustomerFactory(CustomerFactory&& Other);
	~CustomerFactory();
	CustomerFactory& operator=(const CustomerFactory& Other);
	CustomerFactory& operator=(CustomerFactory&& Other);

	Customer* getCustomer(string& customerString);

private:
	int nextCustomerID;
};

#endif

