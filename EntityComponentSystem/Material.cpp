#include "Material.h"


Material::Material()
{
	memset(&Flag, 0, 10);
	Normal_ptr = -1;
	Displacement_ptr = -1;
	Texture_ptr = -1;
	Specular_ptr = -1;
	Incandescent_ptr = -1;
}

Material::~Material(){}