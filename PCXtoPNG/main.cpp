#include <iostream>
#include <fstream>
#include "pcx.h"
#include <png.h>
#include <zlib.h>

void CreatePNGImage(unsigned char* starcraftImage, unsigned char* palatte, char* outputName);

int main(int argc, char* argv[])
{
	unsigned char* specialFile;
	unsigned char* palatte;
	for(int i = 1; i < argc; i++)
	{
		std::string fileName(argv[i]);
		Pcx infile(fileName);

		std::cout << fileName;

		fileName = fileName.replace(fileName.size()-3, 3, "png");

		std::cout << " --> " << fileName << std::endl;

		specialFile = infile.getImage();
		palatte = infile.getPalatte();
		CreatePNGImage(specialFile, palatte, (char*) fileName.c_str());
	}
}

void CreatePNGImage(unsigned char* starcraftImage, unsigned char* palatte, char* outputName)
{
	png_bytep* row_pointers;
	FILE* pngFile;
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	int i;
	png_uint_32 width = 640;
	png_uint_32 height = 480;
	png_color* truePalette = (png_color*) malloc(sizeof(png_color) * 256);


	for(i = 0; i < 256; i++)
	{
		truePalette[i].green = palatte[i*3 + 1];
		truePalette[i].blue = palatte[i*3 + 2];
		truePalette[i].red = palatte[i*3 + 0];
	}

	pngFile = fopen(outputName, "wb");
	png_init_io(png_ptr, pngFile);

	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);
	png_set_PLTE(png_ptr, info_ptr, (png_const_colorp) truePalette, 256);
	png_write_info(png_ptr, info_ptr);

	row_pointers = (png_bytep*) malloc((sizeof(png_bytep) * 480) + 1);
	for(i = 0; i < 480; i++)
	{
		row_pointers[i] = &(starcraftImage[i * 640]);
	}
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	free(row_pointers);
	free(starcraftImage);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(pngFile);
}