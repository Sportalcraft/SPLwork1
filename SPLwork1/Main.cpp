#include "Restaurant.h"
#include <iostream>

using namespace std;

Restaurant* backup = nullptr;

int main(int argc, char** argv) {
//	if (argc != 2) {
//		std::cout << "usage: rest <config_path>" << std::endl;
//		return 0;
//	}
//	string configurationFile = argv[1];
//	Restaurant rest(configurationFile);
//	rest.start();
//	if (backup != nullptr) {
//		delete backup;
//		backup = nullptr;
//	}

	Table t(3);
	Customer* c = new CheapCustomer("Tal", 123);
	t.addCustomer(c);
	Customer* c2 = t.getCustomers()[0];
	
	if (c == c2)
		throw new exception("no new object");

	return 0;
}
