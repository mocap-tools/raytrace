#include "bmp.h"
#include <string.h> // for memset

using namespace std;

BMP::BMP(const int width, const int height)
    : m_width(width), m_height(height)
{
    m_pixelArray = new pixel24[width*height];
}

BMP::~BMP()
{
    delete m_pixelArray;
}


void BMP::generateShit()
{
    for(int i=0;i<m_width;++i)
    {
        for(int j=0;j<m_height;++j)
        {
            setPixelAt(i,j,i,i,i);
        }
    }
}

void BMP::setPixelAt(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    pixel24* pix = &m_pixelArray[x+y*m_width];
    pix->r = r;
    pix->g = g;
    pix->b = b;
}

ostream& operator<<(ostream& os, const BMP& b)
{
    unsigned int arraysize = b.m_width*b.m_height*4 + 10000;
    unsigned char* bmpdata =  new unsigned char[arraysize];
    
    // Magic word
    bmpdata[0] = 'B';
    bmpdata[1] = 'M';
    
    // File size, written at the end
            
    // reserved words, actually we can put anything there
    memset(&bmpdata[6], 0, 4);

    // offset to pixel data
    unsigned int offset = 54;
    memcpy(&bmpdata[10], &offset, 4);
    
    // DIB header
    unsigned int dib_size = 40;    
    memcpy(&bmpdata[14], &dib_size, 4);
       
    // width and height of bitmap
    memcpy(&bmpdata[18], &b.m_width, 4);
    memcpy(&bmpdata[22], &b.m_height, 4);
    
    // number of color planes
    unsigned short color_planes = 1;
    color_planes = color_planes;
    memcpy(&bmpdata[26], &color_planes, 2);
    
    unsigned short bits_per_pixel = 24;
    memcpy(&bmpdata[28], &bits_per_pixel, 2);
    
    // compression method
    memset(&bmpdata[30], 0, 4);
    
    // compressed size, written at the end
    
    unsigned int horz_vert_resolution = 2835;
    memcpy(&bmpdata[38], &horz_vert_resolution, 4);
    memcpy(&bmpdata[42], &horz_vert_resolution, 4);
    
    // number of colors in palette and important colors will go zero
    memset(&bmpdata[46], 0, 8);
    
    // Write pixel array, bottom row first
    offset = 54;
    for(int i = b.m_height-1; i >= 0; --i)
    {

        int rowlength = 0;
        for(int j = 0; j < b.m_width; ++j)
        {           
            pixel24* pix = &b.m_pixelArray[i*b.m_width + j];
            bmpdata[offset] = pix->b;
            bmpdata[offset+1] = pix->g;
            bmpdata[offset+2] = pix->r;            
            offset += 3;
            rowlength += 3;
        }

        // zero pad so that each row length is divisable by four
        while(rowlength % 4)
        {
            ++offset;
            ++rowlength;            
        }

    }
    
    // now we write file size to header and compressed size
    unsigned int filesz = offset;
    unsigned int raw_img_size = 54 - offset;
    memcpy(&bmpdata[2], &filesz, 4);
    memcpy(&bmpdata[34], &raw_img_size, 4);
    
    os.write((const char*)bmpdata, offset);
    os.flush();
    // clean up
    delete bmpdata;
    return os;
}
