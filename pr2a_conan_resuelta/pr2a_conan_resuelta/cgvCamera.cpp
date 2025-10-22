//#include <GL/glut.h>
#include <math.h>

#include "cgvCamera.h"

// Constructor Methods

/**
* Parameterized constructor
* @param _tipo Camera type (IGV_PARALELA, IGV_FRUSTUM or IGV_PERSPECTIVE)
* @param _P0 Camera position (viewpoint)
* @param _r Point at which the camera is looking (reference point)
* @param _V Vector indicating the vertical
* @pre All parameters are assumed to have valid values
* @post The attributes of the new camera will be equal to the parameters passed to it
*/
cgvCamera::cgvCamera ( cameraType _type, cgvPoint3D _P0, cgvPoint3D _r
, cgvPoint3D _V ): P0 ( _P0 ), r ( _r ), V ( _V )
, type ( _type )
{ }

// Public Methods
/**
* Defines the camera position
* @param _P0 Camera position (viewpoint)
* @param _r Point the camera is looking at (reference point)
* @param _V Vector indicating the vertical
* @pre All parameters are assumed to have valid values
* @post Camera attributes are set to the values ​​passed as parameters
*/
void cgvCamera::set ( cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V )
{ P0 = _P0;
   r = _r;
   V = _V;
}

/**
* Defines a parallel or frustum type camera
* @param _tipo Type of camera (IGV_PARALELA or IGV_FRUSTUM)
* @param _P0 Position of the camera
* @param _r Point at which the camera is looking
* @param _V Vector indicating the vertical
* @param _xwmin Minimum X coordinate of the frustum
* @param _xwmax Maximum X coordinate of the frustum
* @param _ywmin Minimum Y coordinate of the frustum
* @param _ywmax Maximum Y coordinate of the frustum
* @param _znear Distance of the camera to the near Z plane
* @param _zfar Distance of the camera to the far Z plane
* @pre It is assumed that all Parameters have valid values
* @post The camera attributes are set to the values ​​passed as parameters.
*/
void cgvCamera::set ( cameraType _type, cgvPoint3D _P0, cgvPoint3D _r
, cgvPoint3D _V, double _xwmin, double _xwmax, double _ywmin
, double _ywmax, double _znear, double _zfar )
{ type = _type;

   P0 = _P0;
   r = _r;
   V = _V;

   xwmin = _xwmin;
   xwmax = _xwmax;
   ywmin = _ywmin;
   ywmax = _ywmax;
   znear = _znear;
   zfar = _zfar;
}

/**
* Defines a perspective camera type
* @param _tipo Camera type (IGV_PERSPECTIVE)
* @param _P0 Camera position
* @param _r Point at which the camera is looking
* @param _V Vector indicating the vertical
* @param _angulo Opening angle
* @param _raspecto Aspect ratio
* @param _znear Distance of the camera to the near Z plane
* @param _zfar Distance of the camera to the far Z plane
* @pre All parameters are assumed to have valid values
* @post The camera attributes are set to the values ​​passed as
* parameters
*/
void cgvCamera::set (cameraType _type, cgvPoint3D _P0, cgvPoint3D _r
   , cgvPoint3D _V, double _angle, double _aspect
   , double _znear, double _zfar )
{ type = _type;

   P0 = _P0;
   r = _r;
   V = _V;

   angle = _angle;
   aspect = _aspect;
   znear = _znear;
   zfar = _zfar;
}

/**
* Applies the view transformation and the projection transformation associated with the camera parameters to the scene objects.
*/
void cgvCamera::apply ( void )
{ glMatrixMode ( GL_PROJECTION );
   glLoadIdentity ();

   if ( type == CGV_PARARELL )
   { glOrtho ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
   }
   if ( type == CGV_FRUSTUM )
   { glFrustum ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
   }
   if (type == CGV_PERSPECTIVE)
   { gluPerspective ( angle, aspect, znear, zfar );
   }

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt ( P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z] );
}

/**
* Zooms in on the camera
* @param factor The factor (in percent) applied to the zoom. If the value is
* positive, the zoom is increased. If it's negative, the zoom is decreased.
* @pre The parameter is assumed to have a valid value
*/
void cgvCamera::zoom ( double factor )
{ }