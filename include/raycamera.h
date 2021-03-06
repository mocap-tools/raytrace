#ifndef RAYCAMERA_H
#define RAYCAMERA_H
#include "vector3d.h"

class RayCamera
{
public:
    RayCamera();
    RayCamera(const Vector3D& location, const Vector3D& lookat, const Vector3D& up);

    const Vector3D& location() const;
    const Vector3D& up() const;
    const Vector3D& lookat() const;

    void setLocation(const Vector3D&);
    void setUp(const Vector3D&);
    void setLookat(const Vector3D&);
private:
    Vector3D m_location;
    Vector3D m_lookat;
    Vector3D m_up;

};

#endif // RAYCAMERA_H
