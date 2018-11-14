#include "Customer.h"
#include <vector>
#include <string>
#include "iostream"
#include "string"
#include "Dish.h"
#include <algorithm> // ask in forun of ligal

using namespace std;

Customer ::Customer(string c_name, int c_id) : name(c_name) , id(c_id)
{
	vector<Dish> orders;
}

Customer::Customer(const Customer & Other) : Customer(Other.getName(), Other.getId())
{
}

Customer::Customer(Customer && Other) : Customer(Other.getName(), Other.getId())
{
}

Customer::~Customer()
{
}

string Customer ::getName() const
{
    return name;
}

int Customer ::getId() const
{
    return id;
}



VegetarianCustomer::VegetarianCustomer(string name, int id): Customer(name , id)
{
}
VegetarianCustomer::VegetarianCustomer(const VegetarianCustomer & Other) : Customer(Other)
{
}
VegetarianCustomer::VegetarianCustomer(VegetarianCustomer && Other) : Customer(Other)
{
}
VegetarianCustomer::~VegetarianCustomer()
{
}
string VegetarianCustomer::toString() const
{
    return getName() + ",veg" ;
}
Customer * VegetarianCustomer::clone() const
{
	return new VegetarianCustomer(*this);
}
vector<int> VegetarianCustomer::order(const vector <Dish> &menu)
{
    vector<int> output;
	const Dish* smallestID;
	const  Dish* mostExpenciveBVG;

	if (menu.empty())
		return output; // nothing in the menu - nothing to order
	
	for (Dish dish : menu)
	{
		//find samllest id vegeterian dish		
		// a vegeterian dish with smallerID was fpund, or the first vegeterian dish to be found
		if (dish.getType() == VEG & (smallestID == nullptr || dish.getId() < smallestID->getId()))
			smallestID = &dish;

		//find the most expensive non-alcoholic beverage  
		//   dish is beverage    &  (the first one to be found   ||          a more expensive dish was found       |       a dish with the same price was found,            but it's id is smalller
		if (dish.getType() == BVG & (mostExpenciveBVG == nullptr || dish.getPrice() > mostExpenciveBVG->getPrice() | (dish.getPrice() == mostExpenciveBVG->getPrice() & dish.getId() < mostExpenciveBVG->getId())))
			mostExpenciveBVG = &dish;
	}
   
    if(smallestID == nullptr | mostExpenciveBVG == nullptr)
        return output; // cant complete the order

    output.push_back(smallestID->getId());
    output.push_back(mostExpenciveBVG->getId());
    
	orders.push_back(*smallestID);
    orders.push_back(*mostExpenciveBVG);

    return output;
}


CheapCustomer::CheapCustomer(string name, int id): Customer (name, id)
{
}
CheapCustomer::CheapCustomer(const CheapCustomer & Other) : Customer(Other)
{
}
CheapCustomer::CheapCustomer(CheapCustomer && Other) : Customer(Other)
{
}
CheapCustomer::~CheapCustomer()
{
}
string CheapCustomer ::toString() const
{
	return getName() + ",chp";
}
Customer * CheapCustomer::clone() const
{
	return new CheapCustomer(*this);
}
vector<int> CheapCustomer::order(const vector <Dish> &menu)
{
    vector<int> output;
    int cheapestPos = 0;
	const Dish* cheapest;

	// no menu or alraedy ordered
    if(menu.empty() | (!orders.empty()) )
        return output;

	cheapest = &menu[0];

    for(Dish dish : menu)
    {
		//         cheaper dish was found          |                 same price - the lowest id caunt
		if (dish.getPrice() < cheapest->getPrice() | (dish.getPrice() == cheapest->getPrice() & dish.getId() < cheapest->getId()))
			cheapest = &dish;
    }

    output.push_back(cheapest->getId());
    orders.push_back(*cheapest);

    return output;
}


