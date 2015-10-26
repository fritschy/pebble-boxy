#ifndef UTIL_H
#define UTIL_H

// hash and in to [0,0x10000)
static inline unsigned hash1(unsigned n) {
   return (sin_lookup((n ^ 74623u) & 0xffff) * 27581u) & 0xffff;
}

// hash a point, e.g. a framebuffer coordinate to [0,0x10000)
static inline unsigned hash2(GPoint p) {
   return hash1(hash1(p.x * 7393u) * hash1(p.y * 17573u) + hash1(1019u * p.x * p.y));
}

#endif // !UTIL_H
