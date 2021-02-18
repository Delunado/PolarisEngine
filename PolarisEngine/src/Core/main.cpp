#include <iostream>

#include "Application.h"
#include "Debug.h"

int main(int argc, char** argv) {

	try {
		Application app;
		app.PrintAppInfo();

		std::cout << "Starting Polaris Engine" << std::endl;
		int appInit = app.Init();

		if (appInit != 0) return appInit;

		std::cout << "Running Polaris Engine" << std::endl;
		app.Run();

		std::cout << "Closing Polaris Engine" << std::endl;
		app.Close();

	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return -4;
	}
}