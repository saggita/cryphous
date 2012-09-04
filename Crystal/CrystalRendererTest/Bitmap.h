#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef struct{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}RGB;

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#pragma warning( disable: 4996 )

// http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB ÇéQçlÇ…çÏê¨ÅD
class Image{
public:
	unsigned int height;
	unsigned int width;
	std::vector<RGB> colors;

	enum {
		FILEHEADERSIZE = 14,
		INFOHEADERSIZE = 40,
		HEADERSIZE = FILEHEADERSIZE + INFOHEADERSIZE,
	};
	
	Image(int width, int height) :
		colors( width * height),
		width( width),
		height( height)
	{
	}

	~Image()
	{
	}

	void dump(char *filename)
	{
		unsigned int real_width = width*3 + width%4;;
		unsigned char *bmp_line_data;
		unsigned char header_buf[HEADERSIZE];
		unsigned int file_size = height * real_width + HEADERSIZE;
		unsigned int offset_to_data = HEADERSIZE;
		unsigned long info_header_size = INFOHEADERSIZE;
		unsigned int planes = 1;
		unsigned int color = 24;
		unsigned long compress = 0;
		unsigned long data_size = height * real_width;
		long xppm = 1;
		long yppm = 1;

		FILE* fp = fopen(filename, "wb");
	
		for( int i = 0; i < HEADERSIZE; ++i ) {
			header_buf[i] = 0;
		}
		header_buf[0] = 'B';
		header_buf[1] = 'M';
		memcpy(header_buf + 2, &file_size, sizeof(file_size));
		memcpy(header_buf + 10, &offset_to_data, sizeof(file_size));
		memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
		memcpy(header_buf + 18, &width, sizeof(width));
		memcpy(header_buf + 22, &height, sizeof(height));
		memcpy(header_buf + 26, &planes, sizeof(planes));
		memcpy(header_buf + 28, &color, sizeof(color));
		memcpy(header_buf + 30, &compress, sizeof(compress));
		memcpy(header_buf + 34, &data_size, sizeof(data_size));
		memcpy(header_buf + 38, &xppm, sizeof(xppm));
		memcpy(header_buf + 42, &yppm, sizeof(yppm));
		
		fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
	
		bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width);

		for(unsigned int i=0; i<height; i++){
			for(unsigned int j=0; j<width; j++){
				bmp_line_data[j*3] = colors[(height - i - 1)*width + j].b;
				bmp_line_data[j*3 + 1] = colors[(height - i - 1)*width + j].g;
				bmp_line_data[j*3 + 2] = colors[(height - i - 1)*width + j].r;
			}
			for(unsigned int j=width*3; j<real_width; j++){
				bmp_line_data[j] = 0;
			}
			fwrite(bmp_line_data, sizeof(unsigned char), real_width, fp);
		}

		free(bmp_line_data);

		fclose(fp);
	}

};

#endif
