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

Restaurant ::Restaurant(const string &configFilePath)
{
    open=true;

	ifstream ifs;
    if(! ifs.is_open())
        throw std::runtime_error("file not open");
    ifs.open(configFilePath);
    string s;
    while (getline(ifs, s)){
        if(s=="")
            continue;
        else {
            if(s=="#Number of tables."){
                while (getline(ifs, s)){
                    if(s=="")
                        continue;
                    else {
                        stringstream num(s);
                        int x=0;
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
            else if(s=="#Menu"){
                    while (getline(ifs, s)){
                        if(s=="")
                            continue;
                        else {
                            vector<string> result;
                            int i=0;
							ifs >> s;
                            while( ifs.good() )
                            {
                                string substr;
                                getline( ifs, substr, ',' );
                                result.push_back( substr );
                            }
                            stringstream num1(result[2]);
                            int x1=0;
                            num1 >> x1;
							stringstream num2(result[1]);
							int x2 = 0;
							num2 >> x2;

                            Dish d(i ,result[0] , x1 , x2);
                            menu.push_back(d);
                            i++;
                        }
            }
        }
    }
}
const vector<BaseAction *>& Restaurant::getActionsLog() const
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
    return tables[ind];
}
void Restaurant::start()
{
    cout<<"Restaurant is now open!"<<endl;

}
Restaurant::~Restaurant()
{
	/*for_each(tables.begin(), tables.end(), [](Table* p) { delete p; })*/

	for each (Table* table in tables)
	{
		delete& table
	}

	//for_each(actionsLog.begin(), actionsLog.end(), [](BaseAction* p) { delete p; });
	for each (BaseAction* action in actionsLog)
	{
		delete& action;
	}
};
