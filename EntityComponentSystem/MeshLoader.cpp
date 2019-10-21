#define _CRT_SECURE_NO_WARNINGS
#include "MeshLoader.h"
#include "dirent.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "glew.h"
#include "BufferManager.h"
#include <stdlib.h>
#define BUFFER_OFFSET(i) (((char *)0 )+ i)


struct UV
{
	float u, v;
};

struct Normals
{
	float x, y, z;
};

struct vertex
{
	float x, y, z, w;
};

struct Face
{
	vertex v;
	UV uv;
	Normals norm;
};

union floatToByte
{
	struct
	{
		Face f;
	};
	unsigned char buffer[sizeof(Face)];
};

union fToByte
{
	float f;
	char buffer[sizeof(float)];
};

MeshLoader::MeshLoader(){}

MeshLoader::~MeshLoader(){}

MeshLoader &MeshLoader::getMeshLoader()
{
	static MeshLoader ONLY_ONE;
	return ONLY_ONE;
}

void MeshLoader::readBinaryMesh(std::string &s, Mesh &m)
{
	unsigned int cache = BUFFER_MANAGER.checkIfExists(s.c_str());
	if (cache == 0)
	{
		FILE *fd = fopen(s.c_str(), "rb");
		if (!fd)
		{
			std::cout << "Error opening file. " << s << std::endl;
		}
		fseek(fd, 0, SEEK_END);
		long size = ftell(fd);
		char *buffer = new char[size];
		fseek(fd, 0 , SEEK_SET);
		fread(buffer, size, 1, fd);
		fclose(fd);
		m.mesh_size = (size / (sizeof(float) * 9));
		unsigned int vbo;
		std::vector<Face>fb;
		fb.resize(48);
		memcpy(&fb[0], buffer, 48 * sizeof(Face));
		glGenVertexArrays(1, &m.mesh_ptr);
		glGenBuffers(1, &vbo);

		glBindVertexArray(m.mesh_ptr);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float)* 9, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 9, BUFFER_OFFSET(4));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 9, BUFFER_OFFSET(6));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		
		BUFFER_MANAGER.addBuffer(s.c_str(), m.mesh_ptr, m.mesh_size);
	}
	else
	{
		m.mesh_ptr = cache;
		m.mesh_size = BUFFER_MANAGER.getBufferSize(s.c_str());
	}

}

void MeshLoader::loadMesh(std::string s, Mesh &M)
{
	std::size_t FolderPath = s.find_last_of("/\\");
	DIR *directory;
	std::string temper = s.substr(0, FolderPath + 1);
	directory = opendir(s.substr(0, FolderPath + 1).c_str());
	std::string fileName = s.substr(FolderPath + 1);
	struct dirent *entry;

	std::size_t extensionSize = fileName.find_last_of(".");

	std::string check = fileName.substr(extensionSize + 1);
	if (check == "obj")
	{
		std::size_t filenameNoex = fileName.find_last_of(".obj");

		std::string File_Name = fileName.substr(0, filenameNoex - 3);

		File_Name += ".bin.obj";

		if (!directory)
		{
			std::cout << "Could not find directory." << std::endl;
		}

		while ((entry = readdir(directory)) != NULL)
		{
			if (entry->d_name == File_Name)
			{
				std::string temp = temper;
				temp += entry->d_name;
				readBinaryMesh(temp, M);
				return;
			}
		}
		std::ifstream objfile(s.c_str());

		std::vector<UV> UVBuffer;
		std::vector<vertex> VertexBuffer;
		std::vector<Normals> NormBuffer;
		std::vector<Face> FaceBuffer;

		while (!objfile.eof())
		{
			char buffer[502];
			objfile.getline(buffer, 502);

			std::string cache(buffer);

			if (cache.find("vt ") != std::string::npos)
			{
				float u, v;
				sscanf_s(cache.c_str(), "vt %f %f", &u, &v);
				UV temp;
				temp.u = u;
				temp.v = v;
				UVBuffer.push_back(temp);
			}
			else if (cache.find("vn ") != std::string::npos)
			{
				float x, y, z;
				Normals temp;
				sscanf_s(cache.c_str(), "vn %f %f %f", &x, &y, &z);
				temp.x = x;
				temp.y = y;
				temp.z = z;
				NormBuffer.push_back(temp);
			}
			else if (cache.find("v ") != std::string::npos)
			{
				float x, y, z;
				vertex temp;
				sscanf_s(cache.c_str(), "v %f %f %f", &x, &y, &z);
				temp.x = x;
				temp.y = y;
				temp.z = z;
				VertexBuffer.push_back(temp);
			}
			else if (cache.find("f ") != std::string::npos)
			{
				int v1, vn1, vu1, v2, vn2, vu2, v3, vn3, vu3;
				sscanf_s(cache.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &vu1, &vn1, &v2, &vu2, &vn2, &v3, &vu3, &vn3);
				Face temp;
				Face temp2;
				Face temp3;

				temp.v = VertexBuffer[v1 - 1];
				temp.uv = UVBuffer[vu1 - 1];
				temp.norm = NormBuffer[vn1 - 1];
				temp.v.w = 1.0f;

				temp2.v = VertexBuffer[v2 - 1];
				temp2.uv = UVBuffer[vu2 - 1];
				temp2.norm = NormBuffer[vn2 - 1];
				temp2.v.w = 1.0f;

				temp3.v = VertexBuffer[v3 - 1];
				temp3.uv = UVBuffer[vu3 - 1];
				temp3.norm = NormBuffer[vn3 - 1];
				temp3.v.w = 1.0f;

				FaceBuffer.push_back(temp);
				FaceBuffer.push_back(temp2);
				FaceBuffer.push_back(temp3);
			}
		}
		objfile.close();
		std::size_t t = s.find_last_of(".");
		std::string tempBase = s.substr(0, t +1);
		tempBase += "bin.obj";
		std::ofstream fout(tempBase, std::ios::binary);
		FILE *binFile = fopen(tempBase.c_str(), "wb");
		unsigned int ks = FaceBuffer.size();
		fwrite(&FaceBuffer[0], sizeof(float) * 9,  FaceBuffer.size(), binFile);
		fclose(binFile);

		readBinaryMesh(tempBase, M);
	}
	else if (fileName.substr(extensionSize + 1) == "fbx")
	{

	}
}