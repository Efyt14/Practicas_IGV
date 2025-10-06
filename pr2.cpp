#include <cstdlib>

#include "cgvInterface.h"


int main (int argc, char** argv) {
	// initializes the display window
    cgvInterface::getInstance().configure_environment( argc, argv
                                                    , 500, 500 // window size
                                                    , 100, 100 // window position
                                                    , "CGIV: Practice 2" // window title
   );

	// sets the callback functions for event management
    cgvInterface::getInstance().initialize_callbacks();

	// start the GLUT display loop
    cgvInterface::getInstance().start_display_loop();

	return(0);
}
