#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "cgvInterface.h"

//FIXME testear motionFunc y mouseFunc

// Application of the Singleton design pattern
cgvInterface* cgvInterface::_instance = nullptr;

// Public methods ----------------------------------------

/**
 * Method for accessing the single object of the class, applying the Singleton design pattern.
 * @return A reference to the single object of the class.
 */
cgvInterface& cgvInterface::getInstance ()
{  if ( !_instance )
    {  _instance = new cgvInterface;
    }

    return *_instance;
}

/**
 * Creates the world displayed in the window
 */
void cgvInterface::create_world ()
{  // starts the camera
    _instance->camera.set ( CGV_PARALLEL, { 3.0, 2.0, 4 }, { 0, 0, 0 }
            , { 0, 1.0, 0 }, -1 * 1.5, 1 * 1.5, -1 * 1.5, 1 * 1.5
            , -1 * 3, 200 );
}



/**
 * Initialises all parameters to create a display window.
 * @param argc Number of parameters per command line when executing the application.
 *             application.
 * @param argv Command line parameters when running the application.
 * @param _window_width Initial width of the display window.
 * @param _window_height Initial height of the display window.
 * @param _pos_X X coordinate of the initial position of the display window.
 *               display window
 * @param _pos_Y Y coordinate of the initial position of the
 *               display window
 * @param _title Title of the display window
 * @pre It is assumed that all parameters have valid values
 * @post Changes the height and width of the window stored in the object
 */
void cgvInterface::configure_environment ( int argc, char **argv, int _window_width
        , int _window_height, int _pos_X, int _pos_Y
        , std::string _title )
{
    // initialisation of interface variables
    window_width = _window_width;
    window_height = _window_height;

    // initialisation of display window
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize ( _window_width, _window_height );
    glutInitWindowPosition ( _pos_X, _pos_Y );
    glutCreateWindow ( _title.c_str () );

    glEnable ( GL_DEPTH_TEST ); // activates z-buffer surface hiding
    glClearColor( 1.0, 1.0, 1.0, 0.0 ); // sets the window background colour

    glEnable(GL_LIGHTING); // activates scene lighting
    glEnable(GL_NORMALIZE); // normalises normal vectors for lighting calculation

    create_world(); // creates the world to be displayed in the window
}

/**
 * Method to display the scene and wait for events on the interface
 */
void cgvInterface::start_display_loop ()
{  glutMainLoop (); // starts the GLUT display loop
}


/**
 * Method for controlling keyboard events
 * @param key Code of the key pressed
 * @param x X coordinate of the mouse cursor position at the time of the
 *          keyboard event
 * @param y Y coordinate of the mouse cursor position at the time of the
 *          keyboard event
 * @pre All parameters are assumed to have valid values
 * @post Class attributes may change, depending on the key pressed
 */

//FIXME include all letters por the camera movements
void cgvInterface::keyboardFunc(unsigned char key, int x, int y)
{

    int scene = _instance->scene.getCurrentScene();

    switch (key)
    {
        // --- CONTROLES GLOBALES (Siempre funcionan) ---
        case 'x': // Rotar cámara
            _instance->scene.incrX();
            break;
        case 'X':
            _instance->scene.decrX();
            break;
        case 'y':
            _instance->scene.incrY();
            break;
        case 'Y':
            _instance->scene.decrY();
            break;
        case 'z':
            _instance->scene.incrZ();
            break;
        case 'Z':
            _instance->scene.decrZ();
            break;
        case 'e': // Activar/desactivar ejes
            _instance->scene.set_axes ( !_instance->scene.get_axes () );
            break;
        case 'v':
            _instance->camera.nextView();
            break;
        case 27: // Salir
            exit(1);
            break;

            // --- SELECCIÓN DE OBJETO (Sólo Escena B) ---
        case '1':
            if (scene == 2) _instance->scene.setObjetoSeleccionado(1);
            break;
        case '2':
            if (scene == 2) _instance->scene.setObjetoSeleccionado(2);
            break;

            // --- 'g' / 'G' (Solo Escena A) ---
        case 'g':
        case 'G':
            if (scene == 1 && _instance->scene.getMesh() != nullptr) {
                _instance->scene.getMesh()->changeShader();
            }
            break;

            // --- 'n' / 'N' (Escena A vs Escena B) ---
        case 'n':
            if (scene == 1 && _instance->scene.getMesh() != nullptr) {
                _instance->scene.getMesh()->changeNormal(); // Práctica 1
            } else if (scene == 2) {
                _instance->scene.controlarParte(4, 5.0); // Práctica 2: Logo / Branquias V
            }
            break;
        case 'N':
            if (scene == 1 && _instance->scene.getMesh() != nullptr) {
                _instance->scene.getMesh()->changeNormal(); // Práctica 1
            } else if (scene == 2) {
                _instance->scene.controlarParte(4, -5.0); // Práctica 2
            }
            break;

            // --- 'b' / 'B' (Escena A vs Escena B) ---
        case 'b':
            if (scene == 2) {
                _instance->scene.controlarParte(1, 5.0); // Práctica 2: Base
            }
            break;
        case 'B':
            if (scene == 2) {
                _instance->scene.controlarParte(1, -5.0); // Práctica 2
            }
            break;

            // --- 'c' / 'C' (Escena A vs Escena B) ---
        case 'c':
            if (scene == 2) {
                _instance->scene.controlarParte(2, 5.0); // Práctica 2: Mástil / Cabeza
            }
            break;
        case 'C':
            if (scene == 2) {
                _instance->scene.controlarParte(2, -5.0); // Práctica 2
            }
            break;

            // --- 'm' / 'M' (Escena A vs Escena B) ---
        case 'm':
            if (scene == 2) {
                _instance->scene.controlarParte(3, 5.0); // Práctica 2: Bandera / Branquias H
            }
            break;
        case 'M':
            if (scene == 2) {
                _instance->scene.controlarParte(3, -5.0); // Práctica 2
            }
            break;
        case 'A':
        case 'a':
            if (scene == 2){
                _instance->scene.toggleAnimation();
            }
            break;
    }
    glutPostRedisplay(); // refresh the viewport content
}


