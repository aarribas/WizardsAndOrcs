
#pragma once
#include "BBox.h"
#include <map>
#include <string>
#include <vector>

class BBoxAtlas
{
public:
	BBoxAtlas::BBoxAtlas(const std::string& atlasFile);
	virtual ~BBoxAtlas();

public:
	//Carga la textura y genera todos los Mesh definidos en el fichero indicado
	void load();
	
	//Obtener el Mesh a partir del nombre (definido al fichero o usando addRectangleMesh)
	std::vector<BBox*>* m_bbox(const std::string& name);

private:
	std::string m_atlasFile;
	std::map<std::string, std::vector<BBox*>*> m_bboxes;
};