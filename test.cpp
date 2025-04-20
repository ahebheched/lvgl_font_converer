//
// Created by 14135 on 25-4-19.
//

#include <cstdio>
#include <iostream>

#include "font3.h"

using namespace std;

int a;

FILE *fp = fopen("font_.h", "w+");

int main() {
    conver_lvglfont cl(&font_dsc, sizeof(glyph_dsc)/sizeof(glyph_dsc[0]));
    char16_t ch = u'你';
    cout << "ch: " << (int)ch << endl;
    // cout << sizeof(font_dsc.glyph_dsc) << endl;
    // cout << font_dsc.glyph_dsc[10].bitmap_index << endl;
    // printf("Hello World\n");
    // fprintf(fp, "hello world\n");
    // fclose(fp);
    // cin >> a;
}