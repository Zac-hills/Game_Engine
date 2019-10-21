#include "Quaternions.h"
#include <cmath>
#include "VectorMath.h"


Quaternion Quaternion::operator-() const
{
	return Quaternion(w, -x, -y, -z);
}

void Quaternion::normalize() 
{
	float cache = sqrtf(w * w + x * x + y * y + z * z);
	w /= cache;
	x /= cache;
	y /= cache;
	z /= cache;
}

mat3 Quaternion::toMat3() const
{
	mat3 result;
	result.data[0] = 1.0f - 2.0f * (y * y) - 2.0f * (z *z); result.data[3] = 2.0f * x * y - 2.0f * z * w;		 result.data[6] = 2.0f * x * z + 2.0f * y * w;
	result.data[1] = 2.0f * x * y + 2.0f * z * w;           result.data[4] = 1.0f - 2.0f * (x*x) - 2.0f * (z*z); result.data[7] = 2.0f * y * z - 2.0f * x * w;
	result.data[2] = 2.0f * x * z - 2.0f * y * w;           result.data[5] = 2.0f * y * z + 2.0f * x* w;	     result.data[8] = 1.0f - 2.0f * (x*x) - 2.0f * (y*y);
	return result;
}

Quaternion Quaternion::operator*(const Quaternion &a_Other)const 
{
	Quaternion l_Result;
	return l_Result;
}

Quaternion Quaternion::LookAt(const vec3 &v1, const vec3 &v2) const
{
	vec3 forward = vec3::normalize(v1 - v2);
	vec3 rotAxis = vec3::cross(vec3::FORWARD, forward);
	float dot = vec3::dot(vec3::FORWARD, forward);

	Quaternion l_result;
	l_result.x = rotAxis.x;
	l_result.y = rotAxis.y;
	l_result.z = rotAxis.z;
	l_result.w = dot + 1;
	l_result.normalize();
	return l_result;
}