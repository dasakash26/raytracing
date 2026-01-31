#include <iostream>
using namespace std;

#define CLAMP 255.999

int main() {
  // Image
  int img_w = 256, img_h = 256;

  // Render

  // P3 means ascii
  // then img w-h
  // 255 is max color val
  cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

  // rgb triplets: w x h
  for (int j = 0; j < img_h; ++j) {
    for (int i = 0; i < img_w; ++i) {
      clog << "\rScanlines remaining: " << img_h - j - 1 << ' ' << flush;
      auto r = double(i) / (img_w - 1);
      auto g = double(j) / (img_h - 1);
      auto b = 0;

      int ir = int(CLAMP * r);
      int ig = int(CLAMP * g);
      int ib = int(CLAMP * b);

      cout << ir << " " << ig << " " << ib << '\n';
    }
  }
  clog << "\rDone.                       \n";

  return 0;
}
