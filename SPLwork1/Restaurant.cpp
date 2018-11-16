#include "Restaurant.h"
#include "vector"
#include "string"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <fstream>

#include "ActionFactory.h"

using namespace std;


Restaurant::Restaurant()
{
    open=true;
    vector<Table*> tables;
    vector<Dish> menu;
    vector<BaseAction*> actionsLog;
	ActionFactory factory;
}

Restaurant::Restaurant(const string &configFilePath)
{
	ifstream ifs;
	string s;
	int dishID = 0;
	
	open = true;
	ifs.open(configFilePath);

	if (ifs.fail())
		throw std::runtime_error("file not open");

	while (getline(ifs, s))
	{
		if (s == "")
			continue;
		else
		{
			if (s == "#number of tables")
			{
				while (getline(ifs, s)) {
					if (s == "")
						continue;
					else {
						stringstream num(s);
						int x = 0;
						num >> x;
						vector < Table * > tables(x);
						break;
					}
				}
			}
			else if (s == "#tables description")
			{
				while (getline(ifs, s))
				{
					if (s == "")
						continue;
					else
					{
						stringstream ss(s);
						int i;
						while (ss >> i)
						{
							Table *t = new Table(i);
							tables.push_back(t);
							if (ss.peek() == ',')
								ss.ignore();
						}
						break;
					}
				}
			}
			else if (s == "#Menu")
			{
				while (getline(ifs, s))
				{
					if (s == "")
						continue;
	
					vector<string> result;
					string temp;

					int i = 0;

					for (int wordnum = 1; wordnum <= 3; wordnum++)
					{
						for (; i < s.size() && s[i] != ','; i++)
							temp += s[i];

						result.push_back(temp);
						temp.clear();
						i++;
					}

					int price = atoi(result[2].c_str());

					if(result[1]=="VEG"){
						Dish d(dishID, result[0], price, DishType(VEG));
						menu.push_back(d);
					}
							
					else if(result[1]=="SPC"){
						Dish d(dishID, result[0], price, DishType(SPC));
						menu.push_back(d);
					}
							
					else if(result[1] == "BVG"){
						Dish d(dishID, result[0], price, DishType(BVG));
						menu.push_back(d);
					}
							
					else{ 
						Dish d(dishID, result[0], price, DishType(ALC));
						menu.push_back(d);
					}				
					
					dishID++;
				}
			}
		}
	}
}
const vector<BaseAction *>& Restaurant::getActionsLog() const
{
    return actionsLog;
}
Restaurant::Restaurant(const Restaurant & Other)
{
	copy(Other);
}
Restaurant::Restaurant(Restaurant && Other)
{
	move(std::move(Other));
}
vector<Dish> & Restaurant ::getMenu()
{
    return menu;
}
void Restaurant::RemoveFutereCustomerIDs(int amount)
{
	factory.removeCustomerIDs(amount);
}
void Restaurant::close()
{
	open = false;
}
int Restaurant::getNumOfTables() const
{
   return static_cast<int>(tables.size());
}
Table* Restaurant::getTable(int ind)
{
	 return tables[ind -1]; // no cloneing!
}

void Restaurant::start()
{
	string command;
	BaseAction* ac2Perform;
	
	cout<<"Restaurant is now open!"<<endl;

	while (open) // restorunt still open
	{
		std::getline(std::cin, command);
		ac2Perform = factory.getAction(command);
		ac2Perform->act(*this);
		actionsLog.push_back(ac2Perform);
	}

	system("pause");; // in order to wait for the user
}
Restaurant::~Restaurant()
{
	clear();
}
Restaurant & Restaurant::operator=(const Restaurant & Other)
{
	if (this != &Other)
	{
		clear(); // delete all data
		copy(Other); // get new data
	}

	return *this;
}
Restaurant & Restaurant::operator=(Restaurant && Other)
{
	if (this != &Other)
	{
		clear(); // delete all data
		move(std::move(Other)); // get new data		
	}

	return *this;
}

void Restaurant::copy(const Restaurant & Other)
{
	open = Other.open;

	//copy tables
	for each (Table* table in Other.tables)
		tables.push_back(new Table(*table));

	//copy manu
	menu.clear();
	for each (Dish dish in Other.menu)
		menu.push_back(dish);

	//copy action log
	for each (BaseAction* action in Other.actionsLog)
		actionsLog.push_back(action->clone());
}

void Restaurant::move(Restaurant && Other)
{
	open = Other.open;

	//move tables
	for each (Table* table in Other.tables)
		tables.push_back(table);

	//move menu
	menu.clear();
	for each (Dish dish in Other.menu)
		menu.push_back(dish);

	//move action log
	for each (BaseAction* action in Other.actionsLog)
		actionsLog.push_back(action);

	//Delete old
	Other.open = false;
	Other.tables.clear();
	Other.menu.clear();
	Other.actionsLog.clear();
}

void Restaurant::clear()
{
	open = false;

	//clear tables
	for each (Table* table in tables)
		delete table;
	tables.clear();

	//clear manu
	menu.clear();

	//clear action log

	for each (BaseAction* action in actionsLog)
		delete action;
	actionsLog.clear();
}