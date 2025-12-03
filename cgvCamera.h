#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "cgvPoint3D.h"


/**
* Camera views
*/
enum poscam
{ panoramic ///< View from an arbitrary point
    , plan ///< Plan view (camera on the Y axis)
    , profile ///< Profile view (camera on the X axis)
    , elevation ///< Elevation view (camera on the Z axis)
};

/**
 * Tags for different camera types
 */
enum CameraType
{  CGV_PARALLEL   ///< Parallel projection
    , CGV_FRUSTUM   ///< Perspective projection using OpenGL
    , CGV_PERSPECTIVE   ///< Perspective projection using GLU
};

/**
 * Objects of this class represent display cameras in the application
 */
class cgvCamera
{  private:
    // attributes
    poscam vis = panoramic;      ///< Camera position



    // view window: perspective projection parameters


    // viewpoint
    cgvPoint3D P0 = { 6, 4, 8 };   ///< Camera position

    // viewing reference point
    cgvPoint3D r = { 0, 0, 0 };   ///< Point at which the camera is looking

    // up vector
    cgvPoint3D V = { 0, 1, 0 };   ///< Vector indicating the vertical

    cgvPoint3D P0Panoramic; ///< Almacena la P0 de la vista panorámica
    cgvPoint3D rPanoramic;  ///< Almacena la r de la vista panorámica
    cgvPoint3D vPanoramic;  ///< Almacena la V de la vista panorámica

    //Atributos para la animacion de la camara
    int animState = 0; // 0: Orbitar, 1: Zoom In, 2: Zoom Out. Orbitara y cuando llegue a un punto hara zoom
    double orbitAngle = 0.0;
    double initialZoomWidth = 5.0; // Para guardar el zoom original

    // Methods

public:
    bool interactiveMode;   // indica si la cámara está en modo interactivo
    double orbitAngleY;     // ángulo de rotación alrededor del origen (Y global)
    double pitchAngle;      // ángulo de inclinación vertical
    double selfRotY;        // rotación alrededor del eje Y de la cámara
    double radius;          // distancia de la cámara al origen
    CameraType type = CGV_PARALLEL;  ///< Camera type

    // view window: parallel projection and frustum parameters
    GLdouble xwmin = -5    ///< Minimum X coordinate of the frustum/parallel projection
    , xwmax = 5   ///< Maximum X coordinate of the frustum/parallel projection
    , ywmin = -5   ///< Minimum Y coordinate of the frustum/parallel projection
    , ywmax = 5   ///< Maximum Y coordinate of the frustum/parallel projection
    ;

    GLdouble angle = 60   ///< Opening angle (perspective projection)
    , aspect = 1   ///< Aspect ratio (perspective projection)
    ;

    // distances of near and far planes
    GLdouble znear = 3    ///< Distance from camera to Z near plane
    , zfar = 200 ///< Distance from camera to Z far plane
    ;


    // Default constructors and destructor
    /// Default constructor
    cgvCamera () = default;

    /// Destructor
    ~cgvCamera () = default;

    // Other constructors
    cgvCamera ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V );

    // Methods
    // defines the position of the camera
    void set ( cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V );

    // defines a parallel or frustum camera
    void set ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V
            , double _xwmin, double _xwmax, double _ywmin
            , double _ywmax, double _znear, double _zfar );

    // defines a perspective camera
    void set ( CameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V
            , double _angle, double _aspect, double _znear, double _zfar );

    void apply ( void ); // applies the transformation
    // of vision and the transformation of projection
    // associated with the camera parameters to the objects in the scene
    void zoom ( double factor ); // zooms in on the camera

    void nextView ( void );

    void set_view ( CameraType t );

    CameraType get_view ();

    void set_poscam ( poscam x );

    poscam get_poscam ();

    //Animacion
    void updateCameraAnimation();

    void toggleInteractive();       // activa/desactiva modo interactivo
    void orbit(double delta);       // gira alrededor del origen (Y global)
    void updatePosition();          // recalcula P0 y r según los ángulos
    void pitch(double delta);       // inclina hacia arriba/abajo
    void rotateY(double delta);     // rota sobre su eje local Y
};

#endif   // __IGVCAMARA