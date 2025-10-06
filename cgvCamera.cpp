#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include <math.h>
#include <stdio.h>

#include "cgvCamera.h"
// Constructor methods
cgvCamera::cgvCamera() {}

cgvCamera::~cgvCamera() {}

cgvCamera::cgvCamera(cameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V) {
    P0 = _P0;
    r = _r;
    V = _V;

    type = _type;
}

void cgvCamera::set(cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V) {
    P0 = _P0;
    r = _r;
    V = _V;
}

void cgvCamera::set(cameraType _type, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V,
                    double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
    type = _type;

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

void cgvCamera::set(cameraType _tipo, cgvPoint3D _P0, cgvPoint3D _r, cgvPoint3D _V,
                    double _angulo, double _raspecto, double _znear, double _zfar) {
    type = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    angle = _angulo;
    aspect = _raspecto;
    znear = _znear;
    zfar = _zfar;
}

void cgvCamera::apply(void) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (type == CGV_PARALLEL) {
        glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (type == CGV_FRUSTRUM) {
        glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (type == CGV_PERSPECTIVE) {
        gluPerspective(angle, aspect, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}

void cgvCamera::zoom(double factor) {
    if (type == CGV_PARALLEL || type == CGV_FRUSTRUM)
    {
        xwmin *= factor;
        xwmax *= factor;
        ywmin *= factor;
        ywmax *= factor;
    }
    else
    {
        if (angle * factor < 180.0)
        {
            angle *= factor;
        }
    }
}

void cgvCamera::toggleInteractive() {
    interactiveMode = !interactiveMode;
    if (interactiveMode) {
        // inicializamos parámetros si es la primera vez
        cgvPoint3D dir(r[X] - P0[X], r[Y] - P0[Y], r[Z] - P0[Z]);
        radius = sqrt(dir[X]*dir[X] + dir[Y]*dir[Y] + dir[Z]*dir[Z]);
        orbitAngleY = atan2(P0[X], P0[Z]);
        pitchAngle = asin(P0[Y] / radius);
        selfRotY = 0.0;
    }
}

void cgvCamera::orbit(double delta) {
    orbitAngleY += delta;
    updatePosition();
}

void cgvCamera::pitch(double delta) {
    pitchAngle += delta;

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
    if (fabs(selfRotY) > 1e-6) {
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

void cgvCamera::moveNear(double delta) {
    znear += delta;
    if (znear < 0.1) { // Evitar valores negativos
        znear = 0.1;
    }
    if (znear >= zfar - 0.1) { // Evitar que se pase del zfar
        znear = zfar - 0.1;
    }
    apply();
}

void cgvCamera::moveFar(double delta) {
    zfar += delta;
    if (zfar <= znear + 0.1) { // Evitar que se meta más dentro del znear
        zfar = znear + 0.1;
    }
    apply();
}