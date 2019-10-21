#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

class FrameBuffer
{
public:
	FrameBuffer(unsigned numColorAttachments);
	~FrameBuffer();

	void initBuffer();

	void initDepthTexture(unsigned width, unsigned height);
	void initColorTexture(unsigned index, unsigned width, unsigned height, int internalFormat, int filter, int wrap);

	//-Clears all OpenGL memory
	void unload();
	//-Clears all attached Textures
	void clear();

	bool checkFBO();

	void bind();
	void unBind();

	void moveToBackBuffer(int windowWidth, int windowHeight);

	unsigned int getDepthHandle() const;

	unsigned int getColorHandle(unsigned index) const;

private:
	unsigned int _FBO = 0;
	unsigned int _DepthAttachment = 0;
	unsigned int *_colorAttacherment = nullptr;
	unsigned int *_buffs = nullptr;
	unsigned int _numColorAttachments = 0;

};

#endif