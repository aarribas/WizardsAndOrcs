
#include "BBoxAtlas.h"
#include "BBox.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

BBoxAtlas::BBoxAtlas(const std::string& atlasFile)
{
	m_atlasFile = atlasFile;
}

BBoxAtlas::~BBoxAtlas()
{
}

void BBoxAtlas::load()
{
	
	std::string line;
	std::string name;
	float x1, y1, x2, y2, x3, y3, x4, y4;

	//Cargamos el fichero con los datos
	std::ifstream myfile(m_atlasFile);

	if (myfile.is_open())
	{
		//Las siguientes contienen los datos de los elementos/sprites

		while ( myfile.good() )
		{
			int num_bbox=0;
			
			std::vector<BBox*>* bboxSet = new std::vector<BBox*> ;

			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
			iss >> num_bbox;
			for(num_bbox; num_bbox > 0; --num_bbox)
			{
				BBox* temp_bbox = new BBox();

				iss >> x1;
				iss >> y1;
				iss >> x2;
				iss >> y2;
				iss >> x3;
				iss >> y3;
				iss >> x4;
				iss >> y4;

				temp_bbox->define(x1,y1,x2,y2,x3,y3,x4,y4);
				bboxSet->push_back(temp_bbox);
			}

			m_bboxes.insert(std::make_pair(name, bboxSet));

		
		}
		myfile.close();
	} else {
		std::cerr << "Resource file not found" << std::endl;
		exit(-1);
	}
}

std::vector<BBox*>* BBoxAtlas::m_bbox(const std::string& name)
{ 
	//Comprobamos si el cuadrado existe
	std::map<std::string, std::vector<BBox*>*>::const_iterator found = m_bboxes.find(name);
	if (found == m_bboxes.end()) {
		std::cerr << "Bbox set not found" << std::endl;
		return NULL;
	}

	//Si existe devolvemos el cuadrado
	return found->second;

}
