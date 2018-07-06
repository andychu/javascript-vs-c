// https://rosettacode.org/wiki/Mandelbrot_set#JavaScript
// Ported to C.
#include <stdio.h>
#include <math.h>

int mandelIter(double cx, double cy, int maxIter) {
  double x = 0.0;
  double y = 0.0;
  double xx = 0;
  double yy = 0;
  double xy = 0;
 
  int i = maxIter;
  while (i-- && xx + yy <= 4) {
    xy = x * y;
    xx = x * x;
    yy = y * y;
    x = xx - yy + cx;
    y = xy + xy + cy;
  }
  return maxIter - i;
}
 
void mandelbrot(char* pix, int width, int height,
                double xmin, double xmax,
                double ymin, double ymax, int iterations) {
  for (int ix = 0; ix < width; ++ix) {
    for (int iy = 0; iy < height; ++iy) {
      double x = xmin + (xmax - xmin) * ix / (width - 1);
      double y = ymin + (ymax - ymin) * iy / (height - 1);
      int i = mandelIter(x, y, iterations);
      int ppos = 4 * (width * iy + ix);
 
      if (i > iterations) {
        pix[ppos] = 0;
        pix[ppos + 1] = 0;
        pix[ppos + 2] = 0;
      } else {
        double c = 3 * log((double)i) / log((double)(iterations - 1.0));
 
        if (c < 1.0) {
          pix[ppos] = 255 * c;
          pix[ppos + 1] = 0;
          pix[ppos + 2] = 0;
        }
        else if ( c < 2.0 ) {
          pix[ppos] = 255;
          pix[ppos + 1] = 255 * (c - 1);
          pix[ppos + 2] = 0;
        } else {
          pix[ppos] = 255;
          pix[ppos + 1] = 255;
          pix[ppos + 2] = 255 * (c - 2);
        }
      }
      pix[ppos + 3] = 255;
    }
  }
}
 
int main() {
  const int width = 900;
  const int height = 600;

  //char pix[width * height];  // BUG
  char pix[width * height * 4];
  mandelbrot(pix, width, height, -0.75, 0.25, 0.20, 0.75, 1000);

  printf("Rendering Mandelbrot ...");
  FILE* fp = fopen("out.ppm", "wb"); /* b -  binary mode */

  fprintf(fp,"P6\n # \n %d\n %d\n 255\n", width,height);

  for (int iy = 0; iy < height; ++iy) {
    for (int ix = 0; ix < width; ++ix) {
      int ppos = 4 * (width * iy + ix);
      fwrite(&pix[ppos], 1, 3, fp);
    }
  }
  fclose(fp);
}
