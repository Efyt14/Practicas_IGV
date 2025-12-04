#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "cgvInterface.h"

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
    glEnable(GL_TEXTURE_2D); // Enables the use of textures
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

void cgvInterface::keyboardFunc(unsigned char key, int x, int y)
{
    const float TRANSL_STEP = 0.1f;
    const float ROT_STEP = 5.0f; // degrees
    const float SCALE_UP = 1.1f;
    const float SCALE_DOWN = 0.9f;

    int scene = _instance->scene.getCurrentScene();

    switch (key)
    {
        // --- CONTROLES GLOBALES ---
        case 'u':
            _instance->scene.applyTranslation(0.0f, TRANSL_STEP, 0.0f);
            break;
        case 'U':
            _instance->scene.applyTranslation(0.0f, -TRANSL_STEP, 0.0f);
            break;
        case 'w':
            if (scene == 3) {
                _instance->scene.incrX();
            }
            break;
        case 'W':
            if (scene == 3) {
                _instance->scene.decrX();
            }
            break;
        case 'x':
            if (scene == 3) {
                _instance->scene.addCoin();
            } else {
                _instance->scene.incrX();
            }
            break;
        case 'X':
            if (scene == 3) {
                _instance->scene.removeCoin();
            } else {
                if (scene == 2) {
                    if (_instance->scene.getObjetoSeleccionado() == 1) {
                        _instance->scene.selected = 0;
                        _instance->scene.applyRotation(ROT_STEP, 0, 0);
                    } else {
                        _instance->scene.selected = 1;
                        _instance->scene.applyRotation(ROT_STEP, 0, 0);
                    }
                }
                _instance->scene.decrX();
            }
            break;
        case 'y':
            if (_instance->camera.interactiveMode) {
                _instance->camera.rotateY(0.05f);
                _instance->camera.apply();
            } else {
                _instance->scene.incrY();
            }
            break;
        case 'Y':
            if (_instance->camera.interactiveMode) {
                _instance->camera.rotateY(-0.05f);
                _instance->camera.apply();
            } else {
                if (scene == 2) {
                    if (_instance->scene.getObjetoSeleccionado() == 1) {
                        _instance->scene.selected = 0;
                        _instance->scene.applyRotation(0, ROT_STEP, 0);
                    } else {
                        _instance->scene.selected = 1;
                        _instance->scene.applyRotation(0, ROT_STEP, 0);
                    }
                }
                _instance->scene.decrY();
            }
            break;
        case 'z':
            if (scene == 2) {
                if (_instance->scene.getObjetoSeleccionado() == 1) {
                    _instance->scene.selected = 0;
                    _instance->scene.applyRotation(0, 0, ROT_STEP);
                } else {
                    _instance->scene.selected = 1;
                    _instance->scene.applyRotation(0, 0, ROT_STEP);
                }
            }
            _instance->scene.incrZ();
            break;
        case 'Z':
            _instance->scene.decrZ();
            break;
        case 's':
            _instance->scene.applyScaling(SCALE_UP);
            break;
        case 'S':
            _instance->scene.applyScaling(SCALE_DOWN);
            break;
        case 'e': // Activar/desactivar ejes
            _instance->scene.set_axes ( !_instance->scene.get_axes () );
            break;
        case 'v':
            _instance->camera.nextView();
            break;
            // split the window into four views
        case '4':
            _instance->windowChange = !_instance->windowChange;
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
            if (scene == 3) {
                _instance->activationCamera = !_instance->activationCamera;
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
            if (scene == 3){
                _instance->scene.toggleAnimation();
            }
            break;
        case 'q':
        case 'Q':
            _instance->camera.toggleInteractive();
            break;

            //ONLY SCENE 3
        case 'd': // Section E: Increase the R component of the material's diffuse coefficient by 0.1
            if (scene == 3)
            _instance->scene.getMaterial()->incrementDiffuse(0.1);
            break;
        case 'D': // Section E: Decrease the R component of the material's diffuse coefficient by 0.1
            if (scene == 3)
            _instance->scene.getMaterial()->incrementDiffuse(-0.1);
            break;
        case 'r': // Section E: Increase the R component of the material's specular coefficient by 0.1
            if (scene == 3)
            _instance->scene.getMaterial()->incrementSpecular(0.1);
            break;
        case 'R': // Section E: Decrease the R component of the material's specular coefficient by 0.1
            if (scene == 3)
            _instance->scene.getMaterial()->incrementSpecular(-0.1);
            break;
        case 'p': // Section E: Increase the Phong exponent of the material by 10
            if (scene == 3)
            _instance->scene.getMaterial()->incrementExpPhong(10);
            break;
        case 'P': // Section E: Decrease the Phong exponent of the material by 10
            if (scene == 3)
            _instance->scene.getMaterial()->incrementExpPhong(-10);
            break;
    }
    glutPostRedisplay(); // refresh the viewport content
}


void cgvInterface::specialFunc(int key, int x, int y) {
    //Teclas para mover en modo camera
    if (_instance->camera.interactiveMode) {
        switch (key) {
            case GLUT_KEY_LEFT:
                _instance->camera.orbit(-0.05);
                break;
            case GLUT_KEY_RIGHT:
                _instance->camera.orbit(0.05);
                break;
            case GLUT_KEY_UP:
                _instance->camera.pitch(0.05);
                break;
            case GLUT_KEY_DOWN:
                _instance->camera.pitch(-0.05);
                break;
        }
    } else {
        //Teclas para mover en modo normal
        switch (key) {
            case GLUT_KEY_LEFT:
                if (_instance->scene.getCurrentScene() == 3) {
                    _instance->scene.getSpotlight()->move(-0.2, 0, 0);
                }else
                    _instance->scene.applyTranslation(1, 0, 0);
                break;
            case GLUT_KEY_RIGHT:
                if (_instance->scene.getCurrentScene() == 3) {
                    _instance->scene.getSpotlight()->move(0.2, 0, 0);
                }else
                    _instance->scene.applyTranslation(-1, 0, 0); break;
            case GLUT_KEY_UP:
                if (_instance->scene.getCurrentScene() == 3) {
                    _instance->scene.getSpotlight()->move(0, 0.2, 0);
                }else
                    _instance->scene.applyTranslation(0, 0, 1); break;
            case GLUT_KEY_DOWN:
                if (_instance->scene.getCurrentScene() == 3) {
                    _instance->scene.getSpotlight()->move(0, -0.2, 0);
                }else
                    _instance->scene.applyTranslation(0, 0, -1); break;
        }
    }
    glutPostRedisplay();
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
    else if (camera.type == CGV_FRUSTUM) {
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
    // 1. Limpieza inicial
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Obtener dimensiones
    int w = _instance->get_window_width();
    int h = _instance->get_window_height();
    if (w <= 0) w = glutGet(GLUT_WINDOW_WIDTH);
    if (h <= 0) h = glutGet(GLUT_WINDOW_HEIGHT);

    // --- MODO NORMAL (1 sola vista) ---
    if (!_instance->windowChange)
    {
        glViewport(0, 0, w, h);
        _instance->camera.apply(); // Cámara interactiva
        _instance->scene.display();
        glutSwapBuffers();
        return;
    }

    // --- MODO 4 VISTAS ---
    // Calculamos mitad de ancho y alto
    int vw = w / 2;
    int vh = h / 2;

    // Relación de aspecto para las vistas
    double aspect = (double)vw / (double)vh;

    // Radio de visión para la cámara ortogonal (ajústalo según el tamaño de tu escena)
    double radio = 1.5;

    // ===== 1) SUPERIOR IZQUIERDA: CÁMARA MÓVIL (Perspectiva) =====
    glViewport(0, vh, vw, vh);
    _instance->camera.apply(); // Usa la cámara que mueves con el ratón
    _instance->scene.display(); // Dibuja la escena

    // ===== 2) SUPERIOR DERECHA: PLANTA (Vista desde Y) =====
    glViewport(vw, vh, vw, vh);
    // Usamos Ortho para vista técnica 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-radio * aspect, radio * aspect, -radio, radio, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 20, 0,  0, 0, 0,  -1, 0, 0); // Ojo: UP vector ajustado para que no rote raro

    _instance->scene.display();

    // ===== 3) INFERIOR IZQUIERDA: ALZADO (Vista desde Z) =====
    glViewport(0, 0, vw, vh);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-radio * aspect, radio * aspect, -radio, radio, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20,  0, 0, 0,  0, 1, 0);

    _instance->scene.display();

    // ===== 4) INFERIOR DERECHA: PERFIL (Vista desde X) =====
    glViewport(vw, 0, vw, vh);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-radio * aspect, radio * aspect, -radio, radio, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 0, 0,  0, 0, 0,  0, 1, 0);

    _instance->scene.display();

    glutSwapBuffers();
}


