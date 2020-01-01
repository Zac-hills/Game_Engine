#include "Camera.h"

mat4 Camera::GetProjectionMatrix() const 
{
	return m_Projection;
}

mat4 Camera::GetViewMatrix() const 
{
	return m_Transform.getLocal();
}

void Camera::SetProjection(const float a_right, const float a_left, const float a_top, const float a_bottom, const float a_near, const float a_far)
{
	m_Projection.OrthoGraphicMatrix(a_right,a_left,a_top,a_bottom,a_near,a_far);
}