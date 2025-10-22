#include <cstdlib>
#include <stdio.h>

#include "cgvInterface.h"
// Singleton design pattern implementation
cgvInterface* cgvInterface::_instance = nullptr;

// Public methods ----------------------------------------

/**
* Method to access the class's singleton object, applying the Singleton design pattern
*
* @return A reference to the class's singleton object
*/
cgvInterface& cgvInterface::getInstance()
{
    if (!_instance)
    {
        _instance = new cgvInterface;
    }

    return *_instance;
}

/**
* Creates the world displayed in the window
*/
void cgvInterface::create_world()
{
    // start the camera
    _instance->camera.set(CGV_PARARELL, {3.0, 2.0, 4}, {0, 0, 0}
    , {0, 1.0, 0}, -1 * 1.5, 1 * 1.5, -1 * 1.5, 1 * 1.5
    , -1 * 3, 200);
}
/**
* Initializes all parameters to create a display window
* @param argc Number of parameters per command line when running the
* application
* @param argv Parameters per command line when running the application
* @param _window_width Initial width of the display window
* @param _window_height Initial height of the display window
* @param _pos_X X coordinate of the initial position of the display * window
* @param _pos_Y Y coordinate of the initial position of the display * window
* @param _title Title of the display window
* @pre All parameters are assumed to be Parameters have valid values
* @post Changes the height and width of the window stored in the object
*/
void cgvInterface::configure_environment(int argc, char** argv, int _window_width
, int _window_height, int _x_pos, int _y_pos
, std::string _title)
{
    // initialize interface variables
    window_width = _window_width;
    window_height = _window_height;

    // initialize the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_window_width, _window_height);
    glutInitWindowPosition(_x_pos, _y_pos);
    glutCreateWindow(_title.c_str());

    glEnable(GL_DEPTH_TEST); // Enables z-buffering of surfaces
    glClearColor(1.0, 1.0, 1.0, 0.0); // Sets the window's background color

    glEnable(GL_LIGHTING); // Enables scene lighting
    glEnable(GL_NORMALIZE); // Normalizes the normal vectors for lighting calculations

    create_world(); // Creates the world to be displayed in the window
}

/**
* Method to display the scene and wait for events on the interface
*/
void cgvInterface::start_display_loop()
{
    glutMainLoop(); // starts the GLUT display loop
}

/**
* Method to handle keyboard events
* @param key Code of the key pressed
* @param x X coordinate of the mouse cursor position at the time of the
* keyboard event
* @param y Y coordinate of the mouse cursor position at the time of the
* keyboard event
* @pre All parameters are assumed to have valid values
* @post Class attributes may change, depending on the key pressed
*/
void cgvInterface::keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x': // Section A: rotate X positive
        _instance->scene.incrX();
        break;
    case 'X': // Section A: rotate negative X
        _instance->scene.decrX();
        break;
    case 'y': // Section A: rotate positive Y
        _instance->scene. incrY();
        break;
    case 'Y': // Section C: rotate negative Y
        _instance->scene. decrY();
        break;
    case 'z': // Section C: rotate positive Z
        _instance->scene. incrZ();
        break;
    case 'Z': // Section C: rotate negative Z
        _instance->scene.decrZ();
        break;
    case 'n':
        _instance->scene.getMesh()->changeNormals();
        break;
    case 'N':
        _instance->scene.getMesh()->changeNormals();
        break;
    case 'g':
        _instance->scene.getMesh()->changeVis();
        break;
    case 'G':
        _instance->scene.getMesh()->changeVis();
        break;

    case 'e': // activate/deactivate the display of the axes
         _instance->scene.set_axes(_instance->scene.get_axes() ? false : true);
        break;
    case 27: // escape key to EXIT
        exit(1);
        break;
    }
    glutPostRedisplay(); // refresh the viewport content
}
/**
* Method that defines the camera and viewport. Called automatically
* when the window is resized.
* @param w New window width
* @param h New window height
* @pre All parameters are assumed to have valid values
*/
void cgvInterface::reshapeFunc(int w, int h)
{
    // Resize the viewport to the new window width and height
    // Save the new viewport values
    _instance->set_window_width(w);
    _instance->set_window_height(h);

    // Set the camera and projection parameters
    _instance->camera.apply();
}
/**
* Method to display the scene
*/
void cgvInterface::displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the window and the z-buffer

    // sets the viewport
    glViewport(0, 0, _instance->get_window_width(), _instance->get_window_height());

    // sets the camera and projection parameters
    _instance->camera.apply();

    // displays the scene
    _instance->scene.display();

    // refreshes the window
    glutSwapBuffers(); // used instead of glFlush() to prevent flickering
}
/**
* Method to initialize GLUT callbacks
*/
void cgvInterface::initialize_callbacks()
{
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
}

/**
* Method to query the display window width
* @return The value stored as the display window width
*/
int cgvInterface::get_window_width()
{
    return window_width;
}
/**
* Method to query the height of the display window
* @return The value stored as the height of the display window
*/
int cgvInterface::get_window_height()
{
    return window_height;
}

/**
* Method to change the width of the display window
* @param _window_width New value for the width of the display window
* @pre Assumes the parameter has a valid value
* @post The window width stored in the application is changed to the new value
*/
void cgvInterface::set_window_width(int _window_width)
{
    window_width = _window_width;
}
/**
* Method to change the display window height
* @param _window_height New value for the display window height
* @pre Assumes the parameter has a valid value
* @post The window height stored in the application is changed to the new value
*/
void cgvInterface::set_window_height(int _window_height)
{
    window_height = _window_height;
}