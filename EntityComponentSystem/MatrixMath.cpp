#include "MatrixMath.h"
#include <array>
#include <string>
#include <math.h>
#define PI 3.14159265358979323846

mat3::mat3()
{
	data[0] = 1; data[3] = 0; data[6] = 0;
	data[1] = 0; data[4] = 1; data[7] = 0;
	data[2] = 0; data[5] = 0; data[8] = 1;
}

mat3::mat3(const mat4 &m)
{
	data[0] = m.data[0]; data[3] = m.data[4]; data[6] = m.data[8];
	data[1] = m.data[1]; data[4] = m.data[5]; data[7] = m.data[9];
	data[2] = m.data[2]; data[5] = m.data[6]; data[8] = m.data[10];
}

void mat3::operator=(const mat3 &m)
{
	data[0] = m.data[0]; data[3] = m.data[3]; data[6] = m.data[6];
	data[1] = m.data[1]; data[4] = m.data[4]; data[7] = m.data[7];
	data[2] = m.data[2]; data[5] = m.data[5]; data[8] = m.data[8];
}

mat3 mat3::operator*(float scaler) const
{
	mat3 m;
	m.data[0] = data[0] * scaler;  m.data[3] = data[3] * scaler;  m.data[6] = data[6] * scaler;
	m.data[1] = data[1] * scaler;  m.data[4] = data[4] * scaler;  m.data[7] = data[7] * scaler;
	m.data[2] = data[2] * scaler;  m.data[5] = data[5] * scaler;  m.data[8] = data[8] * scaler;
	return m;
}

vec3 mat3::operator*(const vec3 &v) const
{
	return vec3(data[0] * v.x + data[3] * v.y + data[6] * v.z,
		data[1] * v.x + data[4] * v.y + data[7] * v.z,
		data[2] * v.x + data[5] * v.y + data[8] * v.z);
}

void mat3::operator=(const mat4 &m)
{
	data[0] = m.data[0]; data[3] = m.data[4]; data[6] = m.data[8];
	data[1] = m.data[1]; data[4] = m.data[5]; data[7] = m.data[9];
	data[2] = m.data[2]; data[5] = m.data[6]; data[8] = m.data[10];
}

mat3 mat3::transpose() const
{
	mat3 m;

	m.data[0] = data[0];	 m.data[3] = data[1];   m.data[6] = data[2];
	m.data[1] = data[3];	 m.data[4] = data[4];   m.data[7] = data[5];
	m.data[2] = data[6];	 m.data[5] = data[7];   m.data[8] = data[8];

	return m;
}

std::string mat3::toString() const 
{
	std::string L_result = "<";
	for (unsigned int i = 0; i < 9; i++)
	{
		L_result += std::to_string(data[i]);
		L_result += ",";
	}
	L_result += ">";
	return L_result;
}

mat3 mat3::operator-()
{
	mat3 m;

	m.data[0] = -data[0];	 m.data[3] = -data[1];   m.data[6] = -data[2];
	m.data[1] = -data[3];	 m.data[4] = -data[4];   m.data[7] = -data[5];
	m.data[2] = -data[6];	 m.data[5] = -data[7];   m.data[8] = -data[8];
	return m;
}

/********************************************************************************

								Mat4


								*********************************************************************************/

mat4::mat4()
{
	data[0] = 1;   data[4] = 0;     data[8] = 0;    data[12] = 0;
	data[1] = 0;   data[5] = 1;     data[9] = 0;    data[13] = 0;
	data[2] = 0;   data[6] = 0;     data[10] = 1;   data[14] = 0;
	data[3] = 0;   data[7] = 0;     data[11] = 0;	data[15] = 1;
}

mat4 mat4::transpose() const
{
	mat4 m;

	m.data[0] = data[0]; m.data[4] = data[1]; m.data[8] = data[2]; m.data[12] = data[3];
	m.data[1] = data[4]; m.data[5] = data[5]; m.data[9] = data[6]; m.data[13] = data[7];
	m.data[2] = data[8]; m.data[6] = data[9]; m.data[10] = data[10]; m.data[14] = data[11];
	m.data[3] = data[12]; m.data[7] = data[13]; m.data[11] = data[14]; m.data[15] = data[15];

	return m;
}

void mat4::operator=(mat4 &m)
{
	data[0] = m.data[0]; data[4] = m.data[4]; data[8] = m.data[8]; data[12] = m.data[12];
	data[1] = m.data[1]; data[5] = m.data[5]; data[9] = m.data[9]; data[13] = m.data[13];
	data[2] = m.data[2]; data[6] = m.data[6]; data[10] = m.data[10]; data[14] = m.data[14];
	data[3] = m.data[3]; data[7] = m.data[7]; data[11] = m.data[11]; data[15] = m.data[15];
}

