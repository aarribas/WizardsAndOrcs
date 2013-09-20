//###############################################################################
// INTRODUCCION: TextureAtlas.h
//------------------------------------------------------------------------------
// Un Texture Atlas es un conjunto de texturas que estan integradas en una sola
// imagen. http://en.wikipedia.org/wiki/Texture_atlas
// Este codigo recibe una imagen y un fichero con la descripcion de las texturas
// contenidas en el fichero. Asi podemos crear multitud de rectangulos donde
// cada uno tiene un nombre y la textura / tamaño asociado.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include "Texture.h"
#include "RectangleMesh.h"
#include <map>
#include <string>

class TextureAtlas
{
public:
	TextureAtlas::TextureAtlas(const std::string& textureFile, const std::string& atlasFile);
	virtual ~TextureAtlas();

public:
	//Carga la textura y genera todos los Mesh definidos en el fichero indicado
	void load();
	
	//Libera la textura y los Mesh definidos
	void unload();
	
	//Permite indicar al programador Mesh
	void addRectangleMesh(const std::string& name, float tx, float ty, float tw, float th, float width, float height);
	
	//Obtener el Mesh a partir del nombre (definido al fichero o usando addRectangleMesh)
	RectangleMesh *mesh(const std::string& name);
	
	//return Atlas Texture
	Texture *texture();

	bool findMesh(const std::string& name);

private:
	std::string m_atlasFile;
	Texture *m_texture;
	std::map<std::string, RectangleMesh*> m_mesh;
};