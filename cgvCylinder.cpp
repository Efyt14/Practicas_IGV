#include "cgvCylinder.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/**
* Default constructor
*/
cgvCylinder::cgvCylinder() : cgvTriangleMesh()
{
}

/**
* Parameterized constructor
* @param r Radius of the cylinder's base
* @param a Height of the cylinder
* @param divU Number of side divisions
* @param divV Number of divisions in height
* @pre Parameters are assumed to have valid values
* @post A new triangle mesh is created representing the side face of
* a cylinder with height a and radius r
*/
cgvCylinder::cgvCylinder(float r, float a, int divU, int divV)
{
    // TODO: Section B: Construct the triangle mesh to represent the cylinder
    // TODO: Section C: Add the normal vector

    if (divU < 3) divU = 3;
    if (divV < 1) divV = 1;

    num_vertex = divU * (divV + 1);
    vertex = new float[num_vertex * 3];
    normals = new float[num_vertex * 3];

    num_triangles = divU * divV * 2;
    triangles = new unsigned int[num_triangles * 3];

    // -------- Base ring
    for (int i = 0; i < divU; ++i)
    {
        float angle = (i / (float)divU) * 2.0f * (float)M_PI;
        float cx = std::cos(angle);
        float sx = std::sin(angle);

        vertex[i*3 + 0] = r * cx;
        vertex[i*3 + 1] = 0.0f;
        vertex[i*3 + 2] = r * sx;

        normals[i*3 + 0] = cx;
        normals[i*3 + 1] = 0.0f;
        normals[i*3 + 2] = sx;
    }

    for (int j = 0; j < divV; ++j)
    {
        float y = (j + 1) * (a / (float)divV);

        for (int i = 0; i < divU; ++i)
        {
            int base0 = i * 3;
            int baseJ = ((j + 1) * divU + i) * 3;

            // copy xz and change y for each turn
            vertex[baseJ + 0] = vertex[base0 + 0];
            vertex[baseJ + 1] = y;
            vertex[baseJ + 2] = vertex[base0 + 2];

            // same normal
            normals[baseJ + 0] = normals[base0 + 0];
            normals[baseJ + 1] = 0.0f;
            normals[baseJ + 2] = normals[base0 + 2];
        }
    }
    // Triangulation
    int t = 0;
    for (int j = 0; j < divV; ++j)
    {
        for (int i = 0; i < divU; ++i)
        {
            unsigned int i0 = j * divU + i;
            unsigned int i1 = j * divU + ((i + 1) % divU);
            unsigned int i2 = (j + 1) * divU + ((i + 1) % divU);
            unsigned int i3 = (j + 1) * divU + i;

            triangles[t++] = i0; triangles[t++] = i1; triangles[t++] = i3;
            triangles[t++] = i1; triangles[t++] = i2; triangles[t++] = i3;
        }
    }
}

/**
 * Destroyer
 */
cgvCylinder::~cgvCylinder()
{
}