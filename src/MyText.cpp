#include "MyText.h"

namespace myText
{
	void drawText(TextureAtlas* fontTextureAtlas, const std::string& text, float xpos, float ypos, float zPos)
	{
		for(unsigned int i = 0; i < text.length() ; i++)
		{
			glPushMatrix();
			RectangleMesh* mesh = fontTextureAtlas->mesh(text.substr(i,1));
			glTranslatef(mesh->width()/2 + xpos, ypos - mesh->height()/2, zPos);
			mesh->draw();
			glPopMatrix();
			xpos=mesh->width()+xpos;

		}
	}
		void drawTextCentered(TextureAtlas* fontTextureAtlas, const std::string& text, float xpos, float ypos, float zPos)
	{
		float xoffset = 0.0f;
		
		for(unsigned int i = 0; i < text.length() ; i++)
		{
			xoffset += fontTextureAtlas->mesh(text.substr(i,1))->width();
		}
		
		xpos-=xoffset/2.0f;

		for(unsigned int i = 0; i < text.length() ; i++)
		{
			glPushMatrix();
			RectangleMesh* mesh = fontTextureAtlas->mesh(text.substr(i,1));
			glTranslatef(mesh->width()/2 + xpos, ypos - mesh->height()/2, zPos);
			mesh->draw();
			glPopMatrix();
			xpos=mesh->width()+xpos;

		}
	}
}
