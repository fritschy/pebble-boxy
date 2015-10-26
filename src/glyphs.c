#include "glyphs.h"
#include "fb.h"

#define GWIDTH 7
#define GHEIGHT 5

struct glyph {
   uint8_t mask[5]; // pixels we actually fill with fg color
   uint8_t w;       // actual glyph width in pels
} __attribute__((packed));

struct glyph const alnum[] = {
   { { 0b11111000, // 0
       0b10001000,
       0b10001000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b11000000, // 1
       0b01000000,
       0b01000000,
       0b01000000,
       0b01000000 }, 2 },
   { { 0b11111000, // 2
       0b00001000,
       0b11111000,
       0b10000000,
       0b11111000 }, 5 },
   { { 0b11111000, // 3
       0b00001000,
       0b01111000,
       0b00001000,
       0b11111000 }, 5 },
   { { 0b10001000, // 4
       0b10001000,
       0b11111000,
       0b00001000,
       0b00001000 }, 5 },
   { { 0b11111000, // 5
       0b10000000,
       0b11111000,
       0b00001000,
       0b11111000 }, 5 },
   { { 0b11111000, // 6
       0b10000000,
       0b11111000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b11111000, // 7
       0b00001000,
       0b00001000,
       0b00001000,
       0b00001000 }, 5 },
   { { 0b11111000, // 8
       0b10001000,
       0b11111000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b11111000, // 9
       0b10001000,
       0b11111000,
       0b00001000,
       0b11111000 }, 5 },

   { { 0b11111000, // A
       0b10001000,
       0b11111000,
       0b10001000,
       0b10001000 }, 5 },
   { { 0b11110000, // B
       0b10001000,
       0b11111000,
       0b10001000,
       0b11110000 }, 5 },
   { { 0b11110000, // C
       0b10000000,
       0b10000000,
       0b10000000,
       0b11110000 }, 4 },
   { { 0b11110000, // D
       0b10001000,
       0b10001000,
       0b10001000,
       0b11110000 }, 5 },
   { { 0b11111000, // E
       0b10000000,
       0b11110000,
       0b10000000,
       0b11111000 }, 5 },
   { { 0b11111000, // F
       0b10000000,
       0b11110000,
       0b10000000,
       0b10000000 }, 5 },
   { { 0b11111000, // G
       0b10000000,
       0b10011000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b10001000, // H
       0b10001000,
       0b11111000,
       0b10001000,
       0b10001000 }, 5 },
   { { 0b10000000, // I
       0b10000000,
       0b10000000,
       0b10000000,
       0b10000000 }, 1 },
   { { 0b11110000, // J
       0b00010000,
       0b00010000,
       0b10010000,
       0b01100000 }, 4 },
   { { 0b10010000, // K
       0b10100000,
       0b11000000,
       0b10100000,
       0b10010000 }, 4 },
   { { 0b10000000, // L
       0b10000000,
       0b10000000,
       0b10000000,
       0b11110000 }, 4 },
   { { 0b11111110, // M
       0b10010010,
       0b10010010,
       0b10010010,
       0b10010010 }, 7 },
   { { 0b11111000, // N
       0b10001000,
       0b10001000,
       0b10001000,
       0b10001000 }, 5 },
   { { 0b11111000, // O
       0b10001000,
       0b10001000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b11111000, // P
       0b10001000,
       0b11111000,
       0b10000000,
       0b10000000 }, 5 },
   { { 0b11111000, // Q
       0b10001000,
       0b10001000,
       0b10011000,
       0b11111000 }, 5 },
   { { 0b11111000, // R
       0b10001000,
       0b11110000,
       0b10001000,
       0b10001000 }, 5 },
   { { 0b11111000, // S
       0b10000000,
       0b11111000,
       0b00001000,
       0b11111000 }, 5 },
   { { 0b11111000, // T
       0b00100000,
       0b00100000,
       0b00100000,
       0b00100000 }, 5 },
   { { 0b10001000, // U
       0b10001000,
       0b10001000,
       0b10001000,
       0b11111000 }, 5 },
   { { 0b10001000, // V
       0b10001000,
       0b01010000,
       0b01010000,
       0b00100000 }, 5 },
   { { 0b10010010, // W
       0b10010010,
       0b10010010,
       0b10010010,
       0b11111110 }, 7 },
   { { 0b10001000, // X
       0b01010000,
       0b00100000,
       0b01010000,
       0b10001000 }, 5 },
   { { 0b10001000, // Y
       0b10001000,
       0b01110000,
       0b00100000,
       0b00100000 }, 5 },
   { { 0b11111000, // Z
       0b00010000,
       0b00100000,
       0b01000000,
       0b11111000 }, 5 },

