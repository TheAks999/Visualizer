#ifndef RESTEXTURE_H
#define RESTEXTURE_H

#include "resource.h"
#include <QImage>
#include <QPainter>
#include <QString>

//prototypes
bool loadTIFF(const QString & path, unsigned int & texId, QImage & texture);
bool loadPNG(const QString & path, unsigned int & texId, QImage & texture);
bool loadTGA(const QString & path, unsigned int & texId, QImage & texture);
bool loadBMP(const QString & path, unsigned int & texId, QImage & texture);



class ResTexture : public Resource
{
	private:
		QImage texture;
		unsigned int texId;
	public:
    const QImage& getQImage() const { return texture; }

		bool load( const std::string & path );
    bool load( const QImage& img );
		ResTexture():Resource(RT_TEXTURE), texId(0){}
		ResTexture(const std::string & path):Resource(RT_TEXTURE){load(path);}

		int getWidth()
		{
			return texture.width();
		}

		int getHeight()
		{
			return texture.height();
		}

		int getTexture()
		{
			return texId;
		}
};


#endif
