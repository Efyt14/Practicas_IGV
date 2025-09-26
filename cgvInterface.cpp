#include <cstdlib>

#include "cgvInterface.h"

// Singleton Pattern Application
cgvInterface* cgvInterface::_instance = nullptr;

// Constructor Methods -----------------------------------

/**
* Default constructor
*/
cgvInterface::cgvInterface(): menuSelection(scene.SceneA)
{}

// Public methods ----------------------------------------

/**
* Method to access the class's singleton object, applying the Singleton
* design pattern
* @return A reference to the class's singleton object
*/
cgvInterface& cgvInterface::getInstance()
{ if ( !_instance )
    { _instance = new cgvInterface;
    }

    return *_instance;
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
void cgvInterface::configure_environment (int argc, char** argv
        , int _window_width, int _window_height
        , int _x_pos, int _y_pos
        , std::string _title )
{ // initialize interface attributes
    window_width = _window_width;
    window_height = _window_height;

// initialize the display window
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize ( _window_width, _window_height );
    glutInitWindowPosition ( _x_pos, _y_pos );
    glutCreateWindow( _title.c_str() );

    create_menu();

    glEnable( GL_DEPTH_TEST ); // enable z-buffer surface hiding
    glClearColor( 1.0, 1.0, 1.0, 0.0 ); // set the window background color

    glEnable( GL_LIGHTING ); // enable scene lighting
    glEnable( GL_NORMALIZE ); // normalize normal vectors for lighting calculations
}

/**
* Creates a menu bound to the right mouse button
*/
void cgvInterface::create_menu ()
{ int menu_id = glutCreateMenu ( menuHandle );
    glutAddMenuEntry ( _instance->scene.Scene_NameA
            , _instance->scene.SceneA );
    glutAddMenuEntry ( _instance->scene.Scene_NameB
            , _instance->scene.SceneB );
    glutAddMenuEntry ( _instance->scene.Scene_NameC
            , _instance->scene.SceneC );

    glutAttachMenu ( GLUT_RIGHT_BUTTON );
}

/**
* Method to display the scene and wait for events on the interface
*/
void cgvInterface::start_display_loop()
{ glutMainLoop(); // starts the GLUT display loop
}

/**
* Method for handling keyboard events
* @param key Code of the key pressed
* @param x X coordinate of the mouse cursor position at the time of the
* keyboard event
* @param y Y coordinate of the mouse cursor position at the time of the
* keyboard event
* @pre All parameters are assumed to have valid values
* @post The scene may change depending on the key pressed
*/
void cgvInterface::keyboardFunc (unsigned char key, int x, int y) {
    const float TRANSL_STEP = 0.1f;
    const float ROT_STEP = 5.0f; // degrees
    const float SCALE_UP = 1.1f;
    const float SCALE_DOWN = 0.9f;


    switch ( key ) {
        case 'e': case 'E':
            _instance->scene.set_axes(!_instance->scene.get_axes());
            break;


        case '1': // select Scene A / object 0
            _instance->menuSelection = _instance->scene.SceneA;
            _instance->scene.selected = 0;
            break;
        case '2':
            _instance->menuSelection = _instance->scene.SceneB;
            _instance->scene.selected = 1;
            break;
        case '3':
            _instance->menuSelection = _instance->scene.SceneC;
            _instance->scene.selected = 2;
            break;


        case 27: exit(1); break; // ESC


    // Traslación en Y
        case 'u': _instance->scene.applyTranslation(0.0f, TRANSL_STEP, 0.0f); break;
        case 'U': _instance->scene.applyTranslation(0.0f, -TRANSL_STEP, 0.0f); break;


    // Rotación
        case 'x': _instance->scene.applyRotation( ROT_STEP,0,0); break;
        case 'X': _instance->scene.applyRotation(-ROT_STEP,0,0); break;
        case 'y': _instance->scene.applyRotation(0, ROT_STEP,0); break;
        case 'Y': _instance->scene.applyRotation(0,-ROT_STEP,0); break;
        case 'z': _instance->scene.applyRotation(0,0, ROT_STEP); break;
        case 'Z': _instance->scene.applyRotation(0,0,-ROT_STEP); break;


    // Escalado
        case 's': _instance->scene.applyScaling(SCALE_UP); break;
        case 'S': _instance->scene.applyScaling(SCALE_DOWN); break;


    // Cambio de modo
        case 'm':
            _instance->scene.deferredMode = false; // libre
            // Al cambiar a libre, si había acumuladas, ejecutarlas
            for (auto &op : _instance->scene.ops[_instance->scene.selected]) {
                op();
            }
            _instance->scene.ops[_instance->scene.selected].clear();
            break;

        case 'M':
            _instance->scene.deferredMode = true;  // diferido
            break;
    }
    glutPostRedisplay();
}

void cgvInterface::specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  _instance->scene.applyTranslation(1, 0, 0); break;
        case GLUT_KEY_RIGHT: _instance->scene.applyTranslation(-1, 0, 0); break;
        case GLUT_KEY_UP:    _instance->scene.applyTranslation(0, 0, 1); break;
        case GLUT_KEY_DOWN:  _instance->scene.applyTranslation(0, 0, -1); break;
    }
    glutPostRedisplay();
}

/**
* Method that defines the camera and viewport. Called automatically
* when the window is resized.
* @param w New window width
* @param h New window height
* @pre All parameters are assumed to have valid values
*/
void cgvInterface::reshapeFunc (int w, int h)
{ // reshape the viewport to the new window width and height
    glViewport ( 0, 0, (GLsizei) w, (GLsizei) h );

// save the new viewport values
    _instance->set_window_width ( w );
    _instance->set_window_height ( h );

// sets the projection type to use
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1*5, 1*5, -1*5, 1*5, -1*5, 200);

// define the view camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.5, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // perspective view
// gluLookAt(1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // plan view from the positive X axis
}

/**
* Method for displaying the scene
*/
void cgvInterface::displayFunc ()
{ _instance->scene.display( _instance->menuSelection );
}

/**
* Method for managing menu option selection
* @param value New selected option
* @pre Assumes the parameter value is correct
* @post Stores the selected option in the object
*/
void cgvInterface::menuHandle (int value )
{ _instance->menuSelection = value;
    glutPostRedisplay (); // renew the contents of the window
}


/**
* Method to initialize callbacks
*/
void cgvInterface::initialize_callbacks()
{ glutKeyboardFunc ( keyboardFunc );
    glutSpecialFunc(specialFunc);
    glutReshapeFunc ( reshapeFunc );
    glutDisplayFunc ( displayFunc );
}

/**
* Method to query the display window width
* @return The value stored as the display window width
*/
int cgvInterface::get_window_width ()
{ return window_width;
}

/**
* Method to query the height of the display window
* @return The value stored as the height of the display window
*/
int cgvInterface::get_window_height ()
{ return window_height;
}

/**
* Method to change the width of the display window
* @param _window_width New value for the width of the display window
* @pre Assumes the parameter has a valid value
* @post The window width stored in the application is changed to the new value
*/
void cgvInterface::set_window_width (int _window_width )
{ window_width = _window_width;
}

/**
* Method to change the display window height
* @param _window_height New value for the display window height
* @pre Assumes the parameter has a valid value
* @post The window height stored in the application is changed to the new value
*/
void cgvInterface::set_window_height (int _window_height )
{ window_height = _window_height;
}