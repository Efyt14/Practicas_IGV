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
{ private:
    // Attributes
    int window_width = 0; ///< Width of the display window
    int window_height = 0; ///< Height of the display window

    cgvScene3D scene; ///< Scene to display in the window defined by cgvInterface
    cgvCamera camera; ///< Camera used to display the scene

    // Implementing the Singleton design pattern
    static cgvInterface* _instance; ///< Memory address of the class's singleton object
    /// Default constructor
    cgvInterface () = default;
public:
    // Implementing the Singleton Design Pattern
    static cgvInterface& getInstance();
    // Default Constructors and Destructor

    /// Destructor
    ~cgvInterface() = default;

    // Static Methods
    // Event Callbacks
    static void keyboardFunc(unsigned char key, int x, int y); // Method for handling keyboard events
    static void reshapeFunc(int w, int h); // Method that defines the camera and viewport
    // Called automatically when the window is resized
    static void displayFunc(); // Method for displaying the scene

    // Methods
    // Creates the world displayed in the window
    void create_world ();

    // Initializes all parameters for creating a display window
    void configure_environment ( int argc, char **argv // main parameters
    , int _window_width, int _window_height // width and height of the display window
    , int _pos_X, int _pos_Y // initial position of the display window
    , std::string _title // title of the display window
    );
    void initialize_callbacks (); // Initializes all callbacks

    void start_display_loop (); // Displays the scene and waits for events on the interface

    // Get_ and set_ methods for accessing attributes
    int get_window_width();

    int get_window_height();

    void set_window_width(int _window_width);

    void set_window_height(int _window_height);
};
#endif   // __CGVINTERFACE
