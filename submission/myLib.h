typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

//function headers
void waitForVblank(void);
int main(void);

#define OFFSET(r, c, rowlen) ((c)+(rowlen)*(r))

#define UNUSED_PARAM(param) ((void)((param)))

#define MODE3 3
#define BG2_ENABLE (1<<10)

// #define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
// #define WHITE COLOR(31,31,31)
// #define GREEN COLOR(0, 31, 0)
// #define BLACK 0

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define GRAY COLOR(5, 5, 5)
#define LIGHTGRAY COLOR(20, 20, 20)

#define WIDTH 240 //this is the width of the GBA emulator

/* Mode 3 */
extern volatile unsigned short *videoBuffer;               // 0x6000000
// Need in one of your .c files:
//     volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
#define REG_DISPCNT  *(volatile unsigned short *) 0x4000000
#define SCANLINECOUNTER (volatile unsigned short *)0x4000006


//BUTTONS
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define NBUTTONS        10

#define BUTTONS (*(volatile unsigned int *)0x4000130)
#define KEY_DOWN(key, buttons) (~(buttons) & (key))
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & (1<<key))

#define KEY_JUST_PRESSED(key, buttons, oldbuttons) (~(buttons) & (key) & ~(~(oldbuttons) & (key)))

/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

// ---------------------------------------------------------------------------
//                       DRAWING
// ---------------------------------------------------------------------------
void setPixel(int row, int col, u16 color);

// Draw an image onto the screen using DMA.
// It's guaranteed that this image will be 240 * 160
// which is the size of the GBA screen.
// You MUST use DMA in this!
void drawFullScreenImage(const u16 *img);

/* drawImage3
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage3(int r, int c, int width, int height, const u16* image);

/* drawRect3
* A DMA Implementation of drawRect
*/
void drawRect3(int r, int c, int width, int height, u16 color);

/* drawChar
* draw character
*/
void drawChar(int row, int col, char ch, unsigned short color);

/* drawString
* draw String
*/
void drawString(int row, int col, char *str, unsigned short color);



extern const unsigned char fontdata_6x8[12288];





extern u32 vBlankCounter;
