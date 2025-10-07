#include <cstdlib>

#include "cgvInterface.h"

cgvInterface interface;


//NOTE REFACTORIZAR TODO LO QUE TENGA INSTANCE POR INTERFACE

cgvInterface* cgvInterface::_instance = nullptr;

// Constructor Methods -----------------------------------

/**
* Default constructor
*/
cgvInterface::cgvInterface(): menuSelection(scene.SceneA), pos(1), windowChange(false) {}


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

    create_world();// Añadido para la practica 2
}

/**
* Creates a menu bound to the right mouse button
*/
void cgvInterface::create_menu ()
{ int menu_id = glutCreateMenu ( menuHandle );
    glutAddMenuEntry ( interface.scene.Scene_NameA
            , interface.scene.SceneA );
    glutAddMenuEntry ( interface.scene.Scene_NameB
            , interface.scene.SceneB );
    glutAddMenuEntry ( interface.scene.Scene_NameC
            , interface.scene.SceneC );

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
        case 'e':
        case 'E':
            interface.scene.set_axes(!interface.scene.get_axes());
            break;


        case '1': // select Scene A / object 0
            interface.menuSelection = interface.scene.SceneA;
            interface.scene.selected = 0;
            break;
        case '2':
            interface.menuSelection = interface.scene.SceneB;
            interface.scene.selected = 1;
            break;
        case '3':
            interface.menuSelection = interface.scene.SceneC;
            interface.scene.selected = 2;
            break;


        case 27:
            exit(1);
            break; // ESC

            // Traslación en Y
        case 'u':
            interface.scene.applyTranslation(0.0f, TRANSL_STEP, 0.0f);
            break;
        case 'U':
            interface.scene.applyTranslation(0.0f, -TRANSL_STEP, 0.0f);
            break;


            // Rotación
        case 'x':
            interface.scene.applyRotation(ROT_STEP, 0, 0);
            break;
        case 'X':
            interface.scene.applyRotation(-ROT_STEP, 0, 0);
            break;
        case 'y':
        case 'Y':
            if (interface.camera.interactiveMode) {
                //Practica 2
                // Si el modo interactivo está activo, rota la cámara
                if (key == 'y') {
                    interface.camera.rotateY(0.05f);
                } else {
                    interface.camera.rotateY(-0.05f);
                }
                interface.camera.apply();
            } else {
                // Si no, rota la escena como antes
                if (key == 'y') interface.scene.applyRotation(0, ROT_STEP, 0);
                else interface.scene.applyRotation(0, -ROT_STEP, 0);
            }
            break;
        case 'z':
            interface.scene.applyRotation(0, 0, ROT_STEP);
            break;
        case 'Z':
            interface.scene.applyRotation(0, 0, -ROT_STEP);
            break;

            // Escalado
        case 's':
            interface.scene.applyScaling(SCALE_UP);
            break;
        case 'S':
            interface.scene.applyScaling(SCALE_DOWN);
            break;

            // Cambio de modo
        case 'm':
            interface.scene.deferredMode = false; // libre
            // Al cambiar a libre, si había acumuladas, ejecutarlas
            for (int i = 0; i < interface.scene.ops[interface.scene.selected].size(); ++i) {
                std::function<void()>& op = interface.scene.ops[interface.scene.selected][i];
                op();
            }
            interface.scene.ops[interface.scene.selected].clear();
            break;

        case 'M':
            interface.scene.deferredMode = true;  // diferido
            break;

            //Practica 2

        case 'p': // change the projection type from parallel to perspective and vice versa
        case 'P':
            if (interface.camera.type == CGV_PARALLEL) { // Perspective mode
                interface.camera.set(CGV_PERSPECTIVE,
                                     interface.camera.P0,
                                     interface.camera.r,
                                     interface.camera.V,
                                     interface.camera.angle,
                                     interface.camera.aspect,
                                     interface.camera.znear,
                                     interface.camera.zfar
                );
            } else {
                interface.camera.set(CGV_PARALLEL,
                                     interface.camera.P0,
                                     interface.camera.r,
                                     interface.camera.V,
                                     interface.camera.xwmin,
                                     interface.camera.xwmax,
                                     interface.camera.ywmin,
                                     interface.camera.ywmax,
                                     interface.camera.znear,
                                     interface.camera.zfar
                );
            }
            interface.camera.apply();
            break;

        case 'v': // Change the camera position to display plan, profile, elevation, or perspective views
        case 'V':
            // mantener interface.pos entre 0..3 y actualizar la cámara en consecuencia TODO NO VA 😭😭
            interface.pos = (interface.pos + 1) % 4;
            interface.update_camera_view(interface.pos);
            break;

            //Zooms
        case '+': // zoom in
            interface.camera.zoom(0.95);
            interface.camera.apply();
            break;
        case '-': // zoom out
            interface.camera.zoom(1.05);
            interface.camera.apply();
            break;

            //Planes play
        case 'n': // increase the distance of the near plane
            interface.camera.znear += 0.2;
            interface.camera.apply();
            break;
        case 'N': // decrease the distance of the near plane
            interface.camera.znear -= 0.2;
            interface.camera.apply();
            break;

            // split the window into four views
        case '4':
            interface.windowChange = !interface.windowChange;
            break;

            //Camera type
        case 'c':
        case 'C':
            interface.camera.toggleInteractive();
            break;

            //Near and Far plane Play (F = N?)
        case 'f':
            interface.camera.moveNear(0.1);
            break;
        case 'F':
            interface.camera.moveNear(-0.1);
            break;

            //DISCLAIMER: Tarda mucho mucho en que el far plane corte la figura
        case 'b':
            interface.camera.moveFar(0.1);
            break;
        case 'B':
            interface.camera.moveFar(-0.1);
            break;
    }
    glutPostRedisplay();
}

