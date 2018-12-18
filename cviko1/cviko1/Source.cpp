#include <stdlib.h>
#include "Application.h"

int main(int argc, char* argv[])
{
	Application *app;
	app = app->getInstance();

	if (!app->init(argc, argv)) {
		exit(EXIT_FAILURE);
	}

	app->callBackFunctions();

	app->draw();
	return 0;
}