void cgvInterface::setPerspectiveProjection(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/**
* Method to animate the scene
*/
void cgvInterface::idleFunc()
{
    // 1. Animación de MODELO (controlada por 'a'/'A')
    _instance->scene.updateAnimation();

    // 2. Animación de CÁMARA (controlada por 'g'/'G')
    if (_instance->activationCamera) {
        _instance->camera.updateCameraAnimation();
    }

    glutPostRedisplay();
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
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            _instance->button_held = true;
            _instance->mode = CGV_SELECT;
            _instance->cursorX = x;
            _instance->cursorY = y;

            glClearColor(0.0, 0.0, 0.0, 0.0);

            // 1. Ponemos la escena en modo selección
            _instance->scene.setSelectionMode(true);

            // 2. Dibujamos (en el back buffer)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            _instance->scene.display();

            // 3. Leemos el color
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            //Definimos un área de picking (ej. 5x5 píxeles)
            const int PICK_REGION_SIZE = 5;
            // Centramos el área en el cursor
            int region_x = x - (PICK_REGION_SIZE / 2);
            int region_y = viewport[3] - y - (PICK_REGION_SIZE / 2);

            // Creamos un buffer para todos los píxeles del área
            GLubyte pixels[PICK_REGION_SIZE * PICK_REGION_SIZE * 3];

            // Leemos el bloque de píxeles
            glReadPixels(region_x, region_y, PICK_REGION_SIZE, PICK_REGION_SIZE, GL_RGB, GL_UNSIGNED_BYTE, pixels);

            glClearColor(1.0, 1.0, 1.0, 0.0); // Restaurar fondo blanco

            // 4. "Votación" para encontrar el ID más común (que no sea 0)
            int id_counts[256] = {0}; // Array para contar IDs (0-255)
            int max_count = 0;
            int selected_id = 0; // ID ganador (0 = fondo)

            for (int i = 0; i < PICK_REGION_SIZE * PICK_REGION_SIZE; ++i) {
                int id = pixels[i * 3]; // Obtenemos el canal Rojo (nuestro ID)
                if (id != 0) { // Ignoramos el fondo
                    id_counts[id]++;
                    if (id_counts[id] > max_count) {
                        max_count = id_counts[id];
                        selected_id = id;
                    }
                }
            }

            // Usamos el 'selected_id' de la votación
            std::cout << "Click X:" << x << " Y:" << y << " -> ID detectado en region: " << selected_id << std::endl;

            if (selected_id == 0) _instance->selected_object = -1;
            else _instance->selected_object = selected_id;

            // 5. Volvemos a modo normal
            _instance->scene.setSelectionMode(false);
            _instance->scene.setObjetoSeleccionado(_instance->selected_object); // Para Escena B
            _instance->scene.setIdToHighlight(_instance->selected_object);     // Para Escena C (Highlight)

            glutPostRedisplay();
        }
        if (state == GLUT_UP)
        {
            _instance->button_held = false;
        }
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
    if (!_instance->button_held || _instance->selected_object <= 0)
        return;

    int diffX = x - _instance->cursorX;
    int diffY = _instance->cursorY - y;

    int scene = _instance->scene.getCurrentScene();
    int id = _instance->selected_object;

    double sensitivity = 0.5;

    if (scene == 2)
    {
        // Bandera (parte 3) usa diffY
        if (id == 3)
            _instance->scene.controlarParte(id, diffY * 0.05);
        else
            _instance->scene.controlarParte(id, diffX * sensitivity);

        _instance->cursorX = x;
        _instance->cursorY = y;
        glutPostRedisplay();
        return;
    }

    if (scene == 3)
    {
        switch (id)
        {
            case 1: // BASE
                _instance->scene.controlarParteSceneC(1, diffX * sensitivity);
                break;

            case 2: // MÁSTIL
                _instance->scene.controlarParteSceneC(2, diffX * sensitivity);
                break;

            case 3: // BANDERA
                _instance->scene.controlarParteSceneC(3, diffY * sensitivity);
                break;

            case 4: // LOGO
                _instance->scene.controlarParteSceneC(4, diffX * sensitivity);
                break;
        }

        _instance->cursorX = x;
        _instance->cursorY = y;
        glutPostRedisplay();
        return;
    }
}

