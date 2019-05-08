/*!
 *  @file Bouton.cpp
 *  @brief Fichier contenant la déclaration de la classe Bouton.
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#include "pch.h"
#include "Bouton.h"
#include "stb_implement.h"

using namespace cimg_library;

Bouton::Bouton(std::string nom, const char *fileName, float factorScale) : nom_(std::move(nom)), positionX_(0),
                                                                           positionY_(0) {
    chemin_ = fileName;
    charger(image_, fileName, Channels::RGBA);
    tailleOriginaleX_ = int(image_.width() * factorScale);
    tailleOriginaleY_ = int(image_.height() * factorScale);
    tailleX_ = tailleOriginaleX_;
    tailleY_ = tailleOriginaleY_;
    image_.resize(tailleX_, tailleY_);

}

Bouton::~Bouton() = default;

void Bouton::dessinerBouton(cimg_library::CImg<unsigned char> *visu, int posX, int posY) {
    setPosX(posX);
    setPosY(posY);
    CImg<unsigned char> render(tailleX_, tailleY_, couleurFond[0], couleurFond[1], couleurFond[2]);
    cimg_forXY(render, x, y)
    {
        //Rouge
        render(x, y, 0, 0) = couleurFond[0];
        //Vert
        render(x, y, 0, 1) = couleurFond[1];
        //Bleu
        render(x, y, 0, 2) = couleurFond[2];

    }
    render.draw_image(0, 0, 0, 0, image_, image_.get_channel(3), 1, 255);
    visu->draw_image(getPosX(), getPosY(), render);
}

bool Bouton::estCliquee(int mx, int my) {
    return mx >= getPosX() && mx <= getPosX() + getTailleX() && my >= getPosY() &&
           my <= getPosY() + getTailleY();
}

void Bouton::reload(float coeffX, float coeffY) {
    charger(image_, chemin_, Channels::RGBA);
    setTailleX(tailleOriginaleX_ * coeffX);
    setTailleY(tailleOriginaleY_ * coeffY);
    image_.resize(tailleX_, tailleY_);
}



