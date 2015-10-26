#include "fb.h"
#include "util.h"

uint8_t *fb;

uint8_t *fbSet(uint8_t *data) {
   uint8_t *o = fb;
   fb = data;
   return o;
}

void fbClear(uint8_t col) {
   // clear of framebuffer:
   // memset of framebuffer: ~1.25ms
   // loop of uint32 of framebuffer -O3: ~0.6ms
   // loop of uint32 of framebuffer -Os: ~0.8ms
   // loop of uint8 of framebuffer -O3: ~1.2ms
   if (!fb)
      return;

   uint32_t c = col;
   c |= c << 8;
   c |= c << 16;
   for (int i = 0; i < FBSIZE / 4; i++)
      ((uint32_t *)fb)[i] = c;
}

void fbSetPixel(GPoint p, uint8_t col) {
   if (!fb)
      return;
   fb[p.x + p.y * FBW] = col;
}

void fbFillRect(GRect r, uint8_t col) {
   if (!fb)
      return;
   for (int y = r.origin.y, yend = r.origin.y + r.size.h; y < yend; y++) {
      uint8_t *row = fb + y * FBW;
      for (int x = r.origin.x, xend = r.origin.x + r.size.w; x < xend; x++) {
         row[x] = col;
      }
   }
}

void fbFillRandom(GRect r) {
   if (!fb)
      return;
   for (int y = r.origin.y, yend = r.origin.y + r.size.h; y < yend; y++) {
      uint8_t *row = fb + y * FBW;
      for (int x = r.origin.x, xend = r.origin.x + r.size.w; x < xend; x++) {
         row[x] = (uint8_t)((hash2(GPoint(x, y)) >> 8) & 0xff);
      }
   }
}
