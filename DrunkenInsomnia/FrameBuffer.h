#pragma once
#include <vector>
#include <unordered_map>
#include <mutex>
#include "UniqueIdentifier.h"

class RenderBuffer 
{
public:
	RenderBuffer(const unsigned int a_Height, const unsigned int a_Width, const unsigned int a_Depth);
	virtual ~RenderBuffer();
	unsigned int GetID() const;
	unsigned int GetHeight() const;
	unsigned int GetWidth() const;
	unsigned int GetDepth() const;
	void SetId(const unsigned int a_ID);

protected:
	unsigned int m_Height = 0;
	unsigned int m_Width = 0;
	unsigned int m_ID = 0;
	unsigned int m_Depth = 0;
	mutable std::mutex m_Mutex;
};

class DepthBuffer : public RenderBuffer
{
public:
	DepthBuffer(const unsigned int a_Height, const unsigned int a_Width);
	~DepthBuffer();
};

class ColorBufferRGB8 : public RenderBuffer 
{
public:
	ColorBufferRGB8(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGB8();
};
class ColorBufferRGB16 : public RenderBuffer
{
public:
	ColorBufferRGB16(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGB16();
};
class ColorBufferRGB32 : public RenderBuffer
{
public:
	ColorBufferRGB32(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGB32();
};

class ColorBufferRGBA8 : public RenderBuffer
{
public:
	ColorBufferRGBA8(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGBA8();
};
class ColorBufferRGBA16 : public RenderBuffer
{
public:
	ColorBufferRGBA16(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGBA16();
};
class ColorBufferRGBA32 : public RenderBuffer
{
public:
	ColorBufferRGBA32(const unsigned int a_Height, const unsigned int a_Width);
	~ColorBufferRGBA32();
};

class FrameBuffer
{
public:
	FrameBuffer();
	void AddBuffer(const std::string &a_RenderBufferName, DepthBuffer &a_RenderBuffer);
	void AddBuffer(const std::string &a_RenderBufferName, RenderBuffer &a_RenderBuffer);
private:
	std::unordered_map<std::string, RenderBuffer *> FrameMap;
	unsigned int m_ID=0;
	unsigned int m_NumOfAttachments = 0;
	std::mutex m_Mutex;
	UniqueIdentifier m_UniqueCounter;
};