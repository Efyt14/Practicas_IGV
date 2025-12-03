#include <cstdlib>

#include "cgvInterface.h"

int main ( int argc, char **argv )
{

   // initialize the display window
   cgvInterface::getInstance().configure_environment ( argc, argv
                                                  , 500, 500 // window size
                                                  , 100, 100 // window position
                                                  , "IG&V. Practice 3." // window title
    );

   // set the callback functions for event management
   cgvInterface::getInstance().initialize_callbacks();

    // activa el menú
    cgvInterface::getInstance().create_menu();

   // start the GLUT display loop
   cgvInterface::getInstance().start_display_loop();



   return ( 0 );
}
