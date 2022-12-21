#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
  int w;
  int h;
  unsigned char *data;
} Image;

Image *createImage(int w, int h);
void imageSetPixel(Image *im, int x, int y, unsigned char color);
void imageSaveAsGif(Image *im, const char *filename, const char *colormapfile);

#endif
