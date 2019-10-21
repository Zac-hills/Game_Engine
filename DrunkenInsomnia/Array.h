#pragma once
#include<iostream>


template<typename t>
class Array 
{
public:
	Array(const unsigned int a_Size) 
	{
		m_Size = a_Size;
		m_Buffer = new t[m_Size];
		std::memset(m_Buffer, 0, sizeof(t) * m_Size);
	};
	Array(const Array<t> &a_Other)
	{
		if (m_Buffer = nullptr)
		{
			m_Size = a_Other.m_Size;
			m_Buffer = new t[a_Other.m_Size];
			std::memcpy(m_Buffer, a_Other.m_Buffer, sizeof(t) * m_Size);
		}
		else if (m_Size == a_Other.m_Size) 
		{
			std::memcpy(m_Buffer, a_Other.m_Buffer, sizeof(t) * m_Size);
		}
		else 
		{
			delete[] m_Buffer;
			m_Buffer = new t[a_Other.m_Size];
			m_Size = a_Other.m_Size;
		}
	};

	~Array() 
	{
		delete[] m_Buffer; 
		m_Buffer = nullptr;
		m_Size = 0;
	};
	t& operator[](const unsigned int a_Index) { return m_Buffer[a_Index]; };
	t operator[](const unsigned int a_Index) const { return m_Buffer[a_Index]; };
	unsigned int GetSize() const { return m_Size; };
private:
	t * m_Buffer;
	unsigned int m_Size;
};