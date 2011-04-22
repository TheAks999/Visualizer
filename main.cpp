
#include <iostream>
#include "managizer.h"

using namespace std;


int main(int argc, char *argv[])
{


	QApplication app( argc, argv );

	std::string error;
	switch(Managizer::createSingletons(error))
	{
	case M_CRITICAL:
	    std::cout << error << '\n';
	    return 1;
	case M_NONCRIT:
	    std::cout << error << '\n';
	    std::cout << "Continuing anyways\n";
	default:
	    break;
	}



	switch(Managizer::loadData(error))
	{
	case M_CRITICAL:
	    std::cout << error << '\n';
	    return 1;
	case M_NONCRIT:
	    std::cout << error << '\n';
	    std::cout << "Continuing anyways\n";
	default:
	    break;
	}


	if( argc > 1 )
	{
	    GUI::loadGamelog( argv[1] );
	    TimeManager::timerStart();
	}



	int retval = app.exec();

	Managizer::destroySingletons(error);
	//std::cerr << "Error: " << error << '\n';

	return retval;
}
