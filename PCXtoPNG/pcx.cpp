#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

#include "pcx.h"

// Pcx class destructor
Pcx::~Pcx()
{
	// if pointers have changed from initial 0
	// then release memory
}


int Pcx::Load(char* filename)
{

	return 0;
}

unsigned char* Pcx::getImage(void)
{
	return this->pcxImage;
}

unsigned char* Pcx::getPalatte(void)
{
	std::ifstream infile(this->fileName.c_str(), std::ios::in | std::ios::binary);
	int tell;
	unsigned char* palatte = (unsigned char*) calloc(768, 1);
	infile.seekg(0, std::ios::end);
	tell = infile.tellg();
	tell -= 768;
	infile.seekg(tell, std::ios::beg);
	infile.read((char*) palatte, 768);
	infile.close();

	return palatte;

}

Pcx::Pcx(std::string fileName)
{
	this->fileName = fileName;
	this->pcxImage = load_image();
}

// Decompress bitmap and store in buffer
unsigned char* Pcx::load_image(void)
{
	// Symbolic constants for encoding modes, with
	// BYTEMODE representing uncompressed byte mode
	// and RUNMODE representing run-length encoding mode:
	std::ifstream pcxFile(this->fileName.c_str(), std::ios::in | std::ios::binary);
	const int BYTEMODE = 0;
	const int RUNMODE = 1;

	int mode = BYTEMODE;				// Current encoding mode being used,
										//  initially set to BYTEMODE
	unsigned char curbyte;			// Next byte for buffer
	unsigned char bytecount;			// Counter for runs
	unsigned char* image = (unsigned char*) malloc(IMAGE_SIZE);
	int bufCount = 0;
	unsigned char* buffer;
	int lengthBuffer;
	int i = 0;

	pcxFile.seekg(0, std::ios::end);
	lengthBuffer = pcxFile.tellg();  
	lengthBuffer = lengthBuffer - 128 - 768; //size header - size palette
	pcxFile.seekg(128, std::ios::beg);
	buffer = (unsigned char*) malloc(lengthBuffer); 
	pcxFile.read((char*) buffer, lengthBuffer);
	pcxFile.close();

	while(i < IMAGE_SIZE) 
	{
		curbyte = buffer[bufCount++];
		if(curbyte > 0xbf)
		{
			bytecount = (int)((int)curbyte & 0x3F);
			curbyte = buffer[bufCount++];
			memset(image + i, curbyte, bytecount);
			i += bytecount;
		}
		else
		{
			image[i] = curbyte;
			i++;
		}
	} 
	free(buffer);
	return image;
}