void cgvInterface::specialFunc(int key, int x, int y) {
    //Teclas para mover en modo camera
    if (interface.camera.interactiveMode) {
        switch (key) {
            case GLUT_KEY_LEFT:
                interface.camera.orbit(-0.05);
                break;
            case GLUT_KEY_RIGHT:
                interface.camera.orbit(0.05);
                break;
            case GLUT_KEY_UP:
                interface.camera.pitch(0.05);
                break;
            case GLUT_KEY_DOWN:
                interface.camera.pitch(-0.05);
                break;
        }
    } else {
        //Teclas para mover en modo normal
        switch (key) {
            case GLUT_KEY_LEFT:  interface.scene.applyTranslation(1, 0, 0); break;
            case GLUT_KEY_RIGHT: interface.scene.applyTranslation(-1, 0, 0); break;
            case GLUT_KEY_UP:    interface.scene.applyTranslation(0, 0, 1); break;
            case GLUT_KEY_DOWN:  interface.scene.applyTranslation(0, 0, -1); break;
        }
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
    interface.set_window_width ( w );
    interface.set_window_height ( h );

// sets the projection type to use
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1*5, 1*5, -1*5, 1*5, -1*5, 200);

// define the view camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.5, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // perspective view
// gluLookAt(1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // plan view from the positive X axis

    //Practica 2

    // Size the viewport to the new window width and height
    // Save the new viewport values
    interface.set_window_width(w);
    interface.set_window_height(h);

    // Set the camera and projection parameters
    interface.camera.apply();
}

void apply_local_camera(
        const cgvCamera& camera,
        int vw, int vh,
        const cgvPoint3D& eye,
        const cgvPoint3D& center,
        const cgvPoint3D& up)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (camera.type == CGV_PARALLEL) {
        glOrtho(camera.xwmin, camera.xwmax,
                camera.ywmin, camera.ywmax,
                camera.znear, camera.zfar);
    }
    else if (camera.type == CGV_FRUSTRUM) {
        glFrustum(camera.xwmin, camera.xwmax,
                  camera.ywmin, camera.ywmax,
                  camera.znear, camera.zfar);
    }
    else { // perspective
        double asp;
        if (vw == 0 || vh == 0)
            asp = camera.aspect;
        else
            asp = vw/vh;

        gluPerspective(camera.angle, asp, camera.znear, camera.zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[X], eye[Y], eye[Z],
              center[X], center[Y], center[Z],
              up[X], up[Y], up[Z]);
}


