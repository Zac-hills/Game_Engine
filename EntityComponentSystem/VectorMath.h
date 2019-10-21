#ifndef __VECTOR_MATH__
#define __VECTOR_MATH__
#include "windows.h"
#include <iostream>

class vec2
{
public:
	vec2() : x(0.0f), y(0.0f){};
	vec2(int a_x, int a_y) : x((float)a_x), y((float)a_y) {};
	vec2(float a_x, float a_y) : x(a_x), y(a_y) {};
	vec2(double a_x, double a_y) : x((float)a_x), y((float)a_y) {};
	vec2(float arr[]) : x(arr[0]), y(arr[1]) {};

	union
	{
		float xy[2];
		struct
		{
			float x, y;
		};
	};

	inline float angle(const vec2 &) const;
	inline float magnitude() const;
	inline vec2 operator+(const vec2 &) const;
	inline void operator+=(const vec2 &);
	inline vec2 operator-(const vec2 &) const;
	inline void operator-=(const vec2 &);
	inline void operator-();
	inline vec2 operator*(const float) const;
	inline void operator*=(const float);
	inline vec2 operator/(const float) const;
	inline void operator/=(const float);
	inline bool operator!=(const vec2 &) const;
	inline bool operator==(const vec2 &) const;
	inline std::string toString() const;
	inline static float dot(const vec2 &, const vec2 &);
	inline static vec2 normalize(const vec2 &);
	inline static vec2 lerp(const vec2 &start, const vec2 &dest, float CurrentTime);

	static vec2 UP;
	static vec2 DOWN;
	static vec2 RIGHT;
	static vec2 LEFT;

private:

};

class vec3
{
public:
	vec3() : x(0.0f), y(0.0f), z(0.0f){};
	vec3(int a_x, int a_y, int a_z) : x((float)a_x), y((float)a_y), z((float)a_z) {};
	vec3(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) {};
	vec3(double a_x, double a_y, double a_z) : x((float)a_x), y((float)a_y), z((float)a_z) {};
	vec3(float arr[]) : x(arr[0]), y(arr[1]), z(arr[2]) {}

	union
	{
		float xy[2];
		float xyz[3];
		struct
		{
			float x, y, z;
		};
	};

	inline float angle(const vec3 &) const;
	inline float magnitude() const;
	inline void operator=(const vec3 &);
	inline bool operator!=(const vec3 &) const;
	inline bool operator==(const vec3 &) const;
	inline vec3 operator+(const vec3 &) const;
	inline void operator+=(const vec3 &);
	inline vec3 operator-(const vec3 &) const;
	inline void operator-=(const vec3 &);
	inline vec3 operator*(const float) const;
	inline void operator*=(const float);
	inline vec3 operator/(const float) const;
	inline void operator/=(const float);
	inline std::string toString() const;
	inline static vec3 normalize(const vec3 &v)
	{
		float mag = v.magnitude();
		return vec3(v.x / mag, v.y / mag, v.z / mag);
	};

	inline static vec3 cross(const vec3 &v1, const vec3 &v2)
	{
		return vec3(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	};
	inline static float dot(const vec3 &, const vec3 &);
	inline static vec3 lerp(const vec3 &start, const vec3 &dest, const float currentTime);

	static vec3 UP;
	static vec3 DOWN;
	static vec3 RIGHT;
	static vec3 LEFT;
	static vec3 FORWARD;
	static vec3 BACK;
};


class vec4
{
public:
	vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};

	vec4(int a_x, int a_y, int a_z, int a_w) : x((float)a_x), y((float)a_y), z((float)a_z), w((float)a_w) {};
	vec4(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {};
	vec4(double a_x, double a_y, double a_z, double a_w) : x((float)a_x), y((float)a_y), z((float)a_z), w((float)a_w) {};

	vec4(void *t1)
	{
		memcpy(&xyzw, &t1, sizeof(xyzw));
	};

	union
	{
		float xy[2];
		float xyz[3];
		float xyzw[4];
		struct
		{
			float x, y, z, w;
		};
	};

	inline vec4 operator*(float) const;
	inline vec4 operator+(vec4) const;
	inline vec4 operator/(float) const;
	inline std::string toString() const;


	static vec4 UP;
	static vec4 DOWN;
	static vec4 RIGHT;
	static vec4 LEFT;
	static vec4 FORWARD;
	static vec4 BACK;
};

#endif