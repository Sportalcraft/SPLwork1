#include "Restaurant.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "string"
#include <stdexcept>
#include <sstream>

using namespace std;


Restaurant::Restaurant()
{
    open=true;
    vector<Table*> tables;
    vector<Dish> menu;
    vector<BaseAction*> actionsLog;
}

Restaurant::Restaurant(const string &configFilePath)
{
	open = true;

	ifstream ifs;
	if (!ifs.is_open())
		throw std::runtime_error("file not open");
	ifs.open(configFilePath);
	string s;
	while (getline(ifs, s))
	{
		if (s == "")
			continue;
		else
		{
			if (s == "#Number of tables.")
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
			else if (s == "#Tables")
			{
				while (getline(ifs, s))
				{
					if (s == "")
						continue;
					else
					{
						vector<int> vect;
						stringstream ss(s);
						int i;
						while (ss >> i)
						{
							vect.push_back(i);
							if (ss.peek() == ',')
								ss.ignore();
						}
					}
				}
			}
			else if (s == "#Menu")
			{
				while (getline(ifs, s))
				{
					if (s == "")
						continue;
					else {
						vector<string> result;
						int i = 0;
						ifs >> s;
						while (ifs.good())
						{
							string substr;
							getline(ifs, substr, ',');
							result.push_back(substr);
						}
						stringstream num1(result[2]);
						int x1 = 0;
						num1 >> x1;
						if(result[1]=="VEG"){
							Dish d(i, result[0], x1, DishType(VEG));
							menu.push_back(d);
						}
							
						else if(result[1]=="SPC"){
							Dish d(i, result[0], x1, DishType(SPC));
							menu.push_back(d);
						}
							
						else if(result[1] == "BVG"){
							Dish d(i, result[0], x1, DishType(BVG));
							menu.push_back(d);
						}
							
						else{ 
							Dish d(i, result[0], x1, DishType(ALC)); 
							menu.push_back(d);
						}				
						i++;
					}
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
int Restaurant::getNumOfTables() const
{
   return static_cast<int>(tables.size());
}
Table* Restaurant::getTable(int ind)
{
    return tables[ind];
}

void Restaurant::start()
{
    cout<<"Restaurant is now open!"<<endl;

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