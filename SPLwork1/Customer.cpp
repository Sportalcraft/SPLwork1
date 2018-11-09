#include "Customer.h"
#include <vector>
#include <string>
#include "iostream"
#include "string"
#include "Dish.h"

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
vector<int> VegetarianCustomer::order(const vector <Dish> &menu)
{
    vector<int> output= new vector<int>;
    if(menu.empty())
        return output;
    int minID= -1;
    int maxPriceDrink= -1;
    int id_maxPriceDrink=-1;
    for(Dish dish : menu)
    {
        if( (dish.getType()==VEG & minID== -1) | (dish.getType()==VEG & dish.getId()<minID) )
            minID=dish.getId();
        if(dish.getPrice()>=maxPriceDrink & dish.getType() != ALC) {
            if(dish.getPrice()==maxPriceDrink)
            {
                if (dish.getId() < id_maxPriceDrink)
                {
                    maxPriceDrink = dish.getPrice();
                    id_maxPriceDrink = dish.getId();
                }
            }
            else
                {
                    maxPriceDrink = dish.getPrice();
                    id_maxPriceDrink = dish.getId();
                }
        }
    }
    if(maxPriceDrink==-1 | minID==-1)
        return output;
    output.push_back(minID);
    output.push_back(id_maxPriceDrink);
    return output;
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
vector<int> CheapCustomer::order(const vector <Dish> &menu)
{

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
vector<int> SpicyCustomer ::order(const vector <Dish> &menu)
{

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
vector<int> AlchoholicCustomer::order(const vector <Dish> &menu)
{

}


Customer::~Customer()
{
}
