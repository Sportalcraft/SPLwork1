#include "Customer.h"
#include <vector>
#include <string>
#include "iostream"
#include "string"

class  Customer {
    Customer::Customer()
    {
        public:
        Customer(string c_name, int c_id){
            this->id(c_id);
            this->name(c_name);
        }
        vector<int> Customer :: order(const vector<Dish> &menu) {

        }
        Customer string :: toString(){

        }
    }
};
class VegetarianCustomer : public Customer{
    VegetarianCustomer::VegetarianCustomer(std::string name, int id): public Customer {

    }
};
class CheapCustomer :public Customer{
    CheapCustomer::CheapCustomer(std::string name, int id): public Customer {}
};

class SpicyCustomer : public Customer {
    SpicyCustomer::SpicyCustomer(std::string name, int id): public Customer {}
}

class AlchoholicCustomer : public Customer {
    AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):public Customer {}
}


Customer::~Customer()
{
}
