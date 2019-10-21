#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include <iostream>
#include <unordered_map>

class FreeTypeWrap 
{
	FreeTypeWrap()
	{
		FT_Init_FreeType(&m_Library);
		FT_Error error = FT_Init_FreeType(&m_Library);
		if (error) 
		{
			std::cout << "Error Loading FreeType Library." << std::endl;
		}
		m_CharacterList.push_back(' ');
		m_CharacterList.push_back('`');
		m_CharacterList.push_back('1');
		m_CharacterList.push_back('2');
		m_CharacterList.push_back('3');
		m_CharacterList.push_back('4');
		m_CharacterList.push_back('5');
		m_CharacterList.push_back('6');
		m_CharacterList.push_back('7');
		m_CharacterList.push_back('8');
		m_CharacterList.push_back('9');
		m_CharacterList.push_back('0');
		m_CharacterList.push_back('-');
		m_CharacterList.push_back('=');
		m_CharacterList.push_back('~');
		m_CharacterList.push_back('!');
		m_CharacterList.push_back('@');
		m_CharacterList.push_back('#');
		m_CharacterList.push_back('$');
		m_CharacterList.push_back('%');
		m_CharacterList.push_back('^');
		m_CharacterList.push_back('&');
		m_CharacterList.push_back('*');
		m_CharacterList.push_back('(');
		m_CharacterList.push_back(')');
		m_CharacterList.push_back('_');
		m_CharacterList.push_back('+');
		m_CharacterList.push_back('q');
		m_CharacterList.push_back('w');
		m_CharacterList.push_back('e');
		m_CharacterList.push_back('r');
		m_CharacterList.push_back('t');
		m_CharacterList.push_back('y');
		m_CharacterList.push_back('u');
		m_CharacterList.push_back('i');
		m_CharacterList.push_back('o');
		m_CharacterList.push_back('p');
		m_CharacterList.push_back('[');
		m_CharacterList.push_back(']');
		m_CharacterList.push_back('\\');
		m_CharacterList.push_back('a');
		m_CharacterList.push_back('s');
		m_CharacterList.push_back('d');
		m_CharacterList.push_back('f');
		m_CharacterList.push_back('g');
		m_CharacterList.push_back('h');
		m_CharacterList.push_back('j');
		m_CharacterList.push_back('k');
		m_CharacterList.push_back('l');
		m_CharacterList.push_back(';');
		m_CharacterList.push_back('\'');
		m_CharacterList.push_back('z');
		m_CharacterList.push_back('x');
		m_CharacterList.push_back('c');
		m_CharacterList.push_back('v');
		m_CharacterList.push_back('b');
		m_CharacterList.push_back('n');
		m_CharacterList.push_back('m');
		m_CharacterList.push_back(',');
		m_CharacterList.push_back('.');
		m_CharacterList.push_back('/');
		m_CharacterList.push_back('Q');
		m_CharacterList.push_back('W');
		m_CharacterList.push_back('E');
		m_CharacterList.push_back('R');
		m_CharacterList.push_back('T');
		m_CharacterList.push_back('Y');
		m_CharacterList.push_back('U');
		m_CharacterList.push_back('I');
		m_CharacterList.push_back('O');
		m_CharacterList.push_back('P');
		m_CharacterList.push_back('{');
		m_CharacterList.push_back('}');
		m_CharacterList.push_back('|');
		m_CharacterList.push_back('A');
		m_CharacterList.push_back('S');
		m_CharacterList.push_back('D');
		m_CharacterList.push_back('F');
		m_CharacterList.push_back('G');
		m_CharacterList.push_back('H');
		m_CharacterList.push_back('J');
		m_CharacterList.push_back('K');
		m_CharacterList.push_back('L');
		m_CharacterList.push_back(':');
		m_CharacterList.push_back('"');
		m_CharacterList.push_back('Z');
		m_CharacterList.push_back('X');
		m_CharacterList.push_back('C');
		m_CharacterList.push_back('V');
		m_CharacterList.push_back('B');
		m_CharacterList.push_back('N');
		m_CharacterList.push_back('M');
		m_CharacterList.push_back('<');
		m_CharacterList.push_back('>');
		m_CharacterList.push_back('?');
	}

public:
	FT_Library m_Library;
	static FreeTypeWrap m_Singleton;
	std::vector<char> m_CharacterList;
};

FreeTypeWrap FreeTypeWrap::m_Singleton;

class Font 
{
public:
	void SetSize(unsigned int a_ResHeight, unsigned int a_ResWidth, unsigned int a_Height, unsigned int a_Width)
	{
		FT_Set_Char_Size(m_Face, a_Width * 64, a_Height * 64, a_ResWidth, a_ResHeight);
	}
	//leaving width blank makes width = height allowing uniform size
	void SetPixelSize(unsigned int a_Height, unsigned int a_Width = 0)
	{
		FT_Set_Pixel_Sizes(m_Face, a_Width, a_Height);
	}

private:
	void LoadFontMap()
	{
		for (unsigned int i = 0; i < FreeTypeWrap::m_Singleton.m_CharacterList.size(); i++)
		{
			CharMapIndex[FreeTypeWrap::m_Singleton.m_CharacterList[i]] = FT_Get_Char_Index(m_Face, FreeTypeWrap::m_Singleton.m_CharacterList[i]);
		}
	}
	template<typename T>
	friend T Load(const std::string &a_FilePath);
	FT_Face m_Face;
	std::unordered_map<char, unsigned int> CharMapIndex;
};