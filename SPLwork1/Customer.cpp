#include "Customer.h"
#include <vector>
#include <string>
#include "iostream"
#include "string"
using namespace std;

Customer ::Customer(string c_name, int c_id)
{
    this->name(c_name);
    this->id(c_id);
}

string Customer ::getName() const
{
    return this->name;
}

int Customer ::getId() const
{
    return this->id;
}

VegetarianCustomer::VegetarianCustomer(string name, int id): public Customer
{
    this->name(c_name);
    this->id(c_id);
}
string VegetarianCustomer::toString() const
{
    return getName() + " " + getId() + " - VegetarianCustomer";
}

CheapCustomer::CheapCustomer(string name, int id): public Customer
{
    this->name(c_name);
    this->id(c_id);
}
string CheapCustomer ::toString() const
{
    return getName() + " " + getId() + " - CheapCustomer";
}

SpicyCustomer::SpicyCustomer(string name, int id): public Customer
{
    this->name(c_name);
    this->id(c_id);
}
string SpicyCustomer::toString() const
{
    return getName() + " " + getId() + " - SpicyCustomer";
}

AlchoholicCustomer::AlchoholicCustomer(string name, int id):public Customer
{
    this->name(c_name);
    this->id(c_id);
}
string AlchoholicCustomer::toString() const
{
    return getName() + " " + getId() + " - AlchoholicCustomer";
}

Customer::~Customer()
{
}
