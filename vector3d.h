#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:
    Vector3D();
    Vector3D(float x, float y, float z);

    // Getters and setters
    float x() const;
    float y() const;
    float z() const;


    Vector3D& setX(float x);
    Vector3D& setY(float y);
    Vector3D& setZ(float z);


    const Vector3D operator*(float scale) const;
    /*const Vector3D operator*(int scale) const;*/
    const Vector3D operator+(const Vector3D& v2) const;
    const Vector3D operator-(const Vector3D& v2) const;

    // Operations
    Vector3D& normalize();
    float length() const;
    float lengthSquared() const;

    float dotProduct(const Vector3D& other) const;
    Vector3D crossProduct(const Vector3D& other) const;

    Vector3D normalized() const;


private:
    float m_x;
    float m_y;
    float m_z;
};

// global operator functions
/*Vector3D operator*(const Vector3D& v, float scale);

Vector3D operator*(const Vector3D& v, int scale);

Vector3D operator+(const Vector3D& v1, const Vector3D& v2);

Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
*/
#endif // VECTOR3D_H
