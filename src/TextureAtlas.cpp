//###############################################################################
// INTRODUCCION: TextureAtlas.cpp
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

#include "TextureAtlas.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

TextureAtlas::TextureAtlas(const std::string& textureFile, const std::string& atlasFile)
{
	//Preparamos la textura 
	m_texture = new Texture(textureFile);
	m_atlasFile = atlasFile;
}

TextureAtlas::~TextureAtlas()
{
	delete m_texture;
}

void TextureAtlas::load()
{
	int texWidth, texHeight;
	std::string line;
	std::string name;
	std::string devNull;
	float tx, ty, tw, th;

	//Cargamos la textura a partir de la imagen
	m_texture->load();

	//Cargamos el fichero con los datos y creamos los rectangulos
	std::ifstream myfile(m_atlasFile);
	if (myfile.is_open())
	{
		//La primera linea contiene el tamaño de la textura
		getline(myfile, line);
		std::istringstream iss(line);
		iss >> texWidth;
		iss >> texHeight;

		//Las siguientes contienen los datos de los elementos/sprites
		while ( myfile.good() )
		{
			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
			iss >> devNull;
			iss >> tx;
			iss >> ty;
			iss >> tw;
			iss >> th;

			//Una vez leidos los parametros, cramos el cuadrado texturado
			addRectangleMesh(name, tx/texWidth, ty/texHeight, tw/texWidth, th/texHeight, tw, th);
		}
		myfile.close();
	} else {
		std::cerr << "E: TextureAtlas resource file " << m_atlasFile << " not found" << std::endl;
		exit(-1);
	}
}

void TextureAtlas::unload()
{
	//Borramos la textura
	m_texture->unload();
}

void TextureAtlas::addRectangleMesh(const std::string& name, float tx, float ty, float tw, float th, float width, float height)
{
	//Creamos un nuevo rectangulo y le pasamos la textura y sus 4 coordenadas
	RectangleMesh *newMesh = new RectangleMesh(m_texture, tx, ty, tw, th, width, height);

	//Comprobamos si ya existe un cuadrado texturado con el mismo nombre
	std::map<std::string, RectangleMesh*>::const_iterator found = m_mesh.find(name);
	if (found != m_mesh.end()) {
		std::cerr << "W: mesh " << name << " exists!" << std::endl;
		return;
	}

	//Sino añadimos el cuadrado a una tabla de hashing identificada por su nombre
	m_mesh.insert(std::make_pair(name, newMesh));
}

RectangleMesh *TextureAtlas::mesh(const std::string& name)
{
	//Comprobamos si el cuadrado existe
	std::map<std::string, RectangleMesh*>::const_iterator found = m_mesh.find(name);
	if (found == m_mesh.end()) {
		std::cerr << "W: mesh " << name << "doesn't exist!" << std::endl;
		return NULL;
	}

	//Si existe devolvemos el cuadrado
	return found->second;
}

Texture *TextureAtlas::texture()
{
	return m_texture;
}


bool TextureAtlas::findMesh(const std::string& name)
{
	std::map<std::string, RectangleMesh*>::const_iterator found = m_mesh.find(name);

	if(found != m_mesh.end())
	{
		return true;
	}
	else
	{
		return false;
	}

}