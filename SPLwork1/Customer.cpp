#include "Customer.h"
#include <vector>
#include <string>
#include "iostream"
#include "string"


Customer::Customer()
{

}

VegetarianCustomer::VegetarianCustomer(std::string name, int id): public Customer
{

}

CheapCustomer::CheapCustomer(std::string name, int id): public Customer
{

}

SpicyCustomer::SpicyCustomer(std::string name, int id): public Customer
{

}

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):public Customer
{

}

Customer::~Customer()
{
}
