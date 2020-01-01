#include "Render.h"
#include "Renderables.h"
#include "Interface.h"
#include "Context.h"

Renderer::Renderer()
{
	//generating empty VAO for full screen effects
	//generating default texture
	GLuint imageID;
	glGenVertexArrays(1, &emptyVAO);
	float arr[4] = {0.0f, 1.0f, 0.0f, 1.0f};
	glGenTextures(1, &imageID);
	TextureContext t(GL_TEXTURE_2D, imageID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_BGRA, GL_FLOAT, arr);
}

void Renderer::createTextureID(Image &a_Image)
{
	if (textureMap.find(a_Image.m_FilePath) != textureMap.end())
	{
		a_Image.m_ID = textureMap[a_Image.m_FilePath];
		return;
	}
	glGenTextures(1, &a_Image.m_ID);
	TextureContext t(GL_TEXTURE_2D, a_Image.m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, a_Image.m_Width, a_Image.m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, a_Image.m_Bits);
	textureMap[a_Image.m_FilePath] = a_Image.m_ID;
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenerateTextureMipmap(a_Image.m_ID);
}


void Renderer::render(Image &a_Image, Program &a_Prog)
{
	ProgramContext p(a_Prog.GetProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(1);
	TextureContext tc(GL_TEXTURE_2D, a_Image.m_ID);
	GLint location = glGetUniformLocation(a_Prog.GetProgram(), "tex");
	glProgramUniform1i(a_Prog.GetProgram(), location, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::render(const Quad &a_Quad, Program &a_Prog) 
{
	ProgramContext p(a_Prog.GetProgram());
	glBindVertexArray(1);
	GLint location = glGetUniformLocation(a_Prog.GetProgram(), "Vertices");
	GLint UVLocation = glGetUniformLocation(a_Prog.GetProgram(), "UV");
	GLint ViewProjection = glGetUniformLocation(a_Prog.GetProgram(), "ViewProjection");
	GLint Model = glGetUniformLocation(a_Prog.GetProgram(), "ViewProjection");

}

void Renderer::setCamera(Camera &a_Camera)
{
	std::lock_guard<std::mutex>Lock(mutex);
	currentCamera = &a_Camera;
}

void Renderer::getPick(const MouseEvent & a_MouseEvent)
{
	//set to picker buffer id       
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	unsigned char buffer[4];
	glReadPixels(a_MouseEvent.GetX(), a_MouseEvent.GetY(), 1,1, GL_RGBA, GL_UNSIGNED_BYTE, &buffer);

}

void Renderer::addBuffer(const std::string &name,  RenderBuffer& buffer)
{
	frameBuffer.addBuffer(name, buffer);
}

void Renderer::renderBuffer(const std::string &name)
{
	if (frameBuffer.hasBuffer(name))
	{

	}
}

void Renderer::render(InterfaceItem &a_InterfaceItem, Program &a_Prog)
{
	ProgramContext p(a_Prog.GetProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(1);
	TextureContext tc(GL_TEXTURE_2D, a_InterfaceItem.GetTextureID());
	GLint Vertlocation = glGetUniformLocation(a_Prog.GetProgram(), "Vertices");
	GLint UVlocation = glGetUniformLocation(a_Prog.GetProgram(), "UVCoordinates");
	GLint TexLocation = glGetUniformLocation(a_Prog.GetProgram(), "tex");

	glProgramUniform1i(a_Prog.GetProgram(), TexLocation, 0);
	glUniform2fv(Vertlocation, 6, &(a_InterfaceItem.Vertices[0].x));
	glUniform2fv(UVlocation, 6, &(a_InterfaceItem.UVCoordinates[0].x));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}