/**
 * Method to initialise GLUT callbacks
 */
void cgvInterface::initialize_callbacks ()
{  glutKeyboardFunc ( keyboardFunc );
    glutReshapeFunc ( reshapeFunc );
    glutDisplayFunc ( displayFunc );
    glutSpecialFunc(specialFunc);
    glutIdleFunc(idleFunc);
    glutMouseFunc( mouseFunc );
    glutMotionFunc(motionFunc);
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
    if(_instance->scene.getCurrentScene() == 3) {
        int texturesMenu = glutCreateMenu(menuHandle);
        glutAddMenuEntry("Textures 1", 41);
        glutAddMenuEntry("Textures 2", 42);
        glutAddMenuEntry("Textures 3", 43);
        glutAddMenuEntry("No texture", 44);

        int materialsMenu = glutCreateMenu(menuHandle);
        glutAddMenuEntry("Material 1", 51);
        glutAddMenuEntry("Material 2", 52);
        glutAddMenuEntry("Material 3", 53);

        int filteringMenu = glutCreateMenu(menuHandle);
        glutAddMenuEntry("MAG: GL_NEAREST", 61);
        glutAddMenuEntry("MAG: GL_LINEAR", 62);
        glutAddMenuEntry("MIN: GL_NEAREST", 63);
        glutAddMenuEntry("MIN: GL_LINEAR", 64);

        int menu_id = glutCreateMenu(menuHandle);
        glutAddMenuEntry("Escena A", 1);
        glutAddMenuEntry("Escena B", 2);
        glutAddMenuEntry("Escena C", 3);

        glutAddSubMenu("Textures", texturesMenu);
        glutAddSubMenu("Materials", materialsMenu);
        glutAddSubMenu("Texture Filtering", filteringMenu);

        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }else{
        int menu_id = glutCreateMenu(menuHandle);
        glutAddMenuEntry("Escena A", 1);
        glutAddMenuEntry("Escena B", 2);
        glutAddMenuEntry("Escena C", 3);

        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void cgvInterface::menuHandle(int value)
{
    switch (value)
    {
        case 1:
            std::cout << "Menu option 1 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneA();
            _instance->create_menu();
            break;
        case 2:
            std::cout << "Menu option 2 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneB();
            _instance->create_menu();
            break;
        case 3:
            std::cout << "Menu option 3 selected\n"; //Log pq no me carga
            _instance->scene.renderSceneC();
            _instance->create_menu();
            break;
    }
}

