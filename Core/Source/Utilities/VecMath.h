/*
 Copyright (C) 2010-2012 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TrenchBroom_VecMath_h
#define TrenchBroom_VecMath_h

#include <string>
#include <cmath>
#include <ostream>
#include <limits>

namespace Math {
    static const float AlmostZero = 0.001f;
    static const float PointStatusEpsilon = 0.01f;
    static const float Pi = 3.141592f;

    inline bool isnan(float f) {
#ifdef _MSC_VER
        return _isnan(f) != 0;
#else
        return std::isnan(f);
#endif
    }

    inline float nan() {
        return std::numeric_limits<float>::quiet_NaN();
    }

    inline float fradians(float d) {
        return Pi * d / 180.0f;
    }

    inline float fdegrees(float r) {
        return 180.0f * r / Pi;
    }

    inline float fround(float f) {
        return f > 0.0f ? floor(f + 0.5f) : ceil(f - 0.5f);
    }

    inline float fcorrect(float f) {
        return fround(1000.0f * f) / 1000.0f;
    }

    inline bool fzero(float f) {
        return fabsf(f) <= AlmostZero;
    }

    inline bool fpos(float f) {
        return f > AlmostZero;
    }

    inline bool fneg(float f) {
        return f < -AlmostZero;
    }

    inline bool feq(float f1, float f2) {
        return fabsf(f1 - f2) < AlmostZero;
    }

    inline bool fgt(float f1, float f2) {
        return f1 > f2 + AlmostZero;
    }

    inline bool flt(float f1, float f2) {
        return f1 < f2 - AlmostZero;
    }

    inline bool fgte(float f1, float f2) {
        return !flt(f1, f2);
    }

    inline bool flte(float f1, float f2) {
        return !fgt(f1, f2);
    }

    inline float fmin(float f1, float f2) {
        return f1 < f2 ? f1 : f2;
    }

    inline float fmax(float f1, float f2) {
        return f1 < f2 ? f2 : f1;
    }

    inline int imin(int i1, int i2) {
        return i1 < i2 ? i1 : i2;
    }

    inline int imax(int i1, int i2) {
        return i1 < i2 ? i2 : i1;
    }
}

typedef enum {
    TB_AX_X,
    TB_AX_Y,
    TB_AX_Z
} EAxis;

typedef enum {
    TB_PS_ABOVE, // point is above the plane
    TB_PS_BELOW, // point is below the plane
    TB_PS_INSIDE // point is contained inside the plane
} EPointStatus;

class Vec2f {
public:
    float x,y;
    Vec2f& operator= (const Vec2f& right);
    const Vec2f operator+ (const Vec2f& right) const;
    const Vec2f operator- (const Vec2f& right) const;
    const Vec2f operator* (const float right) const;
    const Vec2f operator/ (const float right) const;
    const float operator| (const Vec2f& right) const; // dot product
    Vec2f& operator+= (const Vec2f& right);
    Vec2f& operator-= (const Vec2f& right);
    Vec2f& operator*= (const float right);
    Vec2f& operator/= (const float right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Vec2f();
    Vec2f(float x, float y);

    float length() const;
    float lengthSquared() const;
    const Vec2f normalize() const;
    const Vec2f correct() const;
    bool equals(const Vec2f& other) const;
    bool equals(const Vec2f& other, float delta) const;
    void write(std::ostream& str) const;
    std::string asString() const;
};

class Vec3f {
public:
    static const Vec3f PosX;
    static const Vec3f PosY;
    static const Vec3f PosZ;
    static const Vec3f NegX;
    static const Vec3f NegY;
    static const Vec3f NegZ;
    static const Vec3f Null;
    static const Vec3f NaN;
    
    float x,y,z;
    bool operator== (const Vec3f& right) const;
    Vec3f& operator= (const Vec3f& right);
    const Vec3f operator+ (const Vec3f& right) const;
    const Vec3f operator- (const Vec3f& right) const;
    const Vec3f operator* (const float right) const;
    const Vec3f operator/ (const float right) const;
    const float operator| (const Vec3f& right) const; // dot product
    const Vec3f operator% (const Vec3f& right) const; // cross product
    Vec3f& operator+= (const Vec3f& right);
    Vec3f& operator-= (const Vec3f& right);
    Vec3f& operator*= (const float right);
    Vec3f& operator/= (const float right);
    Vec3f& operator%= (const Vec3f& right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Vec3f();
    Vec3f(const std::string& str);
    Vec3f(float x, float y, float z);

    float length() const;
    float lengthSquared() const;
    const Vec3f normalize() const;
    const Vec3f correct() const;
    bool equals(const Vec3f& other) const;
    bool equals(const Vec3f& other, float delta) const;
    bool null() const;
    EAxis firstComponent() const;
    EAxis secondComponent() const;
    EAxis thirdComponent() const;
    const Vec3f& firstAxis(bool pos = true) const;
    const Vec3f& secondAxis(bool pos = true) const;
    const Vec3f& thirdAxis(bool pos = true) const;
    void write(std::ostream& str) const;
    std::string asString() const;

    const Vec3f snap() const;
    const Vec3f snap(float epsilon) const;
    const Vec3f rotate90(EAxis axis, bool clockwise) const;
    const Vec3f rotate90(EAxis axis, const Vec3f& center, bool clockwise) const;
    const Vec3f flip(EAxis axis) const;
    const Vec3f flip(EAxis axis, const Vec3f& center) const;
};

class Vec4f {
public:
    float x,y,z,w;
    Vec4f& operator= (const Vec4f& right);
    const Vec4f operator+ (const Vec4f& right) const;
    const Vec4f operator- (const Vec4f& right) const;
    const Vec4f operator* (const float right) const;
    const Vec4f operator/ (const float right) const;
    const float operator| (const Vec4f right) const; // dot product
    Vec4f& operator+= (const Vec4f& right);
    Vec4f& operator-= (const Vec4f& right);
    Vec4f& operator*= (const float right);
    Vec4f& operator/= (const float right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Vec4f();
    Vec4f(const std::string& str);
    Vec4f(float x, float y, float z, float w);

    float length() const;
    float lengthSquared() const;
    const Vec4f normalize() const;
    const Vec4f correct() const;
    bool equals(const Vec4f& other) const;
    bool equals(const Vec4f& other, float delta) const;
    void write(std::ostream& str) const;
    std::string asString() const;
};

class Mat2f {
public:
    float v[4];
    Mat2f& operator= (const Mat2f& right);
    const Mat2f operator+ (const Mat2f& right) const;
    const Mat2f operator- (const Mat2f& right) const;
    const Mat2f operator* (const float right) const;
    const Vec2f operator* (const Vec2f& right) const;
    const Mat2f operator* (const Mat2f& right) const;
    const Mat2f operator/ (const float right) const;
    Mat2f& operator+= (const Mat2f& right);
    Mat2f& operator-= (const Mat2f& right);
    Mat2f& operator*= (const float right);
    Mat2f& operator*= (const Mat2f& right);
    Mat2f& operator/= (const float right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Mat2f();
    Mat2f(float v11, float v12, float v21, float v22);
    void setIdentity();
    void setValue(unsigned int row, unsigned int col, float value);
    void setColumn(unsigned int col, const Vec2f& values);
    const Mat2f invert(bool& invertible) const;
    const Mat2f adjugate() const;
    const Mat2f negate() const;
    const Mat2f transpose() const;
    float determinant() const;
};

static const Mat2f IdentityM2f(1, 0, 0, 1);

class Mat3f {
public:
    float v[9];
    Mat3f& operator= (const Mat3f& right);
    const Mat3f operator+ (const Mat3f& right) const;
    const Mat3f operator- (const Mat3f& right) const;
    const Mat3f operator* (const float right) const;
    const Vec3f operator* (const Vec3f& right) const;
    const Mat3f operator* (const Mat3f& right) const;
    const Mat3f operator/ (const float right) const;
    Mat3f& operator+= (const Mat3f& right);
    Mat3f& operator-= (const Mat3f& right);
    Mat3f& operator*= (const float right);
    Mat3f& operator*= (const Mat3f& right);
    Mat3f& operator/= (const float right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Mat3f();
    Mat3f(float v11, float v12, float v13, float v21, float v22, float v23, float v31, float v32, float v33);
    void setIdentity();
    void setValue(unsigned int row, unsigned int col, float value);
    void setColumn(unsigned int col, const Vec3f& values);
    const Mat3f invert(bool& invertible) const;
    const Mat3f adjugate() const;
    const Mat3f negate() const;
    const Mat3f transpose() const;
    float determinant() const;
    const Mat2f subMatrix(unsigned int row, unsigned int col) const;
};

static const Mat3f IdentityM3f(1, 0, 0, 0, 1, 0, 0, 0, 1);

class Quat;
class Mat4f {
public:
    static const Mat4f Identity;
    static const Mat4f Rot90XCW;
    static const Mat4f Rot90YCW;
    static const Mat4f Rot90ZCW;
    static const Mat4f Rot90XCCW;
    static const Mat4f Rot90YCCW;
    static const Mat4f Rot90ZCCW;
    static const Mat4f MirX;
    static const Mat4f MirY;
    static const Mat4f MirZ;
    
    float v[16];
    Mat4f& operator= (const Mat4f& right);
    const Mat4f operator+ (const Mat4f& right) const;
    const Mat4f operator- (const Mat4f& right) const;
    const Mat4f operator* (const float right) const;
    const Vec3f operator* (const Vec3f& right) const;
    const Vec4f operator* (const Vec4f& right) const;
    const Mat4f operator* (const Mat4f& right) const;
    const Mat4f operator/ (const float right) const;
    Mat4f& operator+= (const Mat4f& right);
    Mat4f& operator-= (const Mat4f& right);
    Mat4f& operator*= (const float right);
    Mat4f& operator*= (const Mat4f& right);
    Mat4f& operator/= (const float right);
    float& operator[] (const unsigned int index);
    const float& operator[] (const unsigned int index) const;
    Mat4f();
    Mat4f(float v11, float v12, float v13, float v14, float v21, float v22, float v23, float v24, float v31, float v32, float v33, float v34, float v41, float v42, float v43, float v44);
    void setIdentity();
    void setValue(unsigned int row, unsigned int col, float value);
    void setColumn(unsigned int col, const Vec3f& values);
    void setColumn(unsigned int col, const Vec4f& values);
    void setSubMatrix(int index, const Mat2f& values);
    const Mat2f subMatrix(int index) const;
    const Mat4f invert(bool& invertible) const;
    const Mat4f adjugate() const;
    const Mat4f negate() const;
    const Mat4f transpose() const;
    float determinant() const;
    const Mat3f subMatrix(unsigned int row, unsigned int col) const;

    const Mat4f rotate(float angle, const Vec3f& axis) const;
    const Mat4f rotate(const Quat& rotation) const;
    const Mat4f translate(const Vec3f& delta) const;
    const Mat4f scale(const Vec3f& factors) const;
};

class Quat {
public:
    float s;
    Vec3f v;
    const Quat operator* (const Quat& right) const;
    const Vec3f operator* (const Vec3f& right) const;
    Quat& operator*= (const Quat& right);
    Quat();
    Quat(float angle, const Vec3f& axis);
    void setRotation(float angle, const Vec3f axis);
    const Quat conjugate() const ;
};

class Ray {
public:
    Vec3f origin;
    Vec3f direction;
    Ray();
    Ray(const Vec3f& origin, const Vec3f& direction);
    const Vec3f pointAtDistance(float distance) const;
    EPointStatus pointStatus(const Vec3f& point) const;
};

class Line {
public:
    Vec3f point;
    Vec3f direction;
    Line();
    Line(const Vec3f& point, const Vec3f& direction);
    const Vec3f pointAtDistance(float distance) const;
};

class BBox {
private:
    void repair();
public:
    Vec3f min;
    Vec3f max;
    bool operator== (const BBox& right) const;
    const BBox operator+ (const BBox& right) const;
    const BBox operator+ (const Vec3f& right) const;
    BBox& operator+= (const BBox& right);
    BBox& operator+= (const Vec3f& right);
    BBox();
    BBox(const Vec3f& min, const Vec3f& max);
    BBox(float minx, float miny, float minz, float maxx, float maxy, float maxz);
    BBox(const Vec3f& center, float size);
    const BBox maxBounds() const;
    const BBox centered() const;
    const Vec3f center() const;
    const BBox repaired() const;
    const Vec3f size() const;
    const Vec3f vertex(bool x, bool y, bool z) const;
    bool contains(const Vec3f& point) const;
    bool contains(const BBox& bounds) const;
    bool intersects(const BBox& bounds) const;
    float intersectWithRay(const Ray& ray, Vec3f* sideNormal) const;
    float intersectWithRay(const Ray& ray) const;

    const BBox translate(const Vec3f& delta) const;
    const BBox rotate90(EAxis axis, bool clockwise) const;
    const BBox rotate90(EAxis axis, const Vec3f& center, bool clockwise) const;
    const BBox rotate(Quat rotation) const;
    const BBox rotate(Quat rotation, const Vec3f& center) const;
    const BBox boundsAfterRotation(Quat rotation) const;
    const BBox flip(EAxis axis) const;
    const BBox flip(EAxis axis, const Vec3f& center) const;
    const BBox expand(float f);
};

class Plane {
public:
    Vec3f normal;
    float distance;
    Plane();
    Plane(const Vec3f& normal, float distance);
    Plane(const Vec3f& normal, const Vec3f& anchor);
    bool setPoints(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3);
    const Vec3f anchor() const;
    float intersectWithRay(const Ray& ray) const;
    float intersectWithLine(const class Line& line) const;
    EPointStatus pointStatus(const Vec3f& point) const;
    float x(float y, float z) const;
    float y(float x, float z) const;
    float z(float x, float y) const;
    bool equals(const Plane& other) const;
    bool equals(const Plane& other, float epsilon) const;

    const Plane translate(const Vec3f& delta) const;
    const Plane rotate90(EAxis axis, bool clockwise) const;
    const Plane rotate90(EAxis axis, const Vec3f& center, bool clockwise) const;
    const Plane rotate(Quat rotation) const;
    const Plane rotate(Quat rotation, const Vec3f& center) const;
    const Plane flip(EAxis axis) const;
    const Plane flip(EAxis axis, const Vec3f& center) const;
};

class CoordinatePlane {
public:
    typedef enum {
        TB_CP_XY, TB_CP_XZ, TB_CP_YZ
    } CPlane;
private:
    const CPlane m_plane;
    CoordinatePlane(CPlane plane) : m_plane(plane) {}
public:
    static const CoordinatePlane& plane(CPlane plane);
    static const CoordinatePlane& plane(const Vec3f& normal);
    const Vec3f project(const Vec3f& point);
};

#endif
