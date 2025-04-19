//
// Created by 14135 on 25-4-18.
//

#include "conver_lvglfont.h"

#include <cstdio>
#include <font.h>
#include <iostream>
#include <string.h>

using namespace std;

conver_lvglfont::conver_lvglfont(const lv_font_fmt_txt_dsc_t *glyph_dsc, uint16_t font_mum): draw{0}, draw_{0} {
    // this->font_num = sizeof(glyph_dsc->glyph_dsc) / sizeof(lv_font_fmt_txt_glyph_dsc_t);
    // this->cmap_num = sizeof(glyph_dsc->cmaps) / sizeof(lv_font_fmt_txt_cmap_t);
    this->font_num = font_mum;
    this->cmap_num = glyph_dsc->cmap_num;

    int w_ = 0, h_ = 0;

    cout << "font_num: " << this->font_num << endl;
    for (int j = 0; j < cmap_num; j++) {
        if (glyph_dsc->cmaps[j].type == LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY) {

        }
    }

    for (int i = 0; i < this->font_num; i++) {
        if (glyph_dsc->glyph_dsc[i].adv_w > 0) {
            w_ = glyph_dsc->glyph_dsc[i].box_w;
            h_ = glyph_dsc->glyph_dsc[i].box_h;
            // format_font_size(&w_, &h_);
            eink_font_t font = (format_font(glyph_dsc->glyph_bitmap + glyph_dsc->glyph_dsc[i].bitmap_index, w_, h_));

            if ()
            print_font(font);

            rotate_font(&font, EINK_FONT_ROTATE_270);

            print_font(font);

            flip_font(&font, EINK_FONT_FLIP_X);
            print_font(font);

            reverse_font(&font);
            print_font(font);

            // this->eink_font.insert(pair<uint16_t, eink_font_t>(glyph_dsc->glyph_dsc[i].unicode_letter, format_font(glyph_dsc->glyph_bitmap + glyph_dsc->glyph_dsc[i].bitmap_index, w_, h_)));
        }
    }
}

void conver_lvglfont::format_font_size(int *w, int *h) {
    *w = 8 * (*w / 8 + (*w % 8 != 0 ? 1 : 0));
    *h = 8 * (*h / 8 + (*h % 8 != 0 ? 1 : 0));
}

eink_font_t conver_lvglfont::format_font(const uint8_t *glyph_bitmap, const int w, const int h) {
    int w_ = w, h_ = h;
    eink_font_t font;
    format_font_size(&w_, &h_);
    font.line_width = w_;
    font.line_height = h_;
    uint8_t *bitmap = new uint8_t[w_ * h_ / 8];
    memset(bitmap, 0, w_ * h_ / 8);
    font.glyph_bitmap = bitmap;

    bitmap_to_draw(glyph_bitmap, w, h);
    draw_to_bitmap(bitmap, w, h);

    return font;
}

void conver_lvglfont::bitmap_to_draw(const uint8_t *bitmap, const int w, const int h) {
    memset(this->draw, 0, sizeof(this->draw));
    // for (int i = 0; i < 200; i++) {
    //     for (int j = 0; j < 200; j++) {
    //         this->draw[i][j] = 0;
    //     }
    // }
    int w_ = w, h_ = h;
    format_font_size(&w_, &h_);
    int height = 0, width = 0;
    int add_pixcel = 0;
    cout << "kong" << (w_ - w) / 2 << " " << (h_ - h) / 2 << endl;
    for (int i = 0; i < h * w / 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (add_pixcel <= w * h) {
                this -> draw[width + (w_ - w) / 2][height + (h_ - h) / 2] = ((bitmap[i] >> (7 - j)) & 0x01);
            }
            width++;
            if (width >= w) {
                width = 0;
                height++;
            }
            add_pixcel++;
        }
    }

    // print_draw(w_, h_);
}

void conver_lvglfont::draw_to_bitmap(uint8_t *bitmap, const int w, const int h) const {
    int w_ = w, h_ = h;
    format_font_size(&w_, &h_);
    int a = 0;
    for (int i = 0; i < h_; i++) {
        for (int j = 0; j < w_; j++) {
            bitmap[a / 8] |= draw[j][i] << (7 - (a % 8));
            a++;
        }
    }
}

void conver_lvglfont::print_draw(const int w, const int h) const {
    printf("%3d:", 0);
    for (int i = 0; i < w; i++) {
        printf("%3d", i + 1);
    }
    cout << endl;
    for (int i = 0; i < h; i++) {
        printf("%3d:", i + 1);
        for (int j = 0; j < w; j++) {
            if (draw[j][i] == 1) {
                cout << "###";
            } else {
                cout << "___";
            }
        }
        cout << endl;
    }
    cout << endl << endl << endl << endl;
}

void conver_lvglfont::print_font(const eink_font_t &font) const {
    // printf("%3d:", 0);
    for (int i = 0; i < font.line_width; i++) {
        printf("%3d", i + 1);
    }
    cout << endl;
    int w = 0;
    for (int i = 0; i < font.line_height * font.line_width / 8; i++) {
        for (int j = 0; j < 8; j++) {
            w++;
            if (font.glyph_bitmap[i] >> (7 - j) & 1) {
                cout << "###";
            } else {
                cout << "___";
            }
            if (w >= font.line_width) {
                w = 0;
                cout << endl;
            }
        }
        // cout << endl;
    }
    cout << endl << endl << endl << endl;
}

void conver_lvglfont::rotate_font(eink_font_t *font, int angle) {
    int h = font->line_height;
    int w = font->line_width;
    int w_ = w, h_ = h;
    bitmap_to_draw(font->glyph_bitmap, w, h);
    memset(this->draw_, 0, sizeof(this->draw_));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (angle) {
                case EINK_FONT_ROTATE_90:
                    draw_[i][j] = draw[w - j - 1][i];
                    w_ = font->line_height;
                    h_ = font->line_width;
                break;
                case EINK_FONT_ROTATE_180:
                    draw_[w - j - 1][h - i - 1] = draw[j][i];
                break;
                case EINK_FONT_ROTATE_270:
                    draw_[i][j] = draw[j][h - i - 1];
                    w_ = font->line_height;
                    h_ = font->line_width;
                break;
                default:
                    draw_[i][j] = draw[i][j];
            }
        }
    }
    memcpy(this->draw, this->draw_, sizeof(this->draw_));
    memset(font->glyph_bitmap, 0, w * h / 8);
    draw_to_bitmap(font->glyph_bitmap, w_, h_);
    font->line_width = w_;
    font->line_height = h_;
}

void conver_lvglfont::flip_font(eink_font_t *font, int style) {
    const int h = font->line_height;
    const int w = font->line_width;
    memset(this->draw_, 0, sizeof(this->draw_));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (style == EINK_FONT_FLIP_X) {
                draw_[j][i] = draw[j][h - i - 1];
            }
            else {
                draw_[j][i] = draw[w - j - 1][i];
            }
        }
    }
    memcpy(this->draw, this->draw_, sizeof(this->draw_));
    memset(font->glyph_bitmap, 0, w * h / 8);
    draw_to_bitmap(font->glyph_bitmap, w, h);
    font->line_width = w;
    font->line_height = h;
}

void conver_lvglfont::reverse_font(eink_font_t *font) {
    const int h = font->line_height;
    const int w = font->line_width;
    for (int i = 0; i < h * w / 8; i++) {
        font->glyph_bitmap[i] = ~font->glyph_bitmap[i];
    }
}

