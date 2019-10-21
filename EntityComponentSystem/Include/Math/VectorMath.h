#ifndef __VECTOR_MATH__
#define __VECTOR_MATH__
#define NULL 0
#include "windows.h"
#include <iostream>

class vec2
{
public:
	vec2() : x(NULL), y(NULL){};

	template<class TYPE>
	vec2(TYPE t1, TYPE t2) : x(t1), y(t2){};

	vec2(void *t1)
	{
		memcpy(&xy, &t1, sizeof(xy));
	};

	union
	{
		float xy[2];
		struct
		{
			float x, y;
		};
	};

	inline float angle(vec2) const;
	inline float magnitude() const;
	inline vec2 operator+(vec2) const;
	inline vec2 operator*(float) const;
	inline vec2 operator/(float) const;
	inline bool operator!=(vec2 &) const;
	inline bool operator==(vec2 &) const;
	inline std::string toString() const;
	inline static float dot(vec2, vec2);
	inline static vec2 normalize(vec2);
	inline static vec2 lerp(vec2 start, vec2 dest, float dt);

	static vec2 UP;
	static vec2 DOWN;
	static vec2 RIGHT;
	static vec2 LEFT;

private:

};

class vec3
{
public:
	vec3() : x(NULL), y(NULL), z(NULL){};

	template<class TYPE>
	vec3(TYPE t1, TYPE t2, TYPE t3) : x(t1), y(t2), z(t3){};
	/*pass floats in complex data types, structs, arrays*/
	vec3(void *t1)	
	{
		memcpy(&xyz, t1, sizeof(xyz));
		x = (float)x;
		y = (float)y;
		z = (float)z;
	};

	union
	{
		float xy[2];
		float xyz[3];
		struct
		{
			float x, y, z;
		};
	};

	inline float angle(vec3 &) const;
	inline float magnitude() const;
	inline void operator=(vec3 &);
	inline bool operator!=(vec3 &) const;
	inline bool operator==(vec3 &) const;
	inline vec3 operator+(vec3 &) const;
	inline vec3 operator*(float) const;
	inline vec3 operator/(float) const;
	inline std::string toString() const;
	inline static vec3 normalize(vec3 &v)
	{
		float mag = v.magnitude();
		return new vec3(v.x / mag, v.y / mag, v.z / mag);
	};

	inline static vec3 cross(vec3 &v1, vec3 &v2)
	{
		return new vec3(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	};
	inline static float dot(vec3 &, vec3 &);
	inline static vec3 lerp(vec3 &start, vec3 &dest, float dt);

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
	vec4() : x(NULL), y(NULL), z(NULL), w(NULL){};

	template<class TYPE>
	vec4(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : x(t1), y(t2), z(t3), w(t4){};


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