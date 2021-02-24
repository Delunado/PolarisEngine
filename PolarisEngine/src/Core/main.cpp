#include <iostream>

#include "Application.h"
#include "Debug.h"

int main(int argc, char** argv) {

	try {
		Application app;
		app.PrintAppInfo();

		Log::PrintMessage("Starting Polaris Engine");
		int appInit = app.Init();

		if (appInit != 0) return appInit;

		Log::PrintMessage("Running Polaris Engine");
		app.Run();

		Log::PrintMessage("Closing Polaris Engine");
		app.Close();
	}
	catch (std::exception & e) {
		Log::PrintMessage(e.what());
		return -4;
	}
}