SpicyCustomer::SpicyCustomer(string name, int id): Customer(name, id)
{
}
SpicyCustomer::SpicyCustomer(const SpicyCustomer & Other) : Customer(Other)
{
}
SpicyCustomer::SpicyCustomer(SpicyCustomer && Other) : Customer(Other)
{
}
SpicyCustomer::~SpicyCustomer()
{
}
string SpicyCustomer::toString() const
{
	return getName() + ",spc";
}
Customer * SpicyCustomer::clone() const
{
	return new SpicyCustomer(*this);
}
vector<int> SpicyCustomer ::order(const vector <Dish> &menu)
{
    vector<int> output;
    const Dish* MostExpemciveSPC;
	const Dish* cheapestBVG;

    if(menu.empty())
        return output; // no menu - no order

    if(orders.empty()) // nothing was order before
    {
       //order most expensive spicy dish       
		
		for (Dish dish : menu) 
		{
			for (Dish dish : menu)
			{
				//     dish is spicy      &  (the first one to be found  ||          a more expensive dish was found       |       a dish with the same price was foound,            but it's id is smalller
				if (dish.getType() == SPC & (MostExpemciveSPC == nullptr || dish.getPrice() > MostExpemciveSPC->getPrice() | (dish.getPrice() == MostExpemciveSPC->getPrice() & dish.getId() < MostExpemciveSPC->getId())))
					MostExpemciveSPC = &dish;
			}
        }

        if (MostExpemciveSPC == nullptr)
			return output; // could not complete order
       
		output.push_back(MostExpemciveSPC->getId());
        orders.push_back(*MostExpemciveSPC);
        return output;
    }
    else // somthig was ordered before
    {
        // order the cheapest non-alcoholic beverage 
		      
		for (Dish dish : menu)
		{
			for (Dish dish : menu)
			{
				//   dish is beverage     &  (the first one to be found  ||          a cheaper dish was found    |       a dish with the same price was found,            but it's id is smalller
				if (dish.getType() == BVG & (cheapestBVG == nullptr || dish.getPrice() < cheapestBVG->getPrice() | (dish.getPrice() == cheapestBVG->getPrice() & dish.getId() < cheapestBVG->getId())))
					cheapestBVG = &dish;
			}
		}

		if (cheapestBVG == nullptr)
			return output; // could not complete order

		output.push_back(cheapestBVG->getId());
		orders.push_back(*cheapestBVG);
		return output;
    }
}


AlchoholicCustomer::AlchoholicCustomer(string name, int id): Customer (name, id), sorted(false)
{
}
AlchoholicCustomer::AlchoholicCustomer(const AlchoholicCustomer & Other) : Customer(Other) , sorted(false)
{
}
AlchoholicCustomer::AlchoholicCustomer(AlchoholicCustomer && Other) : Customer(Other), sorted(false)
{
}
AlchoholicCustomer::~AlchoholicCustomer()
{
}
string AlchoholicCustomer::toString() const
{
	return getName() + ",alc";
}
Customer * AlchoholicCustomer::clone() const
{
	return new AlchoholicCustomer(*this);
}

vector<int> AlchoholicCustomer::order(const vector <Dish> &menu)
{
	// order the most chepest alcoholic beverage that was not ordered yet
	// in this kind of customer, orders will hold the alcoholic beverage that was not ordered yet, in sorted order.

	vector<int> output;

	if (!sorted) //fors time to order - ned to sort
		sortOrders(menu);

	//already sorterd

	if (!orders.empty()) // there are beverages that was not ordered yet
	{
		output.push_back(orders[0].getId());
		orders.erase(orders.begin()); // remove the beverage that was ordered
	}

	return output;
}

void AlchoholicCustomer::sortOrders(const vector<Dish>& menu)
{
	sorted = true; // now being sorted

	for each (Dish dish in menu)
		if (dish.getType() == ALC) // alcholic beverage was found
			orders.push_back(dish);

	// now orders contains only alcoholic beverage, but not sorted
	//sorting
	sort(orders.begin(), orders.end(), wayToSort); // check in forun if ligal
}

bool AlchoholicCustomer::wayToSort(Dish d1, Dish d2) const
{
	return d1.getPrice() > d2.getPrice() | (d1.getPrice() == d2.getPrice() & d1.getId() > d2.getId());
}
