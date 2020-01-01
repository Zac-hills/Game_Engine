#include "FrameBuffer.h"
#include "GL\glew.h"
#include "Render.h"
#include "Context.h"

RenderBuffer::~RenderBuffer() 
{
	
}

RenderBuffer::RenderBuffer(const unsigned int a_Height, const unsigned int a_Width, const unsigned int a_Depth)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Height = a_Height;
	m_Width = a_Width;
	m_Depth = m_Depth;
}

unsigned int RenderBuffer::GetID() const 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return m_ID;
}

unsigned int RenderBuffer::GetHeight() const 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return m_Height;
}

unsigned int RenderBuffer::GetWidth() const
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return m_Width;
}

unsigned int RenderBuffer::GetDepth() const
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return m_Depth;
}

void RenderBuffer::SetId(const unsigned int a_ID) 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_ID = a_ID;
}

DepthBuffer::DepthBuffer(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 1)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

DepthBuffer::~DepthBuffer() {}

ColorBufferRGB8::ColorBufferRGB8(const unsigned int a_Height, const unsigned int a_Width) :RenderBuffer(a_Height,a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8,a_Width,a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGB8::~ColorBufferRGB8() {}

ColorBufferRGB16::ColorBufferRGB16(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGB16::~ColorBufferRGB16() {}

ColorBufferRGB32::ColorBufferRGB32(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGB32::~ColorBufferRGB32() {}

ColorBufferRGBA8::ColorBufferRGBA8(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGBA8::~ColorBufferRGBA8() {}

ColorBufferRGBA16::ColorBufferRGBA16(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGBA16::~ColorBufferRGBA16() {}

ColorBufferRGBA32::ColorBufferRGBA32(const unsigned int a_Height, const unsigned int a_Width) : RenderBuffer(a_Height, a_Width, 3)
{
	glGenTextures(1, &m_ID);
	TextureContext t(GL_TEXTURE_2D, m_ID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, a_Width, a_Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
ColorBufferRGBA32::~ColorBufferRGBA32() {}

FrameBuffer::FrameBuffer() 
{
	std::lock_guard<std::mutex>Lock(mutex);
	glGenFramebuffers(1, &id);
}

void FrameBuffer::addBuffer(const std::string &a_RenderBufferName, DepthBuffer &a_RenderBuffer)
{
	FrameBufferContext fbc(GL_DEPTH_BUFFER, id);
	glFramebufferTexture2D(GL_DRAW_BUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, a_RenderBuffer.GetID(), 0);
	std::lock_guard<std::mutex> Lock(mutex);
	frameMap[a_RenderBufferName] = &a_RenderBuffer;
	++numOfAttachments;
}

void FrameBuffer::addBuffer(const std::string &a_RenderBufferName, RenderBuffer &a_RenderBuffer) 
{
	FrameBufferContext fbc(GL_FRAMEBUFFER, id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + numColorAttachments, GL_TEXTURE_2D, a_RenderBuffer.GetID(), 0);
	std::lock_guard<std::mutex> Lock(mutex);
	frameMap[a_RenderBufferName] = &a_RenderBuffer;
	++numOfAttachments;
	++numColorAttachments;
}

bool FrameBuffer::hasBuffer(const std::string & name)
{
	return frameMap.find(name) != frameMap.end();
}
