//
// Created by 14135 on 25-4-19.
//

#include <cstdio>
#include <iostream>

#include "font.h"

using namespace std;

int a;

int main() {
    conver_lvglfont cl(&font_dsc, sizeof(glyph_dsc)/sizeof(glyph_dsc[0]));
    cout << sizeof(font_dsc.glyph_dsc) << endl;
    cout << font_dsc.glyph_dsc[10].bitmap_index << endl;
    printf("Hello World\n");
    cin >> a;
}