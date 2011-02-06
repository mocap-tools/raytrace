#include "raycanvas.h"
#include "vector3d.h"
#include <iostream>

using namespace std;
#define AX 1.0
#define AY .8

RayCanvas::RayCanvas(const Vector3D& origin, const Vector3D& lookat, const Vector3D& up, int pixWidth, int pixHeight)
    : m_origin(origin), m_pixWidth(pixWidth), m_pixHeight(pixHeight)
{
    double d = 2;
    Vector3D direction = lookat - m_origin;
    direction.normalize();

    m_side = up.normalized().crossProduct(direction);
    m_up = direction.crossProduct(m_side);
    Vector3D canvasCenter = origin + direction*d;

    //m_focalPlane = RayPlane();

    m_upperLeft = canvasCenter + m_side*(AX/2) + m_up*(AY/2);    
    m_pixelColors.resize(pixHeight*pixWidth);
}


Vector3D RayCanvas::vectorThrough(int pixelRow, int pixelCol)
{

    Vector3D canvasPoint = m_upperLeft - 
                           m_side*((double)pixelRow/m_pixWidth)*AX - 
                           m_up*((double)pixelCol/m_pixHeight)*AY;

    Vector3D v = canvasPoint - m_origin;
    v.normalize();
    return v;
}

void RayCanvas::setColor(unsigned int x, unsigned int y, const RayColor& color)
{
    unsigned int index = y*m_pixWidth + x;
    if (index > m_pixelColors.size()-1)
    {
        return;
    }
    m_pixelColors[index] = color;
}

RayColor RayCanvas::color(unsigned int x, unsigned int y)
{
    unsigned int index = y*m_pixWidth + x;
    if (index > m_pixelColors.size()-1)
    {
        return RayColor();
    }
    return m_pixelColors[index];
}