/**
 * Method that defines the camera and viewport. It is called automatically
 * when the window size is changed.
 * @param w New window width
 * @param h New window height
 * @pre All parameters are assumed to have valid values
 */
void cgvInterface::reshapeFunc ( int w, int h )
{  // resizes the viewport to the new window width and height
    // save new values for the display window
    _instance->set_window_width ( w );
    _instance->set_window_height ( h );

    // sets the camera and projection parameters
    _instance->camera.apply ();
}

/**
 * Method for displaying the scene
 */
void cgvInterface::displayFunc ()
{  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clears the window and the z-buffer

    // set the viewport
    glViewport ( 0, 0, _instance->get_window_width (), _instance->get_window_height () );

    // set the camera and projection parameters
    _instance->camera.apply ();

    //display the scene
    _instance->scene.display();

    // refresh the window
    glutSwapBuffers (); // used instead of glFlush() to prevent flickering
}

/**
* Method to animate the scene
*/
void cgvInterface::idleFunc()
{
    _instance->scene.updateAnimation();
    glutPostRedisplay();
}

/**
 * Method to initialise GLUT callbacks
 */
void cgvInterface::initialize_callbacks ()
{  glutKeyboardFunc ( keyboardFunc );
    glutReshapeFunc ( reshapeFunc );
    glutDisplayFunc ( displayFunc );
    glutIdleFunc(idleFunc);
}

/**
 * Method to query the width of the display window
 * @return The value stored as the width of the display window
 */
int cgvInterface::get_window_width ()
{  return window_width;
}

/**
 * Method to query the height of the display window
 * @return The value stored as the height of the display window
 */
int cgvInterface::get_window_height ()
{  return window_height;
}

/**
 * Method to change the width of the display window
 * @param _window_width New value for the width of the display window
 * @pre It is assumed that the parameter has a valid value
 * @post The window width stored in the application changes to the new value
 */
void cgvInterface::set_window_width ( int _window_width )
{  window_width = _window_width;
}

/**
 * Method to change the height of the display window
 * @param _window_height New value for the height of the display window
 * @pre It is assumed that the parameter has a valid value
 * @post The window height stored in the application changes to the new value
 */
void cgvInterface::set_window_height ( int _window_height )
{  window_height = _window_height;
}


void cgvInterface::create_menu() {
    int menu_id = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Escena A", 1);
    glutAddMenuEntry("Escena B", 2);
    glutAddMenuEntry("Escena C", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void cgvInterface::menuHandle(int value)
{
    switch (value)
    {
        case 1:
            std::cout << "Menu option 1 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneA();
            break;
        case 2:
            std::cout << "Menu option 2 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneB();
            break;
        case 3:
            std::cout << "Menu option 3 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneC();
            break;
    }
}

/**
* Method for handling mouse clicks
* @param button Identifies the button that was clicked. Can be
* GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
* @param state Describes whether the button was pressed (GLUT_DOWN) or released
* (GLUT_UP)
* @param x X coordinate of the viewport pixel where the click was made
* @param y Y coordinate of the viewport pixel where the click was made
* @post Updates the interface state
*/
void cgvInterface::mouseFunc(GLint button, GLint state, GLint x, GLint y)
{
    // Section A: Check that the left button has been pressed
    if (button == GLUT_LEFT_BUTTON)
    {
        // Section A: Save that the button has been pressed or released. If it has been pressed, it must be
        // Switch to IGV_SELECT mode
        if (state == GLUT_DOWN)
        {
            _instance->button_held = true;
            _instance->mode = CGV_SELECT;
        }

        if (state == GLUT_UP)
        {
            _instance->button_held = false;
        }

        // Section A: Save the pressed pixel
        _instance->cursorX = x;
        _instance->cursorY = y;
        // Section A: Refresh the contents of the viewing window
        glutPostRedisplay();
    }
}
/**
* Method for controlling mouse movement with a button pressed
* @param x X coordinate of the mouse cursor position in the window
* @param y Y coordinate of the mouse cursor position in the window
* @post The interface state is updated
*/
void cgvInterface::motionFunc(GLint x, GLint y)
{
    // Section B: If the button is held and an object is selected,
    // check the selected object and the mouse position and update
    // the corresponding object's degree of freedom accordingly
    if (_instance->button_held)
    {
        if (_instance->selected_object >= 0) {
            // FIXME, en vez de selecccionar una Box tiene que definir cualquiera de los objetos que forman la bandera
            // _instance->scene.getBoxes()[_instance->selected_object]->rotateY(_instance->cursorX - x);
        }

        // Section B: Save the new mouse position
        _instance->cursorX = x;
        _instance->cursorY = y;

        // Section B: Refresh the contents of the viewport
        displayFunc();
    }
}