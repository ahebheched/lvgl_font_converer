//
// Created by 14135 on 25-4-18.
//
#pragma once
#include <stdint.h>
#include <map>

using namespace std;

#define LV_ATTRIBUTE_LARGE_CONST
#define LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY 0
#define LV_FONT_FMT_TXT_CMAP_SPARSE_TINY 1

typedef struct lvgl_font {
    uint16_t bitmap_index;
    uint16_t adv_w;
    uint16_t box_w;
    uint16_t box_h;
    int16_t ofs_x;
    int16_t ofs_y;
} lv_font_fmt_txt_glyph_dsc_t;

typedef struct lv_font_cmap_t {
    uint16_t range_start;
    uint16_t range_length;
    uint16_t glyph_id_start;
    const uint16_t *unicode_list;
    const uint8_t *glyph_id_ofs_list;
    uint16_t list_length;
    uint8_t type;
} lv_font_fmt_txt_cmap_t;

typedef struct lv_font_dsc_t {
    const uint8_t *glyph_bitmap;
    const lv_font_fmt_txt_glyph_dsc_t *glyph_dsc;
    const lv_font_fmt_txt_cmap_t *cmaps;
    void *kern_dsc;
    uint8_t kern_scale;
    uint8_t cmap_num;
    uint8_t bpp;
    uint8_t kern_classes;
    uint8_t bitmap_format;
} lv_font_fmt_txt_dsc_t;

typedef struct eink_font_t {
    uint8_t line_height;
    uint8_t line_width;
    uint8_t *glyph_bitmap;
} eink_font_t;

enum {
    EINK_FONT_ROTATE_0 = 0,
    EINK_FONT_ROTATE_90,
    EINK_FONT_ROTATE_180,
    EINK_FONT_ROTATE_270,
};

enum {
    EINK_FONT_FLIP_X = 0,
    EINK_FONT_FLIP_Y,
};

class conver_lvglfont {
public:
    conver_lvglfont(const lv_font_fmt_txt_dsc_t *glyph_dsc, uint16_t font_mum);

    static void print_font(const eink_font_t &font);
    static void print_eink_font(const map<uint16_t, eink_font_t> &eink_font);
    void print_eink_font_file(const map<uint16_t, eink_font_t> &eink_font);

private:
    static void format_font_size(int *w, int *h);
    eink_font_t format_font(const uint8_t *glyph_bitmap, int w, int h, int off_x, int off_y);
    void bitmap_to_draw(const uint8_t *bitmap, int w, int h);
    void bitmap_to_draw(const uint8_t *bitmap, int w, int h, int off_x, int off_y);
    void draw_to_bitmap(uint8_t *bitmap, int w, int h) const;
    void print_draw(int w, int h) const;
    void rotate_font(eink_font_t *font, int angle);
    void flip_font(eink_font_t *font, int style);
    void reverse_font(eink_font_t *font);
    map<uint16_t, eink_font_t> eink_font;
    uint16_t font_num;
    uint16_t cmap_num;
    uint8_t draw[200][200];
    uint8_t draw_[200][200];

    // char font_name[40];
};

