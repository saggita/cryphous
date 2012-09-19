#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "../CrystalRenderer/ColorBuffer.h"
#include "../CrystalRenderer/NormalBuffer.h"
#include "../CrystalRenderer/DepthBuffer.h"

#pragma warning( disable: 4996 )

namespace Crystal{
	namespace Renderer{

// http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB ÇéQçlÇ…çÏê¨ÅD
class Bitmap{
private:
	const unsigned int height;
	const unsigned int width;

	enum {
		FILEHEADERSIZE = 14,
		INFOHEADERSIZE = 40,
		HEADERSIZE = FILEHEADERSIZE + INFOHEADERSIZE,
	};
	
public:
	Bitmap(int width, int height) :
		width( width),
		height( height)
	{
	}

	~Bitmap()
	{
	}

	void dump(const std::string& fileName, const ColorBuffer& buffer)
	{
		FILE* fp = fopen(fileName.c_str(), "wb");

		dumpHeader(fp);
		
		std::vector<unsigned char> lineColor( getRealWidth());
		for(unsigned int i=0; i<height; i++){
			for(unsigned int j=0; j<width; j++){
				lineColor[j*3] = static_cast<unsigned char>( buffer.getColor(Point2d(j,i)).blue * 255 );
				lineColor[j*3 + 1] = static_cast<unsigned char>( buffer.getColor(Point2d(j,i)).green * 255 );
				lineColor[j*3 + 2] = static_cast<unsigned char>( buffer.getColor(Point2d(j,i)).red * 255 );
			}
			for(unsigned int j= width*3; j < getRealWidth(); j++){
				lineColor[j] = 0;
			}
			fwrite( &(lineColor.front()), sizeof(unsigned char), getRealWidth(), fp);
		}

		fclose(fp);
	}

	void dump(const std::string& fileName, const NormalBuffer& buffer)
	{
		FILE* fp = fopen(fileName.c_str(), "wb");

		dumpHeader(fp);
	
		std::vector<unsigned char> lineColor( getRealWidth());
		for(unsigned int i=0; i<height; i++){
			for(unsigned int j=0; j<width; j++){
				lineColor[j*3] = static_cast<unsigned char>( buffer.getNormal(Point2d(j,i)).getZ() * 255 );
				lineColor[j*3 + 1] = static_cast<unsigned char>( buffer.getNormal(Point2d(j,i)).getY() * 255 );
				lineColor[j*3 + 2] = static_cast<unsigned char>( buffer.getNormal(Point2d(j,i)).getX() * 255 );
			}
			for(unsigned int j= width*3; j < getRealWidth(); j++){
				lineColor[j] = 0;
			}
			fwrite( &(lineColor.front()), sizeof(unsigned char), getRealWidth(), fp);
		}

		fclose(fp);
	}

	void dump(const std::string& fileName, const DepthBuffer& buffer)
	{
		FILE* fp = fopen(fileName.c_str(), "wb");

		dumpHeader(fp);
	
		std::vector<unsigned char> lineColor( getRealWidth());
		for(unsigned int i=0; i<height; i++){
			for(unsigned int j=0; j<width; j++){
				lineColor[j*3] = static_cast<unsigned char>( buffer.getDepth(Point2d(j,i)) * 255 );
				lineColor[j*3 + 1] = static_cast<unsigned char>( buffer.getDepth(Point2d(j,i)) * 255 );
				lineColor[j*3 + 2] = static_cast<unsigned char>( buffer.getDepth(Point2d(j,i)) * 255 );
			}
			for(unsigned int j= width*3; j < getRealWidth(); j++){
				lineColor[j] = 0;
			}
			fwrite( &(lineColor.front()), sizeof(unsigned char), getRealWidth(), fp);
		}

		fclose(fp);
	}

private:
	unsigned int getRealWidth() const { return width * 3 + width % 4; }

	void dumpHeader(FILE* fp)
	{
		unsigned char header_buf[HEADERSIZE];
		unsigned int fileSize = height * getRealWidth() + HEADERSIZE;
		unsigned int offset_to_data = HEADERSIZE;
		unsigned long info_header_size = INFOHEADERSIZE;
		unsigned int planes = 1;
		unsigned int color = 24;
		unsigned long compress = 0;
		unsigned long size = height * getRealWidth();
		long xppm = 1;
		long yppm = 1;

		for( int i = 0; i < HEADERSIZE; ++i ) {
			header_buf[i] = 0;
		}
		header_buf[0] = 'B';
		header_buf[1] = 'M';
		memcpy(header_buf + 2, &fileSize, sizeof(fileSize));
		memcpy(header_buf + 10, &offset_to_data, sizeof(fileSize));
		memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
		memcpy(header_buf + 18, &width, sizeof(width));
		memcpy(header_buf + 22, &height, sizeof(height));
		memcpy(header_buf + 26, &planes, sizeof(planes));
		memcpy(header_buf + 28, &color, sizeof(color));
		memcpy(header_buf + 30, &compress, sizeof(compress));
		memcpy(header_buf + 34, &size, sizeof(size));
		memcpy(header_buf + 38, &xppm, sizeof(xppm));
		memcpy(header_buf + 42, &yppm, sizeof(yppm));
		
		fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
	}

};

	}
}

#endif
