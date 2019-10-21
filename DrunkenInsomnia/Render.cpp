#include "Render.h"
#include "Renderables.h"
#include "Interface.h"
#include "Context.h"

Renderer::Renderer()
{
	//generating empty VAO for full screen effects
	//generating default texture
	GLuint imageID;
	glGenVertexArrays(1, &EmptyVAO);
	float arr[4] = {0.0f, 1.0f, 0.0f, 1.0f};
	glGenTextures(1, &imageID);
	TextureContext t(GL_TEXTURE_2D, imageID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_BGRA, GL_FLOAT, arr);
}

void Renderer::CreateTextureID(Image &a_Image)
{
	if (TextureMap.find(a_Image.m_FilePath) != TextureMap.end())
	{
		a_Image.m_ID = TextureMap[a_Image.m_FilePath];
		return;
	}
	glGenTextures(1, &a_Image.m_ID);
	TextureContext t(GL_TEXTURE_2D, a_Image.m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, a_Image.m_Width, a_Image.m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, a_Image.m_Bits);
	TextureMap[a_Image.m_FilePath] = a_Image.m_ID;
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenerateTextureMipmap(a_Image.m_ID);
}


void Renderer::Render(Image &a_Image, Program &a_Prog)
{
	ProgramContext p(a_Prog.GetProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(1);
	TextureContext tc(GL_TEXTURE_2D, a_Image.m_ID);
	GLint location = glGetUniformLocation(a_Prog.GetProgram(), "tex");
	glProgramUniform1i(a_Prog.GetProgram(), location, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Render(const Quad &a_Quad, Program &a_Prog) 
{
	ProgramContext p(a_Prog.GetProgram());
	glBindVertexArray(1);
	GLint location = glGetUniformLocation(a_Prog.GetProgram(), "Vertices");
	GLint UVLocation = glGetUniformLocation(a_Prog.GetProgram(), "UV");
	GLint ViewProjection = glGetUniformLocation(a_Prog.GetProgram(), "ViewProjection");
	GLint Model = glGetUniformLocation(a_Prog.GetProgram(), "ViewProjection");

}

void Renderer::SetCamera(Camera &a_Camera)
{
	std::lock_guard<std::mutex>Lock(m_Mutex);
	m_CurrentCamera = &a_Camera;
}

void Renderer::GetPick(const MouseEvent & a_MouseEvent)
{
	//set to picker buffer id
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	float buffer[3];
	glReadPixels(a_MouseEvent.GetX(), a_MouseEvent.GetY(), 1,1, GL_RGB, GL_FLOAT, &buffer);

}

void Renderer::Render(InterfaceItem &a_InterfaceItem, Program &a_Prog)
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