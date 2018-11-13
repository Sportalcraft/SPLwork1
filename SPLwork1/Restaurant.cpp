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
	string s;

	if (!ifs.is_open())
		throw std::runtime_error("file not open");
	ifs.open(configFilePath);

	while (getline(ifs, s))
	{
		if (!s.compare(""))
			continue;

		if (!s.compare("#Number of tables."))
		{
			while (getline(ifs, s))
			{
				if (s == "")
					continue;
				else
				{
					stringstream num(s);
					int x = 0;
					num >> x;
					vector < Table * > tables(x);
					break;
				}
			}
		}

		if (!s.compare("#Tables"))
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


		if (!s.compare("#Menu"))
		{
			while (getline(ifs, s))
			{
				if (s == "")
					continue;
				else
				{
					vector<string> result;
					int i = 0;
					while (s.good())
					{
						string substr;
						getline(s, substr, ',');
						result.push_back(substr);
					}
					stringstream num(result[2]);
					int x = 0;
					num >> x;

					Dish d(i, result[0], x, result[1]);
					menu.push_back(d);
					i++;
				}
			}
		}
	}
}

	
Restaurant::Restaurant(const Restaurant & Other)
{
	copy(Other);
}

Restaurant::Restaurant(Restaurant && Other)
{
	move(std::move(Other));
}

Restaurant::~Restaurant()
{
	clear();
}

Restaurant& Restaurant::operator=(const Restaurant & Other)
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

const vector<BaseAction *> & Restaurant::getActionsLog() const
{
    return actionsLog;
}
vector<Dish> & Restaurant ::getMenu()
{
    return menu;
}
int Restaurant::getNumOfTables() const
{
    return tables.size();
}
Table* Restaurant::getTable(int ind)
{
    return tables[ind]; // no cloning!
}

void Restaurant::start()
{
    cout<<"Restaurant is now open!"<<endl;

}

void Restaurant::copy(const Restaurant & Other)
{
	open = Other.open;

	//copy tables
	for each (Table* table in Other.tables)
		tables.push_back(new Table(*table));

	//copy manu
	menu = Other.menu;

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

	//move manu
	menu = Other.menu;

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

	 //ckear action log

	 for each (BaseAction* action in actionsLog)
		 delete action;
	 actionsLog.clear();
}