/**
* Method for displaying the scene
*/
void cgvInterface::displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int w = interface.get_window_width();
    int h = interface.get_window_height();
    if (w <= 0) w = glutGet(GLUT_WINDOW_WIDTH);
    if (h <= 0) h = glutGet(GLUT_WINDOW_HEIGHT);

    GLfloat light0[] = { 10.0f, 8.0f, 9.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    if (!interface.windowChange) {
        // ---- Vista normal ----
        glViewport(0, 0, w, h);
        interface.camera.apply();
        interface.scene.renderSceneContent(interface.menuSelection);
    }
    else { //TODO Pertracala infame, canallesco 😤😤
        // ---- Vista 4 ventanas ----
        int vw = w / 2;
        int vh = h / 2;

        // 1) Perspectiva / interactiva (arriba izquierda)
        glViewport(0, h - vh, vw, vh);
        interface.camera.apply();
        interface.scene.renderSceneContent(interface.menuSelection);

        // 2) Planta (arriba derecha)
        glViewport(vw, h - vh, vw, vh);
        apply_local_camera(interface.camera, vw, vh,
                           cgvPoint3D(0.0, 5.0, 0.0),
                           cgvPoint3D(0.0, 0.0, 0.0),
                           cgvPoint3D(0.0, 0.0, -1.0));
        interface.scene.renderSceneContent(interface.menuSelection);

        // 3) Alzado (abajo izquierda)
        glViewport(0, 0, vw, vh);
        apply_local_camera(interface.camera, vw, vh,
                           cgvPoint3D(0.0, 0.0, 5.0),
                           cgvPoint3D(0.0, 0.0, 0.0),
                           cgvPoint3D(0.0, 1.0, 0.0));
        interface.scene.renderSceneContent(interface.menuSelection);

        // 4) Perfil (abajo derecha)
        glViewport(vw, 0, vw, vh);
        apply_local_camera(interface.camera, vw, vh,
                           cgvPoint3D(5.0, 0.0, 0.0),
                           cgvPoint3D(0.0, 0.0, 0.0),
                           cgvPoint3D(0.0, 1.0, 0.0));
        interface.scene.renderSceneContent(interface.menuSelection);
    }

    glutSwapBuffers();
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

void cgvInterface::create_world(void) {
    // crear camaras
    p0 = cgvPoint3D(3.0, 2.0, 4);
    r = cgvPoint3D(0, 0, 0);
    V = cgvPoint3D(0, 1.0, 0);

    interface.camera.set(CGV_PARALLEL, p0, r, V,
                         -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);

    //perspective parameters
    interface.camera.angle = 60.0;
    interface.camera.aspect = 1.0;
}

//TODO arreglar
void cgvInterface::update_camera_view(int pos) {
    //Que este solo de 0 a 3
    int p = pos % 4;
    if (p < 0) p += 4;

    cgvPoint3D eye, center(0,0,0), up;

    // Definición de las 4 vistas:
    // 0 = vista "original" (usamos p0,r,V ya definidos en create_world)
    // 1 = planta (desde +Y)
    // 2 = perfil (desde +X)
    // 3 = alzado (desde +Z)
    switch (p) {
        case 0:
            eye = p0;        // conserva la posición original
            center = r;
            up = V;
            break;
        case 1: // planta (desde arriba)
            eye = cgvPoint3D(0.0, 5.0, 0.0);
            center = cgvPoint3D(0.0, 0.0, 0.0);
            // up hacia -Z para que la planta "mire" con X a la derecha
            up = cgvPoint3D(0.0, 0.0, -1.0);
            break;
        case 2: // perfil (desde +X)
            eye = cgvPoint3D(5.0, 0.0, 0.0);
            center = cgvPoint3D(0.0, 0.0, 0.0);
            up = cgvPoint3D(0.0, 1.0, 0.0);
            break;
        case 3: // alzado (desde +Z)
            eye = cgvPoint3D(0.0, 0.0, 5.0);
            center = cgvPoint3D(0.0, 0.0, 0.0);
            up = cgvPoint3D(0.0, 1.0, 0.0);
            break;
    }

    // Aplicamos sin cambiar innecesariamente parámetros de proyección:
    if (interface.camera.type == CGV_PARALLEL || interface.camera.type == CGV_FRUSTRUM) {
        // mantenemos xwmin/xwmax/ywmin/ywmax/znear/zfar
        interface.camera.set(
                interface.camera.type,
                eye, center, up,
                interface.camera.xwmin, interface.camera.xwmax,
                interface.camera.ywmin, interface.camera.ywmax,
                interface.camera.znear, interface.camera.zfar
        );
    } else { // CGV_PERSPECTIVE
        // preservamos angle, aspect, znear, zfar
        double aspect = interface.camera.aspect;
        interface.camera.set(
                CGV_PERSPECTIVE,
                eye, center, up,
                interface.camera.angle, aspect,
                interface.camera.znear, interface.camera.zfar
        );
    }

    // aplicamos la cámara resultante (actualiza matrices)
    interface.camera.apply();
}