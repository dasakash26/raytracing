#include "color.h"
#include <iostream>

using namespace std;

int main() {
  int img_w = 256, img_h = 256;

  // Render
  // P3 means ascii
  // then img w-h
  // 255 is max color val
  cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

  for (int j = 0; j < img_h; ++j) {
    clog << "\r>> Scanlines remaining: " << img_h - j - 1 << ' ' << flush;
    for (int i = 0; i < img_w; ++i) {
      auto r = double(i) / (img_w - 1);
      auto g = double(j) / (img_h - 1);
      auto b = 0;

      Color pixel(r, g, b);
      write_color(cout, pixel);
    }
  }

  clog << "\rDone.                       \n";

  return 0;
}
