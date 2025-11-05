#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>

#include "cgvScene3D.h"
#include "cgvCamera.h"


/**
 * Objects of this class encapsulate the interface and state of the application.
 */
class cgvInterface
{  private:
    // Attributes
    int window_width = 0; ///< Width of the display window
    int window_height = 0;  ///< Height of the display window

    cgvScene3D scene; ///< Scene displayed in the window defined by cgvInterface
    cgvCamera camera; ///< Camera used to display the scene

    // Application of the Singleton design pattern
    static cgvInterface* _instance; ///< Memory address of the single object of the class
    /// Default constructor
    cgvInterface () = default;


public:
    // Application of the Singleton design pattern
    static cgvInterface& getInstance ();
    // Default constructors and destructor

    /// Destructor
    ~cgvInterface () = default;

    // Static methods
    // Event callbacks
    // Event callbacks
    static void keyboardFunc ( unsigned char key, int x, int y ); // Method for controlling keyboard events
    static void reshapeFunc ( int w, int h ); // Method that defines the camera and viewport
    // called automatically when the window size is changed
    static void displayFunc (); // method for displaying the scene
    static void idleFunc (); // method to animate the scene



    // Methods
    // creates the world displayed in the window
    void create_world ();

    // initialise all parameters to create a display window
    void configure_environment ( int argc, char **argv // main parameters
                           , int _window_width, int _window_height // width and height of the display window
                           , int _pos_X, int _pos_Y // initial position of the display window
                           , std::string _title // title of the display window
                           );
    void initialize_callbacks (); // initialise all callbacks

    void start_display_loop (); // display the scene and wait for events on the interface

    // get_ and set_ methods for accessing attributes
    int get_window_width ();

    int get_window_height ();

    void set_window_width ( int _window_width );

    void set_window_height ( int _window_height );

    //Para la creacion del menu, que cada apartado esté en una escena
    void create_menu();
    static void menuHandle(int value);
};

#endif   // __CGVINTERFACE