   { { 0b00000000, // :
       0b00000000,
       0b10000000,
       0b00000000,
       0b10000000 }, 1 },

   { { 0b00000000, // tab, narrow space
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000 }, 1 },

   { { 0b00000000, // vtab, not so narrow space
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000 }, 3 },

   { { 0b00000000, // space
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000 }, 12 },
};

static inline int mask_bit_set(uint8_t const m[const static 5], int x, int y) {
   return (m[y] >> (7-x)) & 1;
}

#ifdef GLYPH_SIZE_1
static void drawGlyph1(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y))
            fb[p.x+x + (p.y+y) * FBW] = c;
   fbSet(fb);
}
#endif

static void drawGlyph2(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0, by = p.y+y*2; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y)) {
            int bx = p.x+x*2;
            fb[bx   + (by)   * FBW] = c;
            fb[bx+1 + (by)   * FBW] = c;
            fb[bx   + (by+1) * FBW] = c;
            fb[bx+1 + (by+1) * FBW] = c;
         }
   fbSet(fb);
}

#ifdef GLYPH_SIZE_3
static void drawGlyph3(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0, by = p.y+y*3; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y)) {
            int bx = p.x+x*3;
            fb[bx   + (by)   * FBW] = c;
            fb[bx+1 + (by)   * FBW] = c;
            fb[bx+2 + (by)   * FBW] = c;
            fb[bx   + (by+1) * FBW] = c;
            fb[bx+1 + (by+1) * FBW] = c;
            fb[bx+2 + (by+1) * FBW] = c;
            fb[bx   + (by+2) * FBW] = c;
            fb[bx+1 + (by+2) * FBW] = c;
            fb[bx+2 + (by+2) * FBW] = c;
         }
   fbSet(fb);
}
#endif

#ifdef GLYPH_SIZE_4
static void drawGlyph4(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0, by = p.y+y*4; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y)) {
            int bx = p.x+x*4;
            fb[bx   + (by)   * FBW] = c;
            fb[bx+1 + (by)   * FBW] = c;
            fb[bx+2 + (by)   * FBW] = c;
            fb[bx+3 + (by)   * FBW] = c;
            fb[bx   + (by+1) * FBW] = c;
            fb[bx+1 + (by+1) * FBW] = c;
            fb[bx+2 + (by+1) * FBW] = c;
            fb[bx+3 + (by+1) * FBW] = c;
            fb[bx   + (by+2) * FBW] = c;
            fb[bx+1 + (by+2) * FBW] = c;
            fb[bx+2 + (by+2) * FBW] = c;
            fb[bx+3 + (by+2) * FBW] = c;
            fb[bx   + (by+3) * FBW] = c;
            fb[bx+1 + (by+3) * FBW] = c;
            fb[bx+2 + (by+3) * FBW] = c;
            fb[bx+3 + (by+3) * FBW] = c;
         }
   fbSet(fb);
}
#endif

static void drawGlyph5(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0, by = p.y+y*5; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y)) {
            int bx = p.x+x*5;
            fb[bx   + (by)   * FBW] = c;
            fb[bx+1 + (by)   * FBW] = c;
            fb[bx+2 + (by)   * FBW] = c;
            fb[bx+3 + (by)   * FBW] = c;
            fb[bx+4 + (by)   * FBW] = c;
            fb[bx   + (by+1) * FBW] = c;
            fb[bx+1 + (by+1) * FBW] = c;
            fb[bx+2 + (by+1) * FBW] = c;
            fb[bx+3 + (by+1) * FBW] = c;
            fb[bx+4 + (by+1) * FBW] = c;
            fb[bx   + (by+2) * FBW] = c;
            fb[bx+1 + (by+2) * FBW] = c;
            fb[bx+2 + (by+2) * FBW] = c;
            fb[bx+3 + (by+2) * FBW] = c;
            fb[bx+4 + (by+2) * FBW] = c;
            fb[bx   + (by+3) * FBW] = c;
            fb[bx+1 + (by+3) * FBW] = c;
            fb[bx+2 + (by+3) * FBW] = c;
            fb[bx+3 + (by+3) * FBW] = c;
            fb[bx+4 + (by+3) * FBW] = c;
            fb[bx   + (by+4) * FBW] = c;
            fb[bx+1 + (by+4) * FBW] = c;
            fb[bx+2 + (by+4) * FBW] = c;
            fb[bx+3 + (by+4) * FBW] = c;
            fb[bx+4 + (by+4) * FBW] = c;
         }
   fbSet(fb);
}

