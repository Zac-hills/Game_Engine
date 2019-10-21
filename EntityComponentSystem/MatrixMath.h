#ifndef __MATRIX_MATH__
#define __MATRIX_MATH__
#include <iostream>
#include "VectorMath.h"

class mat4;

class mat3
{
public:
	mat3();
	mat3(const mat4 &);

	union
	{
		float data[9];
		struct
		{
			vec3 right, up, forward;
		};
	};


	void operator=(const mat3 &);
	mat3 operator*(const float) const;
	void operator*=(const mat3 &);
	mat3 operator*(const mat3 &);
	vec3 operator*(const vec3 &) const;
	void operator=(const mat4 &);
	mat3 operator-();
	mat3 transpose() const;
	std::string toString() const;
};


class mat4
{
public:
	mat4();

	union
	{
		float data[16];
		struct
		{
			vec3 right;
			float scalerRight;
			vec3 up;
			float scalerUp;
			vec3 forward;
			float scalerForward;
			vec3 position;
			float scalerPosition;
		};
	};
	void operator=(mat4 &);
	mat4 operator*(mat4 &) const;
	mat4 rotateY(float degrees) const;
	mat4 rotateX(float degrees) const;
	mat4 rotateZ(float degrees) const;
	mat4 inverse();
	mat4 transpose() const;
	void perspectiveMatrix(float _near, float _far, float FOV, float height, float width);
	std::string toString() const;
private:

};
#endif // !__MATRIX_MATH__