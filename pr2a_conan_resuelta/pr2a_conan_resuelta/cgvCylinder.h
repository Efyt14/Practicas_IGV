#ifndef __IGV_CILINDRO
#define __IGV_CILINDRO

#include "cgvTriangleMesh.h"
/**
* Objects of this class represent 3D cylinders without the top and bottom caps
*/
class cgvCylinder : public cgvTriangleMesh
{ public:

      // Constructors and destructor
      cgvCylinder ();
      cgvCylinder ( float r, float a, int divU, int divV );
      ~cgvCylinder ();

};
#endif   // __IGV_CILINDRO