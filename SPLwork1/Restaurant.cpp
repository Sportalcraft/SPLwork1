#include "Restaurant.h"
#include "vector"
#include "iostream"
using namespace std;

Restaurant::Restaurant()
{
    open=true;
    tables=new vector<Table*>;
    menu= new vector<Dish>;
    actionsLog= new vector<BaseAction*>;
}

Restaurant ::Restaurant(const string &configFilePath)
{
    open=true;

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

}
void Restaurant::start()
{
    cout<<"Restaurant is now open!"<<endl;
}
Restaurant::~Restaurant()
{
    for(int i=0; i< tables.size; i++)
    {
        delete tables[i];
    }
    delete tables;

    for(int i=0; i< actionsLog.size; i++)
    {
        delete actionsLog[i];
    }
    delete actionsLog;

}
