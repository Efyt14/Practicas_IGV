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
* Labels for the different camera types
*/
enum cameraType
{ CGV_PARARELL ///< Parallel projection
, CGV_FRUSTUM ///< Perspective projection using OpenGL
, CGV_PERSPECTIVE ///< Perspective projection using GLU
};

/**
* Objects of this class represent display cameras in the application
*/
class cgvCamera
{ private:
    // attributes
    cameraType type = CGV_PARARELL; ///< Camera type

    // view window: parallel projection and frustum parameters
    GLdouble xwmin = -3 ///< Minimum X coordinate of the frustum/parallel projection
             , xwmax = 3 ///< Maximum X coordinate of the frustum/parallel projection
             , ywmin = -3 ///< Minimum Y coordinate of the frustum/parallel projection
             , ywmax = 3 ///< Maximum Y coordinate of the frustum/parallel projection
             ;

    // Viewport: perspective projection parameters
    GLdouble angle = 60 ///< Opening angle (perspective projection)
    , aspect = 1 ///< Aspect ratio (perspective projection)
    ;

    // Near and far plane distances
    GLdouble znear = 1 ///< Distance from camera to Z plane (near)
    , zfar = 200 ///< Distance from camera to Z plane (far)
    ;

    // Viewpoint
    cgvPoint3D P0 = { 3, 2, 4 }; ///< Camera position

    // Viewpoint reference point
    cgvPoint3D r = { 0, 0, 0 }; ///< Point the camera is looking at

    // Up vector
    cgvPoint3D V = { 0, 1, 0 }; ///< Vector indicating the vertical

    // Methods
public:
    // Default Constructors and Destructor
    /// Default Constructor
    cgvCamera () = default;

    /// Destructor
    ~cgvCamera () = default;

    // Other Constructors
    cgvCamera ( cameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V );

    // Methods
    // Defines the camera position
    void set ( cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V );

    // defines a parallel or frustum type camera
    void set ( cameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V
               , double _xwmin, double _xwmax, double _ywmin
               , double _ywmax, double _znear, double _zfar );

    // defines a perspective camera
    void set ( cameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V
               , double _angle, double _aspect, double _znear, double _zfar );
    void apply(void); // applies the vision transformation and projection transformation associated with the camera parameters to the scene objects
    void zoom(double factor); // zooms in on the camera
};

#endif   // __IGVCAMARA

