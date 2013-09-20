//###############################################################################
// INTRODUCCION: Texture.cpp
//------------------------------------------------------------------------------
// Este codigo nos proporciona la estructura para crear una textura a partir
// de un fichero de imagen.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "Texture.h"
#include "SOIL.h"

#include <iostream>

Texture::Texture(const std::string& filename)
	: m_filename(filename)
	, m_loaded(false)
	, m_textureId(0)
{
}

Texture::~Texture()
{
	if (m_loaded)
		unload();
}

void Texture::load()
{
	if (m_loaded)
		unload();
	//Cargamos la textura del fichero utilizando la libreria SOIL
	//para mas info: www.lonesock.net/soil.html
	m_textureId = SOIL_load_OGL_texture(m_filename.c_str(),
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID,
										SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (m_textureId == 0) {
		std::cout << "E: Texture error '" << m_filename << "': " << SOIL_last_result() << std::endl;
		exit(-1);
	}
	m_loaded = true;
}

void Texture::unload()
{
	if (! m_loaded)
		return;
	//Borramos la textura de la memoria
	glDeleteTextures(1, &m_textureId);
	m_textureId = 0;
	m_loaded = false;
}

void Texture::bind()
{
	if (! m_loaded)
		return;
	//Enlazamos la textura al objeto que este activo en OpenGL
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}
