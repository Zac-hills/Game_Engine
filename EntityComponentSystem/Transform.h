#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include "Component.h"
#include "MatrixMath.h"
#include "Entity.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();
	inline unsigned int childCount() const;
	inline vec3 &up();
	inline void Setforward(vec3 &);
	inline const vec3 &forward() const;
	inline vec3 &right();
	inline vec3 &position();
	//mat4 &getMatrix();
	mat4 m_position;

private:
	unsigned int m_numChild = 0;
};

#endif