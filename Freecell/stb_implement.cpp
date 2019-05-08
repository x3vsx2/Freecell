/*!
 *  @file std_implement.cpp
 *  @brief Fichier contenant la déclaration de la fonction charger
 *  Cette fonction permet de lire des png et de garder la transparance.
 *  @date 07/05/2019
 *  @authors Julien Vernay (julien.vernay@etu.univ-st-etienne.fr)
*/
#include "pch.h"
#include "stb_implement.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

bool charger(CImg<unsigned char> &image, const char *chemin, Channels c) {
    int width, height;
    int nb_channels = static_cast<int>(c);
    unsigned char *read_data = stbi_load(chemin, &width, &height, nullptr, nb_channels);
    if (!read_data)
        return false;
    image.assign(width, height, 1, nb_channels);
    unsigned char *img_data = image.data();

    for (unsigned int x = 0; x < width; ++x)
        for (unsigned int y = 0; y < height; ++y)
            for (unsigned int c = 0; c < nb_channels; ++c)
                img_data[x + width * (y + height * c)] = read_data[c + nb_channels * (x + width * y)];

    stbi_image_free(read_data);
    return true;
}