#ifdef GLYPH_SIZE_6
static void drawGlyph6(GPoint p, int8_t g, uint8_t c) {
   uint8_t *fb = fbSet(NULL);
   for (int y = 0; y < GHEIGHT; y++)
      for (int x = 0, by = p.y+y*6; x < GWIDTH; x++)
         if (mask_bit_set(alnum[g].mask, x, y)) {
            int bx = p.x+x*5;
            fb[bx   + (by)   * FBW] = c;
            fb[bx+1 + (by)   * FBW] = c;
            fb[bx+2 + (by)   * FBW] = c;
            fb[bx+3 + (by)   * FBW] = c;
            fb[bx+4 + (by)   * FBW] = c;
            fb[bx+5 + (by)   * FBW] = c;
            fb[bx   + (by+1) * FBW] = c;
            fb[bx+1 + (by+1) * FBW] = c;
            fb[bx+2 + (by+1) * FBW] = c;
            fb[bx+3 + (by+1) * FBW] = c;
            fb[bx+4 + (by+1) * FBW] = c;
            fb[bx+5 + (by+1) * FBW] = c;
            fb[bx   + (by+2) * FBW] = c;
            fb[bx+1 + (by+2) * FBW] = c;
            fb[bx+2 + (by+2) * FBW] = c;
            fb[bx+3 + (by+2) * FBW] = c;
            fb[bx+4 + (by+2) * FBW] = c;
            fb[bx+5 + (by+2) * FBW] = c;
            fb[bx   + (by+3) * FBW] = c;
            fb[bx+1 + (by+3) * FBW] = c;
            fb[bx+2 + (by+3) * FBW] = c;
            fb[bx+3 + (by+3) * FBW] = c;
            fb[bx+4 + (by+3) * FBW] = c;
            fb[bx+5 + (by+3) * FBW] = c;
            fb[bx   + (by+4) * FBW] = c;
            fb[bx+1 + (by+4) * FBW] = c;
            fb[bx+2 + (by+4) * FBW] = c;
            fb[bx+3 + (by+4) * FBW] = c;
            fb[bx+4 + (by+4) * FBW] = c;
            fb[bx+5 + (by+4) * FBW] = c;
            fb[bx   + (by+5) * FBW] = c;
            fb[bx+1 + (by+5) * FBW] = c;
            fb[bx+2 + (by+5) * FBW] = c;
            fb[bx+3 + (by+5) * FBW] = c;
            fb[bx+4 + (by+5) * FBW] = c;
            fb[bx+5 + (by+5) * FBW] = c;
         }
   fbSet(fb);
}
#endif

// draw a glyph g (index into alnum or -1 for space) with fg color at p
// with pixel size s (small font is 2, large one 5), return actual pixel width
// 
// some performance numbers (tested in a loop of 100 repetitions):
// - drawing all glyphs once with size 3 takes ~0.5ms, that is about
//   0.01-0.02ms per glyph
// - size 5 glyphs take ~0.9ms for all glyphs
// - size 6 glyphs tale 1.1ms
// - size 6 with fbFillRect takes about 5ms for all glyphs
int drawGlyph(GPoint p, int8_t g, uint8_t s, uint8_t c) {
   // I have a feeling that this is quite enough... maybe a tad too much
   switch (s) {
#ifdef GLYPH_SIZE_1
      case 1:
         drawGlyph1(p, g, c);
         break;
#endif
      case 2:
         drawGlyph2(p, g, c);
         break;
#ifdef GLYPH_SIZE_3
      case 3:
         drawGlyph3(p, g, c);
         break;
#endif
#ifdef GLYPH_SIZE_4
      case 4:
         drawGlyph4(p, g, c);
         break;
#endif
      case 5:
         drawGlyph5(p, g, c);
         break;
#ifdef GLYPH_SIZE_6
      case 6:
         drawGlyph6(p, g, c);
         break;
#endif
      default:
         for (int y = 0; y < GHEIGHT; y++)
            for (int x = 0, by = p.y+y*s; x < GWIDTH; x++)
               if (mask_bit_set(alnum[g].mask, x, y))
                  fbFillRect(GRect(p.x+x*s, by, s, s), c);
   }
   return alnum[g].w * s;
}

int glyphSize(uint8_t g, uint8_t s) {
   return alnum[g].w * s;
}
