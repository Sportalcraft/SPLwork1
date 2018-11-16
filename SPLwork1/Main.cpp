#include "Restaurant.h"
#include <iostream>

#include <fstream>
#include <vld.h>

using namespace std;

Restaurant* backup = nullptr;

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "usage: rest <config_path>" << std::endl;
		return 0;
	}
	string configurationFile = argv[1];
	Restaurant rest(configurationFile);
	rest.start();
	
	if (backup != nullptr) {
		delete backup;
		backup = nullptr;
	}

	system("pause");; // in order to wait for the user
	return 0;
}
