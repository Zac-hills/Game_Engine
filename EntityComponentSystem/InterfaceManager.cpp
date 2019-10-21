#include "InterfaceManager.h"
#include "BufferManager.h"
#include "RenderManager.h"
#include "glew.h"


InterfaceManager::InterfaceManager(){}

InterfaceManager::~InterfaceManager(){}

void InterfaceManager::OnClickSetFocus(LMouseDown *e)
{
	RENDER_MANAGER.DeferredBuffer->bind();
	glFlush();
	glFinish();
	glReadBuffer(GL_COLOR_ATTACHMENT3);
	unsigned int check = glGetError();
	unsigned char data[4];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(e->p->x, e->p->y, 1, 1,GL_RGB, GL_UNSIGNED_BYTE, data);
	unsigned int Selected = data[0] + data[1] * 256 + data[2] * 256 * 256;

}	