#include "myLib.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *) 0x6000000;
u32 vBlankCounter = 0;

void setPixel(int row, int col, u16 color) {
    videoBuffer[OFFSET(row, col, 240)] = color;
}

// // Draw an image onto the screen using DMA.
// // It's guaranteed that this image will be 240 * 160
// // which is the size of the GBA screen.
// // You MUST use DMA in this!

void drawFullScreenImage(const u16 *img) {
    DMA[3].src = img;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 240 * 160 | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON; //delete this after you write the function
}

//  drawImage3
// * A function that will draw an arbitrary sized image
// * onto the screen (with DMA).
// * @param r row to draw the image
// * @param c column to draw the image
// * @param width width of the image
// * @param height height of the image
// * @param image Pointer to the first element of the image.
void drawImage3(int r, int c, int width, int height, const u16*
image) {
    for (int x = 0; x < height; x++) {
        DMA[3].src = &image[OFFSET(x, 0, width)];
        DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
        DMA[3].cnt = (width) | DMA_ON;
    }
}

/* drawRect3
* A DMA Implementation of drawRect
*/
void drawRect3(int r, int c, int width, int height, u16 color) {
    for (int x = 0; x < height; x++) {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
        DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_ON;
    }
}

/* drawChar
* draw character
*/
void drawChar(int row, int col, char ch, unsigned short color)
{
    for(int r = 0; r<8; r++)
    {
        for(int c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48])
            {
                setPixel(row+r, col+c, color);
            }
        }
    }
}

/* drawString
* draw String
*/
void drawString(int row, int col, char *str, unsigned short color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}
