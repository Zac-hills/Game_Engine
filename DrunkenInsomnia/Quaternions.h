#pragma once
#include "MatrixMath.h"

class Quaternion 
{
public:
	Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f){}
	//unit quaternion, values must add to one!
	Quaternion(float a_w, float a_x, float a_y, float a_z) : w(a_w), x(a_x), y(a_y), z(a_z) {}
	
	Quaternion operator-() const;
	void normalize();
	Quaternion LookAt(const vec3 &v1, const vec3 &v2) const;
	Quaternion operator*(const Quaternion &a_Other) const;
	mat3 toMat3() const;

private:
	float w, x, y, z;
};