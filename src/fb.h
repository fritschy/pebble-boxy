#ifndef FB_H
#define FB_H

#include <pebble.h>

#define FBW 144
#define FBH 168
#define FBSIZE (FBW * FBH)
#define FBW2 (FBW / 2)
#define FBH2 (FBH / 2)
#define FBC GPoint(FBW2, FBH2)
#define FBBOUNDS GRect(0, 0, FBW, FBH)

uint8_t *fbSet(uint8_t *fb);
void fbClear(uint8_t col);
void fbSetPixel(GPoint p, uint8_t col);
void fbFillRect(GRect r, uint8_t col);
void fbFillRandom(GRect r);

#endif // !FB_H
