/**************
*This file may change between projects
* ~Shep
**************/

#ifndef TEXTURELOAD_CPP
#define TEXTURELOAD_CPP

#include "texture.h"
#include <qgl.h>
#include <GL/glu.h>
#include <iostream>

enum IMAGE_TYPE
{
	IMG_NONE, IMG_TIFF, IMG_PNG, IMG_TGA, IMG_BMP
};


IMAGE_TYPE getImageType(const QString & path)
{
	if ( path.endsWith(".tif"))
		return IMG_TIFF;
	if ( path.endsWith(".png"))
		return IMG_PNG;
	if ( path.endsWith(".tga"))
		return IMG_TGA;
	if ( path.endsWith(".bmp"))
		return IMG_BMP;

	return IMG_NONE;
}


bool ResTexture::load( const QImage& img )
{	

	QImage fixed( img.width(), img.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, img );
	painter.end();

	QImage texture = QGLWidget::convertToGLFormat( fixed );

  glEnable( GL_TEXTURE );
  glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  return false;
}

#include <iostream>
using namespace std;

bool ResTexture::load( const std::string & path )
{
  glEnable( GL_TEXTURE );
  glEnable( GL_TEXTURE_2D );
	switch (getImageType(path.c_str()))
	{
		case IMG_TIFF:
      loadTIFF(path.c_str(),texId,texture);
      break;
		case IMG_PNG:
      loadPNG(path.c_str(),texId,texture);
      break;
		case IMG_TGA:
      loadTGA(path.c_str(),texId,texture);
      break;
		case IMG_BMP:
      loadBMP(path.c_str(),texId,texture);
		default:
      return false;
	}


  return true;
}

bool loadTIFF(const QString & path, unsigned int & texId, QImage & texture)
{

	QImage buffer;
	if (!buffer.load( path ))
	{
		std::cout << "Load Texture Error: TIFF File would not load\n";
    std::cout << "File: " << qPrintable(path) << std::endl;
		return false;
	}

	QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, buffer );
	painter.end();

	texture = QGLWidget::convertToGLFormat( fixed );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );
	//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

	return true;
}

bool loadPNG(const QString & path, unsigned int & texId, QImage & texture)
{
	QImage buffer;

	if (!buffer.load( path ))
	{
		std::cout << "Load Texture Error: PNG File would not load\n";
    std::cout << "File: " << qPrintable(path) << std::endl;
		return false;
	}

	QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, buffer );
	painter.end();

  

	texture = QGLWidget::convertToGLFormat( fixed );

	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

	return true;
}

bool loadTGA(const QString & path, unsigned int & texId, QImage & texture)
{
		QImage buffer;


	if (!buffer.load( path ))
	{
		std::cout << "Load Texture Error: TGA File would not load\n";
    std::cout << "File: " << qPrintable(path) << std::endl;
		return false;
	}


	QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, buffer );
	painter.end();

	texture = QGLWidget::convertToGLFormat( fixed );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );
	//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

	return true;
}

bool loadBMP(const QString & path, unsigned int & texId, QImage & texture)
{
	QImage buffer;

	if (!buffer.load( path ))
	{
		std::cout << "Load Texture Error: BMP File would not load\n";
    std::cout << "File: " << qPrintable(path) << std::endl;
		return false;
	}

	QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, buffer );
	painter.end();

	texture = QGLWidget::convertToGLFormat( fixed );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );
	//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

	return true;
}

#endif
