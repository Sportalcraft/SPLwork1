#include "Restaurant.h"
#include "Action.h"
#include "Table.h"
#include "Customer.h"
#include "Dish.h"
#include <iostream>
using namespace std;

Restaurant* backup = nullptr;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "usage: rest <config_path>" << endl;
		return 0;
	}
	string configurationFile = argv[1];
	Restaurant rest(configurationFile);
	rest.start();
	if (backup != nullptr) {
		delete backup;
		backup = nullptr;
	}
	return 0;
}
