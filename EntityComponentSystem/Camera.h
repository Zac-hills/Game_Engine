#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Component.h"
#include "MatrixMath.h"
#include <math.h>
#define PI 3.14159265358979323846

class Camera : public Component
{
public:
	Camera();
	~Camera();
	mat4 perspectiveMatrix;
};
#endif