#pragma once
#include "GL\glew.h"
#define NULL 0

class TextureContext
{
public:
	TextureContext(GLenum a_Target, GLuint a_ID)
	{
		m_Target = a_Target;
		glBindTexture(a_Target, a_ID);
	}
	~TextureContext()
	{
		glBindTexture(m_Target, 0);
	}

private:
	GLenum m_Target;
};

class ProgramContext
{
public:
	ProgramContext(GLuint a_ProgramID) { glUseProgram(a_ProgramID); }
	~ProgramContext() { glUseProgram(NULL); }
};

class BufferContext
{
public:
	BufferContext(GLenum a_Target, GLuint a_BufferID) : m_Target(a_Target) { glBindBuffer(a_Target, a_BufferID); }
	~BufferContext() { glBindBuffer(m_Target, NULL); }
private:
	GLenum m_Target;
};

class FrameBufferContext 
{
public:
	FrameBufferContext(GLenum a_Target, GLuint a_BufferID) : m_Target(a_Target)
	{
		glBindFramebuffer(a_Target, a_BufferID);
	}	
	~FrameBufferContext() { glBindFramebuffer(m_Target, NULL); }

private:
	GLenum m_Target;
};


