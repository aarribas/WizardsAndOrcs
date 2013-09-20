//###############################################################################
// INTRODUCCION: Texture.h
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

#pragma once

#include "MyGL.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& filename);
	virtual ~Texture();

public:
	//Para crear y cargar la textura a partir del fichero
	void load();
	//Para eliminar la textura
	void unload();
	//Para enlazar la textura al objeto que este activo
	void bind();

private:
	const std::string m_filename;
	bool m_loaded;
	GLuint m_textureId;
};