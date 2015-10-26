#include <pebble.h>

#include "glyphs.h"
#include "fb.h"
#include "util.h"
#include "boxy.h"

#if 1
#undef APP_LOG
#define APP_LOG(...)
#define START_TIME_MEASURE() {
#define END_TIME_MEASURE(x) }
#define DBG(...)
#else
static unsigned int get_time(void) {
   time_t s;
   uint16_t ms;
   time_ms(&s, &ms);
   return (s & 0xfffff) * 1000 + ms;
}

#define DBG(...) APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__)

#define START_TIME_MEASURE() \
   {                         \
   unsigned tm_0 = get_time()
#define END_TIME_MEASURE(x)              \
   unsigned tm_1 = get_time();           \
   DBG("%s: took %dms", x, tm_1 - tm_0); \
   }
#endif

struct App {
   struct tm t;
   Window *w;
   uint8_t fg;
   uint8_t bg;
   uint8_t day_or_month;
};

struct App *g;

static int getDrawStringLength(char *s, int size) {
   int x = 0;
   for (int i = 0; s[i]; i++)
      x += glyphSize(char2index(s[i]), size) + size + 1;
   return x;
}

static int drawString(GPoint p, char *s, int size, uint8_t c) {
   int x = 0;
   for (int i = 0; s[i]; i++)
      x +=
         drawGlyph(GPoint(p.x + x, p.y), char2index(s[i]), size, c) + size + 1;
   return x;
}

static int drawNumber(GPoint p, unsigned num, int s, uint8_t c) {
   char buf[10];
   snprintf(buf, sizeof(buf), "%u", num);
   return drawString(p, buf, s, c);
}

static void draw(void) {
   START_TIME_MEASURE();

   uint8_t bg = g->bg;
   uint8_t fg = g->fg;

   fbClear(bg);

   static char *weekday[] = {"sunday",   "monday", "tuesday", "wednesday",
                             "thursday", "friday", "saturday"};

   static char *month[] = {"jan", "feb", "mar", "apr", "may", "jun",
                           "jul", "aug", "sep", "oct", "nov", "dec"};

   char buf[32];
   GPoint p;
   int len;

   len = getDrawStringLength(weekday[g->t.tm_wday], 2);
   p = GPoint((144 - (len - 5)) / 2, 7);
   drawString(p, weekday[g->t.tm_wday], 2, fg);

   snprintf(buf, sizeof(buf), "%02d\t%02d", g->t.tm_hour, g->t.tm_min);
   len = getDrawStringLength(buf, 5);
   p = GPoint((144 - (len - 5)) / 2, (168 - 5 * 5) / 2);
   drawString(p, buf, 5, fg);

   snprintf(buf, sizeof(buf), "%d\v%s", g->t.tm_mday, month[g->t.tm_mon]);
   len = getDrawStringLength(buf, 2);
   p = GPoint((144 - (len - 5)) / 2, 168 - 7 - 5 * 2);
   drawString(p, buf, 2, fg);

   END_TIME_MEASURE("drawing");
}

static void update(Layer *layer, GContext *ctx) {
   GBitmap *bmp = graphics_capture_frame_buffer(ctx);
   fbSet(gbitmap_get_data(bmp));

   draw();

   graphics_release_frame_buffer(ctx, bmp);
   fbSet(NULL);
}

static void tick(struct tm *tick_time, TimeUnits units_changed) {
   g->t = *tick_time;
   layer_mark_dirty(window_get_root_layer(g->w));
   DBG("watch tick %02d:%02d:%02d", tick_time->tm_hour, tick_time->tm_min,
       tick_time->tm_sec);
}

static void window_load(Window *w) {
   layer_set_update_proc(window_get_root_layer(w), update);
}

static void window_unload(Window *w) {}

static void init_time(struct App *a) {
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
   a->t = *tm;
}

static void set_colors(uint8_t bg, uint8_t fg) {
   g->fg = fg;
   g->bg = bg;
   DBG("bg=%02x, fg=%02x", (unsigned)bg, (unsigned)fg);
   if (g->w) {
      layer_mark_dirty(window_get_root_layer(g->w));
   }
   persist_write_int(0, ((int)g->fg << 8) | g->bg);
}

static void set_colors_rgb(int bg, int fg) {
   set_colors(GColorFromRGB(bg >> 16, (bg & 0xff00) >> 8, bg & 0xff).argb,
              GColorFromRGB(fg >> 16, (fg & 0xff00) >> 8, fg & 0xff).argb);
}

static void inbox_received_handler(DictionaryIterator *iter, void *data) {
   Tuple *tfg = dict_find(iter, KEY_FG);
   Tuple *tbg = dict_find(iter, KEY_BG);
   if (tfg && tbg) {
      int fg = tfg->value->uint32;
      int bg = tbg->value->uint32;
      set_colors_rgb(bg, fg);
   }
}

static void init_config(struct App *a) {
   int bg = persist_read_int(0);
   bg &= 0xffff;
   int fg = bg >> 8;
   bg &= 0xff;
   if (fg == bg) {
      bg = 0xf0;  // red
      fg = 0xff;  // white
   }
   set_colors(bg, fg);
   app_message_register_inbox_received(inbox_received_handler);
   app_message_open(app_message_inbox_size_maximum(),
                    app_message_outbox_size_maximum());
}

static void init(struct App *a) {
   g = a;
   a->w = window_create();
   init_time(a);
   tick_timer_service_subscribe(MINUTE_UNIT, tick);
   window_set_user_data(a->w, a);
   window_set_window_handlers(a->w,
                              (WindowHandlers){
                                 .load = window_load, .unload = window_unload,
                              });
   init_config(a);
   window_stack_push(a->w, false);
}

static void fini(struct App *a) {
   tick_timer_service_unsubscribe();
   window_destroy(a->w);
}

int main(void) {
   struct App a;
   memset(&a, 0, sizeof(a));
   init(&a);
   app_event_loop();
   fini(&a);
   return 0;
}
