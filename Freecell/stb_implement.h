#ifndef FREECELL_STB_IMPLEMENT_H
#define FREECELL_STB_IMPLEMENT_H

#include "CImg.h"

using namespace cimg_library;

enum class Channels {
    RGB = 3, RGBA = 4
};

bool charger(CImg<unsigned char> &image, const char *chemin, Channels c);

#endif //FREECELL_STB_IMPLEMENT_H
