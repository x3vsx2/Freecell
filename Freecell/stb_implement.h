/*!
 *  @file std_implement.h
 *  @brief Fichier contenant la déclaration de la fonction charger
 *  Cette fonction permet de lire des png et de garder la transparance.
 *  @date 07/05/2019
 *  @authors Julien Vernay (julien.vernay@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_STB_IMPLEMENT_H
#define FREECELL_STB_IMPLEMENT_H

#include "CImg.h"

using namespace cimg_library;

enum class Channels {
    RGB = 3, RGBA = 4
};

/*!
 *  Charge une image png. Utilise la bibliothèque std_image en réordonnant les cannaux par rapport avec cimg
 *  @param image Cimg dans laquelle va être chargé le png
 *  @param chemin du png
 *  @param c le nombre de channels de l'image. 3 ou 4.
 */
bool charger(CImg<unsigned char> &image, const char *chemin, Channels c);

#endif //FREECELL_STB_IMPLEMENT_H