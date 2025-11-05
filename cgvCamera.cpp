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