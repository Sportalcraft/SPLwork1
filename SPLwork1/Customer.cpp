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
    orders= new vector<Dish>;
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
    orders= new vector<Dish>;
}
string VegetarianCustomer::toString() const
{
    return getName() + " " + getId() + " - VegetarianCustomer";
}
vector<int> VegetarianCustomer::order(const vector <Dish> &menu)
{
    vector<int> output= new vector<int>;
    Dish d1;
    Dish d2;
    if(menu.empty())
        return output;
    int minID= -1;
    int maxPriceDrink= -1;
    int id_maxPriceDrink=-1;
    for(Dish dish : menu)
    {
        if( (dish.getType()==VEG & minID== -1) | (dish.getType()==VEG & dish.getId()<minID) )
        {
            minID=dish.getId();
            d1=dish;
        }
        if(dish.getPrice()>=maxPriceDrink & dish.getType() != ALC & dish.getType()==BVG) {
            if(dish.getPrice()==maxPriceDrink)
            {
                if (dish.getId() < id_maxPriceDrink)
                {
                    maxPriceDrink = dish.getPrice();
                    id_maxPriceDrink = dish.getId();
                    d2=dish;
                }
            }
            else
                {
                    maxPriceDrink = dish.getPrice();
                    id_maxPriceDrink = dish.getId();
                    d2=dish;
                }
        }
    }
    if(maxPriceDrink==-1 | minID==-1)
        return output;
    output.push_back(minID);
    output.push_back(id_maxPriceDrink);
    orders.push_back(d1);
    orders.push_back(d2);

    return output;
}


CheapCustomer::CheapCustomer(string name, int id): public Customer
{
    this->name(c_name);
    this->id(c_id);
    orders= new vector<Dish>;
}
string CheapCustomer ::toString() const
{
    return getName() + " " + getId() + " - CheapCustomer";
}
vector<int> CheapCustomer::order(const vector <Dish> &menu)
{
    vector<int> output= new vector<int>;
    Dish d1;
    if(menu.empty() | (! orders.empty()) )
        return output;
    int minPrice=-1;
    int id_minPrice=-1;
    for(Dish dish : menu)
    {
        if(minPrice==-1 | dish.getPrice()<minPrice)
        {
            minPrice=dish.getPrice();
            id_minPrice=dish.getId();
            d1=dish;
        }
    }
    output.push_back(id_minPrice);
    orders.push_back(d1);
    return output;
}


SpicyCustomer::SpicyCustomer(string name, int id): public Customer
{
    this->name(c_name);
    this->id(c_id);
    orders= new vector<Dish>;
}
string SpicyCustomer::toString() const
{
    return getName() + " " + getId() + " - SpicyCustomer";
}
vector<int> SpicyCustomer ::order(const vector <Dish> &menu)
{
    vector<int> output= new vector<int>;
    Dish d1;
    if(menu.empty())
        return output;
    if(orders.empty())
    {
        int maxPriceSpicy = -1;
        int id_maxPriceSpicy = -1;
        for (Dish dish : menu) {
            if (dish.getType() == SPC & dish.getPrice() > maxPriceSpicy) {
                maxPriceSpicy = dish.getPrice();
                id_maxPriceSpicy = dish.getId();
                d1=dish;
            }
        }
        if (maxPriceSpicy != -1)
        {
            output.push_back(id_maxPriceSpicy);
            orders.push_back(d1);
        }
        return output;
    }
    else
    {
         int minPriceDrink=-1;
         int id_minPriceDrink=-1;
         Dish d2;
        for (Dish dish : menu) {
            if(dish.getType() != ALC & dish.getType()==BVG)
            {
                if(minPriceDrink==-1 | dish.getPrice()<minPriceDrink)
                {
                    minPriceDrink=dish.getPrice();
                    id_minPriceDrink=dish.getId();
                    d2=dish;
                }
            }
        }
        if(minPriceDrink==-1)
            return output;
        output.push_back(id_minPriceDrink);
        orders.push_back(d2);
        return output;
    }
}


AlchoholicCustomer::AlchoholicCustomer(string name, int id):public Customer
{
    this->name(c_name);
    this->id(c_id);
    orders= new vector<Dish>;
}
string AlchoholicCustomer::toString() const
{
    return getName() + " " + getId() + " - AlchoholicCustomer";
}
vector<int> AlchoholicCustomer::order(const vector <Dish> &menu)
{
    Dish d1;
    vector<int> output= new vector<int>;
    if(menu.empty())
        return output;
    if(orders.empty())
    {
        int minPriceAlc=-1;
        int id_minPriceAlc=-1;
        for(Dish dish : menu)
        {
            if( (dish.getType()==ALC & minPriceAlc==-1) | (dish.getType()==ALC & dish.getPrice()<minPriceAlc) )
            {
                minPriceAlc=dish.getPrice();
                id_minPriceAlc=dish.getId();
                d1=dish;
            }
        }
        if(minPriceAlc!=-1) {
            output.push_back(id_minPriceAlc);
            orders.push_back(d1);
        }
        return output;
    }
    else
        {
            const int minPrice=orders.back().c.getPrice();
            int id_minPrice=order.back().c.getId();
            int maxMin=-1;
            int id_maxMin= -1;
            Dish d2;
            for(Dish dish : menu)
            {
                if((dish.getType()==ALC & dish.getPrice()>=minPriceAlc)) {
                    if(dish.getPrice()>minPriceAlc)
                    {
                        maxMin = dish.getPrice();
                        break;
                    }
                    else
                    {
                        if(dish.getId()>id_minPrice)
                        {
                            maxMin = dish.getPrice();
                            break;
                        }
                    }
                }
            }
            if(maxMin==-1)
                return output;

            for(Dish dish : menu)
            {
                if(dish.getType()==ALC & dish.getPrice()=>minPrice & dish.getPrice()<=maxMin)
                {
                    if(dish.getPrice()>minPrice & dish.getPrice()<maxMin)
                    {
                        maxMin=dish.getPrice();
                        id_maxMin=dish.getId();
                        d2=dish;
                    }
                    else if(dish.getPrice()=>minPrice & dish.getPrice()<maxMin)
                    {
                        if(dish.getId()>id_minPrice)
                        {
                            maxMin=dish.getPrice();
                            id_maxMin=dish.getId();
                            d2=dish;
                        }
                    }
                    else
                        {
                            if(dish.getId()<id_maxMin)
                            {
                                maxMin=dish.getPrice();
                                id_maxMin=dish.getId();
                                d2=dish;
                            }
                        }
                }
            }
            if(maxMin==-1)
                return output;
            output.push_back(id_maxMin);
            orders.push_back(d2);
            return output;
        }

}


Customer::~Customer()
{
}
