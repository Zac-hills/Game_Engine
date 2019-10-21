#include "FrameBuffer.h"
#include "glew.h"
#include <iostream>

FrameBuffer::FrameBuffer(unsigned numColorAttachments)
{
	_numColorAttachments = numColorAttachments;
	_colorAttacherment = new GLuint[_numColorAttachments];

	//buffs setup for glDrawBuffers
	_buffs = new GLenum[_numColorAttachments];
	for (unsigned int i = 0; i < _numColorAttachments; i++)
	{
		_buffs[i] = GL_COLOR_ATTACHMENT0 + i;
	}
}

FrameBuffer::~FrameBuffer()
{
	delete[] _colorAttacherment;
	delete[] _buffs;
}

void FrameBuffer::initBuffer()
{
	glGenFramebuffers(1, &_FBO);
}

void FrameBuffer::initDepthTexture(unsigned width, unsigned height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	/////create depth texture
	glGenTextures(1, &_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, _DepthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	////bind texture to the fbo

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthAttachment, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);


}

void FrameBuffer::initColorTexture(unsigned index, unsigned width, unsigned height, GLint internalFormat, GLint filter, GLint wrap)
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	/////create depth texture
	glGenTextures(1, &_colorAttacherment[index]);
	glBindTexture(GL_TEXTURE_2D, _colorAttacherment[index]);
	glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	////bind texture to the fbo

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, _colorAttacherment[index], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}


bool FrameBuffer::checkFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		unload();
		return false;
		std::cout << "FRAMEBUFFER failed to compile." << std::endl;
		system("PAUSE");
	}
	return true;
}

void FrameBuffer::unload()
{
	if (_buffs != nullptr)
	{
		delete[] _buffs;
		_buffs = nullptr;
	}
	if (_colorAttacherment != nullptr)
	{
		for (unsigned int i = 0; i < _numColorAttachments; i++)
		{
			glDeleteTextures(1, &_colorAttacherment[i]);
		}
		delete[] _colorAttacherment;
		_colorAttacherment = nullptr;
	}
	if (_DepthAttachment != GL_NONE)
	{
		glDeleteTextures(1, &_DepthAttachment);
		_numColorAttachments = 0;
	}

	_numColorAttachments = 0;

}

void FrameBuffer::clear()
{
	GLbitfield temp = 0;

	if (_DepthAttachment != GL_NONE)
	{
		temp |= GL_DEPTH_BUFFER_BIT;
	}

	if (_colorAttacherment != nullptr)
	{
		temp |= GL_COLOR_BUFFER_BIT;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	glClear(temp);

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glDrawBuffers(_numColorAttachments, _buffs);
}

void FrameBuffer::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}


void FrameBuffer::moveToBackBuffer(int windowWidth, int windowHeight)
{

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,  GL_NONE);

	glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}


unsigned int FrameBuffer::getDepthHandle()const 
{
	return _DepthAttachment;
}

unsigned int FrameBuffer::getColorHandle(unsigned index)const 
{
		return _colorAttacherment[index];
}