#ifndef PCX_H
#define PCX_H

#define	NO_ERROR 0
#define FILE_NOT_OPENED 1
#define INSUFFICIENT_MEMORY 2
#define TOO_MANY_ARGUMENTS 3

const unsigned int IMAGE_SIZE=307200u; // Size of PCX bitmap

#include <string>

struct pcx_header {
	char manufacturer;    // Always set to 0
	char version;         // Always 5 for 256-color files
	char encoding;        // Always set to 1
	char bits_per_pixel;  // Should be 8 for 256-color files
	int  xmin,ymin;       // Coordinates for top left corner
	int  xmax,ymax;       // Width and height of image
	int  hres;            // Horizontal resolution of image
	int  vres;            // Vertical resolution of image
	char palette16[48];   // EGA palette; not used for
												//  256-color files
	char reserved;        // Reserved for future use
	char color_planes;    // Color planes
	int  bytes_per_line;  // Number of bytes in 1 line of
												//  pixels
	int  palette_type;    // Should be 2 for color palette
	char filler[58];      // Nothing but junk
};



// Class for loading 256-color VGA PCX files
class Pcx
{
private:
	// Private functions and variables for class Pcx
	// Bitmap loading function:
	// Palette loading function:
	//void load_palette();
	std::string fileName;

protected:
	unsigned char palette[3*256]; // Array holding the 768-
																//  byte palette
public:

	Pcx(std::string filename);
	~Pcx();
	// Function to load PCX data:
	int Load(char* filename);
	// External access to image and palette:
	unsigned char *Palette()
		{ return palette; }
	unsigned char* load_image(void);
	unsigned char* getImage(void);
	unsigned char* pcxImage;
	pcx_header header;    // Structure for holding the PCX header
	unsigned char* getPalatte(void);
};

#endif