mat4 mat4::operator*(mat4 &other) const
{
	mat4 result;

	result.data[0] = data[0] * other.data[0] + data[4] * other.data[1] + data[8] * other.data[2] + data[12] * other.data[3];
	result.data[1] = data[1] * other.data[0] + data[5] * other.data[1] + data[9] * other.data[2] + data[13] * other.data[3];
	result.data[2] = data[2] * other.data[0] + data[6] * other.data[1] + data[10] * other.data[2] + data[14] * other.data[3];
	//result.data[3] = data[3] * other.data[0] + data[7] * other.data[1] + data[11] * other.data[2] + data[15] * other.data[3];

	result.data[4] = data[0] * other.data[4] + data[4] * other.data[5] + data[8] * other.data[6] + data[12] * other.data[7];
	result.data[5] = data[1] * other.data[4] + data[5] * other.data[5] + data[9] * other.data[6] + data[13] * other.data[7];
	result.data[6] = data[2] * other.data[4] + data[6] * other.data[5] + data[10] * other.data[6] + data[14] * other.data[7];
	//result.data[7] = data[3] * other.data[4] + data[7] * other.data[5] + data[11] * other.data[6] + data[15] * other.data[7];

	result.data[8] = data[0] * other.data[8] + data[4] * other.data[9] + data[8] * other.data[10] + data[12] * other.data[11];
	result.data[9] = data[1] * other.data[8] + data[5] * other.data[9] + data[9] * other.data[10] + data[13] * other.data[11];
	result.data[10] = data[2] * other.data[8] + data[6] * other.data[9] + data[10] * other.data[10] + data[14] * other.data[11];
	//result.data[11] = data[3] * other.data[8] + data[7] * other.data[9] + data[11] * other.data[10] + data[15] * other.data[11];

	result.data[12] = data[0] * other.data[12] + data[4] * other.data[13] + data[8] * other.data[14] + data[12] * other.data[15];
	result.data[13] = data[1] * other.data[12] + data[5] * other.data[13] + data[9] * other.data[14] + data[13] * other.data[15];
	result.data[14] = data[2] * other.data[12] + data[6] * other.data[13] + data[10] * other.data[14] + data[14] * other.data[15];
	//result.data[15] = data[3] * other.data[12] + data[7] * other.data[13] + data[11] * other.data[14] + data[15] * other.data[15];

	return result;
}

mat4 mat4::rotateY(float degrees) const
{
	float radians;
	radians = degrees * ((float)PI / 180.0f);

	mat4 yMat;

	yMat.data[0] = cos(radians);  yMat.data[4] = 0.0f;  yMat.data[8] = sin(radians);  yMat.data[12] = 0.0f;
	yMat.data[1] = 0.0f;          yMat.data[5] = 1.0f;  yMat.data[9] = 0.0f;          yMat.data[13] = 0.0f;
	yMat.data[2] = -sin(radians); yMat.data[6] = 0.0f;  yMat.data[10] = cos(radians); yMat.data[14] = 0.0f;
	yMat.data[3] = 0.0f;          yMat.data[7] = 0.0f;  yMat.data[11] = 0.0f;         yMat.data[15] = 1.0f;

	return *this * yMat;
}

mat4 mat4::rotateX(float degrees) const
{
	float radians;
	radians = degrees * ((float)PI / 180.0f);

	mat4 xMat;

	xMat.data[0] = 1.0f; xMat.data[4] = 0.0f;         xMat.data[8] = 0.0f;                  xMat.data[12] = 0.0f;
	xMat.data[1] = 0.0f; xMat.data[5] = cos(radians); xMat.data[9] = -sin(radians);         xMat.data[13] = 0.0f;
	xMat.data[2] = 0.0f; xMat.data[6] = sin(radians); xMat.data[10] = cos(radians);         xMat.data[14] = 0.0f;
	xMat.data[3] = 0.0f; xMat.data[7] = 0.0f;         xMat.data[11] = 0.0f;                 xMat.data[15] = 1.0f;

	return *this*xMat;
}

mat4 mat4::rotateZ(float degrees) const
{
	float radians;

	radians = degrees *((float)PI / 180.0f);

	mat4 zMat;
	zMat.data[0] = cos(radians); zMat.data[4] = -sin(radians); zMat.data[8] = 0.0f;  zMat.data[12] = 0.0f;
	zMat.data[1] = sin(radians); zMat.data[5] = cos(radians);  zMat.data[9] = 0.0f;  zMat.data[13] = 0.0f;
	zMat.data[2] = 0.0f;         zMat.data[6] = 0.0f;          zMat.data[10] = 1.0f; zMat.data[14] = 0.0f;
	zMat.data[3] = 0.0f;         zMat.data[7] = 0.0f;          zMat.data[11] = 0.0f; zMat.data[15] = 1.0f;

	return *this*zMat;
}

mat4 mat4::inverse()
{
	mat4 m;
	mat3 m3 = *this;
	m3 = m3.transpose();

	m.data[0] = m3.data[0]; m.data[4] = m3.data[3]; m.data[8] = m3.data[6];
	m.data[1] = m3.data[1]; m.data[5] = m3.data[4]; m.data[9] = m3.data[7];
	m.data[2] = m3.data[2]; m.data[6] = m3.data[5]; m.data[10] = m3.data[8];
	vec3 hold = ((-m3) * this->position);
	m.data[12] = hold.x;
	m.data[13] = hold.y;
	m.data[14] = hold.z;
	//m.position = ((-m3) * this->position);
	return m;
}

void mat4::perspectiveMatrix(float _near, float _far, float FOV, float height, float width)
{
	float range = _near - _far;
	float ar = height / width;
	float tanHalfFOV = tanf((FOV * ((float)PI / 180)) / 2.0f);

	data[0] = 1.0f / (tanHalfFOV * ar);		 data[4] = 0.0f;						data[8] = 0.0f;										data[12] = 0.0f;
	data[1] = 0.0f;							 data[5] = (1.0f / tanHalfFOV) / ar;    data[9] = 0.0f;										data[13] = 0.0f;
	data[2] = 0.0f;							 data[6] = 0.0f;						data[10] = -((_near + _far) / (_far - _near));		data[14] = -((2 * (_far * _near)) / (_far - _near));
	data[3] = 0.0f;							 data[7] = 0.0f;						data[11] = -1.0f;									data[15] = 0.0f;
}

std::string mat4::toString() const
{
	std::string matString;
	for (int i = 0; i < 16; i++)
	{
		matString += std::to_string(data[i]);
		matString += ", ";
	}
	return matString;
}