#include "VectorMath.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////VECTOR2/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

vec2 vec2::UP(0, 1);
vec2 vec2::DOWN(0, -1);
vec2 vec2::RIGHT(1, 0);
vec2 vec2::LEFT(-1, 0);

vec2 vec2::operator+(const vec2 &v) const
{
	return vec2(v.x + this->x, v.y + this->y);
}

void vec2::operator+=(const vec2 &v)
{
	x += v.x;
	y += v.y;
}

vec2 vec2::operator-(const vec2 &v) const
{
	return vec2(x - v.x, y - v.y);
}

void vec2::operator-=(const vec2 &v)
{
	x -= v.x;
	y -= v.y;
}

void vec2::operator-() 
{
	x = -x;
	y = -y;
}

float vec2::magnitude() const
{
	return sqrtf(x * x + y * y);
}

vec2 vec2::operator*(const float f) const
{
	return vec2(x * f, y * f);
}

void vec2::operator*=(const float f) 
{
	x *= f;
	y *= f;
}

vec2 vec2::operator/(const float f) const 
{
	return vec2(x / f, y / f);
}

void vec2::operator/=(const float f)
{
	x /= f;
	y /= f;
}

bool vec2::operator!=(const vec2 &v) const
{
	return (bool)memcmp(this->xy, v.xy, sizeof(float) * 2);
}

bool vec2::operator==(const vec2 &v) const
{
	return !(bool)memcmp(this->xy, v.xy, sizeof(float) * 2);
}

std::string vec2::toString() const
{
	return std::string(std::to_string(x) + " " + std::to_string(y));
}

float vec2::dot(const vec2 &v1, const vec2 &v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

vec2 vec2::normalize(const vec2 &v) 
{
	float mag = v.magnitude();
	return vec2(v.x / mag, v.y / mag);
}

vec2 vec2::lerp(const vec2 &start,const vec2 &dest, float CurrentTime)
{
	return vec2((start.x * (1.0f - CurrentTime)) + (dest.x * CurrentTime), (start.y * (1.0f - CurrentTime)) + (dest.y * CurrentTime));
}

float vec2::angle(const vec2 &v) const
{
	return ((x * v.x) + (y * v.y)) / (magnitude() * v.magnitude());
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////VECTOR3/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

vec3 vec3::UP(0, 1, 0);
vec3 vec3::DOWN(0, -1, 0);
vec3 vec3::RIGHT(1, 0, 0);
vec3 vec3::LEFT(-1, 0, 0);
vec3 vec3::FORWARD(0, 0, 1);
vec3 vec3::BACK(0, 0, -1);

void vec3::operator=(const vec3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

vec3 vec3::operator+(const vec3 &v) const
{
	return vec3(v.x + this->x, v.y + this->y, v.z + this->z);
}

void vec3::operator+=(const vec3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

vec3 vec3::operator-(const vec3 &v) const 
{
	return vec3(x-v.x, y-v.y,z-v.z);
}

void vec3::operator-=(const vec3 &v) 
{
	x += v.x;
	y += v.y;
	z += v.z;
}

vec3 vec3::operator*(const float f) const
{
	return vec3(x * f, y * f, z * f);
}

void vec3::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
}

vec3 vec3::operator/(const float f) const
{
	return vec3(x / f , y / f, z / f);
}

void vec3::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
}

bool vec3::operator!=(const vec3 &v) const
{
	return (bool)memcmp(this->xyz, v.xyz, sizeof(float) * 3);
}

bool vec3::operator==(const vec3 &v) const
{
	return !(bool)memcmp(this->xyz, v.xyz, sizeof(float) * 3);
}

float vec3::dot(const vec3 &v1, const vec3 &v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float vec3::magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

std::string vec3::toString() const
{
	return std::string(std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
}

vec3 vec3::lerp(const vec3 &start, const vec3 &dest, const float dt)
{
	return vec3((start.x * (1.0f - dt)) + (dest.x * dt), (start.y * (1.0f - dt)) + (dest.y * dt), (start.z * (1.0f - dt)) + (dest.z * dt));
}

float EaseTime(const float time)
{
	float sqt = time * time;
	return sqt / (2.0f * (sqt - time) + 1.0f);
}

vec3 vec3::slerp(const vec3 &start, const vec3 &dest, const float time) 
{
	float cache = EaseTime(time);
	return vec3((start.x * (1.0f - cache)) + (dest.x * cache), (start.y * (1.0f - cache)) + (dest.y * cache), (start.z * (1.0f - cache)) + (dest.z * cache));
}



float vec3::angle(const vec3 &v) const
{
	return ((x * v.x) + (y * v.y) + (z * v.z)) / (magnitude() * v.magnitude());
}
vec3 vec3::cross(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
};
vec3 vec3::normalize(const vec3 &v)
{
	float mag = v.magnitude();
	return vec3(v.x / mag, v.y / mag, v.z / mag);
};
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////VECTOR4/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


vec4 vec4::operator+(vec4 v) const
{
	return vec4(v.x + this->x,
					v.y + this->y, 
					v.z + this->z, 
					1.0f);
}

vec4 vec4::operator*(float f) const
{
	return vec4(x * f, y * f, z * f, 1.0f);
}

vec4 vec4::operator/(float f) const
{
	return vec4(x / f, y / f, z / f, 1.0f);
}

std::string vec4::toString() const
{
	return std::string(std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " " + std::to_string(w));
}