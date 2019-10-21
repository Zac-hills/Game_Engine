#pragma once
#include "FreeImage.h"
#include <string>

class Image
{
public:
	Image() {}
	Image(Image &a_Other)
	{ 
		m_FilePath = a_Other.m_FilePath;
		m_Width = a_Other.m_Width;
		m_Height = a_Other.m_Height;
		m_ID = a_Other.m_ID;
		if (m_Bits == nullptr)
		{
			m_Bits = new BYTE[a_Other.m_Width * a_Other.m_Height * 4];
			std::memcpy(m_Bits, a_Other.m_Bits, a_Other.m_Width * a_Other.m_Height * 4);
		}
		else
		{
			delete[] m_Bits;
			m_Bits = new BYTE[a_Other.m_Width * a_Other.m_Height * 4];
			std::memcpy(m_Bits, a_Other.m_Bits, a_Other.m_Width * a_Other.m_Height * 4);
		}
	}
	~Image() { if (m_Bits != nullptr) delete[] m_Bits; m_Bits = nullptr; }

	unsigned int m_Height = 0;
	unsigned int m_Width = 0;
	unsigned int m_Depth = 0;
	std::string m_FilePath = "";
	FREE_IMAGE_FORMAT m_FileType;
	std::string ToString() const 
	{
		std::string l_Result = "<[PNG] Height: ";
		l_Result += std::to_string(m_Height) + ", Width: " + std::to_string(m_Width) + ", File Path: " + m_FilePath + ">";
		return l_Result;
	}
	BYTE *m_Bits = nullptr;
	GLuint m_ID = 1;
};

