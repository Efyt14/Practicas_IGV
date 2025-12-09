//#include <GL/glut.h>
#include <math.h>

#include "cgvCamera.h"


// Constructor methods

/**
 * Parameterised constructor
 * @param _type Camera type (IGV_PARALLEL, IGV_FRUSTUM or IGV_PERSPECTIVE)
 * @param _P0 Camera position (viewpoint)
 * @param _r Point at which the camera is looking (reference point)
 * @param _V Vector indicating the vertical
 * @pre It is assumed that all parameters have valid values
 * @post The attributes of the new camera will be the same as the parameters that are
 *       passed to it
 */
cgvCamera::cgvCamera ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r
        , cgvPoint3D _V ): P0 ( _P0 ), r ( _r ), V ( _V )
        , type ( _type )
{ }

// Public methods
/**
 * Defines the position of the camera
 * @param _P0 Position of the camera (viewpoint)
 * @param _r Point at which the camera is looking (reference point)
 * @param _V Vector indicating the vertical
 * @pre All parameters are assumed to have valid values
 * @post The camera attributes change to the values passed as parameters
 */
void cgvCamera::set ( cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V )
{  P0 = _P0;
    r  = _r;
    V  = _V;

    P0Panoramic = P0;
    rPanoramic = r;
    vPanoramic = V;
}


/**
 * Defines a parallel or frustum camera type.
 * @param _type Camera type (IGV_PARALLEL or IGV_FRUSTUM)
 * @param _P0 Camera position
 * @param _r Point at which the camera is looking
 * @param _V Vector indicating the vertical
 * @param _xwmin Minimum X coordinate of the frustum
 * @param _xwmax Maximum X coordinate of the frustum
 * @param _ywmin Minimum Y coordinate of the frustum
 * @param _ywmax Maximum Y coordinate of the frustum
 * @param _znear Distance from the camera to the near Z plane
 * @param _zfar Distance from the camera to the far Z plane
 * @pre It is assumed that all parameters have valid values
 * @post The camera attributes change to the values passed as parameters
 */
void cgvCamera::set ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r
        , cgvPoint3D _V, double _xwmin, double _xwmax, double _ywmin
        , double _ywmax, double _znear, double _zfar )
{  type = _type;

    P0 = _P0;
    r  = _r;
    V  = _V;

    xwmin = _xwmin;
    xwmax = _xwmax;
    ywmin = _ywmin;
    ywmax = _ywmax;
    znear = _znear;
    zfar  = _zfar;

    P0Panoramic = P0;
    rPanoramic = r;
    vPanoramic = V;
}

/**
 * Defines a perspective camera
 * @param _type Camera type (IGV_PERSPECTIVE)
 * @param _P0 Camera position
 * @param _r Point at which the camera is looking
 * @param _V Vector indicating the vertical
 * @param _angle Angle of aperture
 * @param _raspecto Aspect ratio
 * @param _znear Distance from the camera to the Z near plane
 * @param _zfar Distance from the camera to the Z far plane
 * @pre All parameters are assumed to have valid values
 * @post The camera attributes change to the values passed as
 *       parameters
 */
void cgvCamera::set ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r
        , cgvPoint3D _V, double _angle, double _aspectRatio
        , double _znear, double _zfar )
{  type = _type;

    P0 = _P0;
    r  = _r;
    V  = _V;

    angle   = _angle;
    aspect = _aspectRatio;
    znear    = _znear;
    zfar     = _zfar;

    P0Panoramic = P0;
    rPanoramic = r;
    vPanoramic = V;
}

/**
 * Applies the view transformation and projection transformation associated with the camera parameters to the objects in the scene.
 */
void cgvCamera::apply(void)
{  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if ( type == CGV_PARALLEL )
    {  glOrtho ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
    }
    if ( type == CGV_FRUSTUM )
    {  glFrustum ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
    }
    if ( type == CGV_PERSPECTIVE )
    {  gluPerspective ( angle, aspect, znear, zfar );
    }

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity ();
    gluLookAt ( P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z] );
}

/**
 * Zooms in on the camera.
 * @param factor Factor (as a percentage of 100) applied to the zoom. If the value is
 *        positive, the zoom is increased. If it is negative, it is reduced.
 * @pre It is assumed that the parameter has a valid value
 */
void cgvCamera::zoom ( double factor )
{
    double aux = (100 - factor/2)/100;
    // In the case of a parallel camera and a frustum-generated camera, the zoom factor must be applied to the viewport coordinates
    xwmin *= aux;
    xwmax *= aux;
    ywmin *= aux;
    ywmax *= aux;

    // In the case of the GLU perspective camera, simply apply the zoom factor to the angle of view: aux = (100 - factor)/100;
    angle *= aux;
}

void cgvCamera::nextView(void)
{
    // Avanza a la siguiente vista (0->1, 1->2, 2->3, 3->0)
    vis = (poscam)((vis + 1) % 4);

    switch (vis)
    {
        case panoramic:
            // Restaura la vista panorámica guardada
            P0 = P0Panoramic;
            r = rPanoramic;
            V = vPanoramic;
            break;
        case plan: // Vista desde arriba (eje Y)
            P0 = { 0, 10, 0 };
            r = { 0, 0, 0 };
            V = { 0, 0, -1 }; //Apunta a la -Z
            break;
        case profile: // Vista desde un lado (eje X)
            P0 = { 10, 0, 0 };
            r = { 0, 0, 0 };
            V = { 0, 1, 0 };
            break;
        case elevation: // Vista desde el frente (eje Z)
            P0 = { 0, 0, 10 };
            r = { 0, 0, 0 };
            V = { 0, 1, 0 };
            break;
    }
}


/**
* Changes the camera type
* @param t New type (valid values: IGV_PARALLEL, IGV_FRUSTUM, IGV_PERSPECTIVA)
* @pre Assumes the parameter has a valid value
* @post Changes the camera type
*/
void cgvCamera::set_view ( CameraType t )
{ type = t;
}

/**
* Query the camera type
* @return The camera type currently stored in the object
*/
CameraType cgvCamera::get_view ()
{ return type;
}

/**
* Change the camera view type
* @param x New view type (valid values: panorama, plan, elevation,
* profile)
* @pre Assumes the parameter has a valid value
* @post Changes the stored view type (does not change the camera position,
* reference point, or vertical vector)
*/void cgvCamera::set_poscam ( poscam x )
{ vis = x;
}

/**
* Query the camera's view type
* @return The view type stored in the poscam object
*/
poscam cgvCamera::get_poscam ()
{ return vis;
}

void cgvCamera::updateCameraAnimation() {
    // Velocidades
    double orbitSpeed = 0.01;
    double zoomSpeed = 0.1;

    switch (animState) {
        case 0: // ORBITAR
            // Rotamos P0 alrededor del eje Y (usando coordenadas polares simples)
        {
            double radio = sqrt(P0[X]*P0[X] + P0[Z]*P0[Z]);
            double angle = atan2(P0[Z], P0[X]);

            angle += orbitSpeed;

            P0[X] = radio * cos(angle);
            P0[Z] = radio * sin(angle);

            // CONDICIÓN: Si la Z pasa cerca de 0 (frente o perfil), pasamos a Zoom
            // (Usamos un margen pequeño porque float nunca es exacto 0), hace que meta dos zooms, bueno, mas estetico
            if (abs(P0[Z]) < 0.05 && P0[X] > -2.0) {
                initialZoomWidth = xwmax; // Guardamos tamaño actual
                animState = 1; // Pasar a Zoom In
            }
        }
            break;

        case 1: // ZOOM IN
            zoom(2.0);
            // Si nos hemos acercado mucho (xwmax pequeño), cambiamos
            if (xwmax < 1.0) {
                animState = 2; // Pasar a Zoom Out
            }
            break;

        case 2: // ZOOM OUT
            zoom(-2.0);
            // Si volvemos al tamaño original, a orbitar
            if (xwmax >= initialZoomWidth) {
                xwmax = initialZoomWidth;
                animState = 0; // Volver a Orbitar
            }
            break;
    }
}

void cgvCamera::toggleInteractive() {
    interactiveMode = !interactiveMode;
    if (interactiveMode) {
        // inicializamos parámetros si es la primera vez
        // Vector desde la cámara (P0) hacia el punto de mira (r)
        cgvPoint3D dir(r[X] - P0[X], r[Y] - P0[Y], r[Z] - P0[Z]);
        radius = sqrt(dir[X]*dir[X] + dir[Y]*dir[Y] + dir[Z]*dir[Z]); // Distancia entre cámara y el punto que mira → radio de la órbita
        orbitAngleY = atan2(P0[X], P0[Z]); //Te devuelve ne que cuadrante está y asi se puede mover orbital en "all" el alrededor
        pitchAngle = asin(P0[Y] / radius); //ArcoSeno para sacar el angulo
        selfRotY = 0.0;
    }
}

void cgvCamera::orbit(double delta) {
    orbitAngleY += delta;
    updatePosition();
}

void cgvCamera::pitch(double delta) {
    // Modificamos el ángulo de pitch
    pitchAngle += delta;

    // Capamos el pitcheo entre -90º y +90º (en radianes) para que funcione como la camara de un videojuego y no se pueda dar la vuelta 360 y maree al jugador 🤓☝
    const double limit = M_PI / 2.0;
    if (pitchAngle > limit) pitchAngle = limit;
    if (pitchAngle < -limit) pitchAngle = -limit;

    updatePosition();
}

void cgvCamera::rotateY(double delta) {
    selfRotY += delta;
    updatePosition();
}

void cgvCamera::updatePosition() {
    // calculamos posición orbital alrededor del origen
    double x = radius * cos(pitchAngle) * sin(orbitAngleY);
    double y = radius * sin(pitchAngle);
    double z = radius * cos(pitchAngle) * cos(orbitAngleY);

    P0 = cgvPoint3D(x, y, z);
    r = cgvPoint3D(0, 0, 0); // siempre mira al origen
    V = cgvPoint3D(0, 1, 0);

    // rotación local sobre Y
    if (fabs(selfRotY) > 0) {
        double cosA = cos(selfRotY);
        double sinA = sin(selfRotY);

        // rotamos el punto de vista en torno al eje Y local
        cgvPoint3D dir(r[X] - P0[X], r[Y] - P0[Y], r[Z] - P0[Z]);
        double newX = dir[X] * cosA + dir[Z] * sinA;
        double newZ = -dir[X] * sinA + dir[Z] * cosA;
        r = cgvPoint3D(P0[X] + newX, P0[Y] + dir[Y], P0[Z] + newZ);
    }
    apply();
}