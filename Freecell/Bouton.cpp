#include <utility>
#include <iostream>

#include "pch.h"
#include "Bouton.h"
#include "stb_implement.h"

using namespace cimg_library;

Bouton::Bouton(std::string nom, const char *fileName, float factorScale) : nom_(std::move(nom)) {
    chemin = fileName;
    charger(image_, fileName, Channels::RGBA);
    tailleOriginaleX_ = image_.width() * factorScale;
    tailleOriginaleY_ = image_.height() * factorScale;
    tailleX_ = tailleOriginaleX_;
    tailleY_ = tailleOriginaleY_;
    image_.resize(tailleX_, tailleY_);

}

void Bouton::dessinerBouton(cimg_library::CImg<unsigned char> *fond, int posX, int posY) {
    positionX_ = posX;
    positionY_ = posY;
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
    fond->draw_image(positionX_, positionY_, render);
}

bool Bouton::estCliquee(int mx, int my) {
    return mx >= getpositionX() && mx <= getpositionX() + getTailleX() && my >= getpositionY() &&
           my <= getpositionY() + getTailleY();
}

Bouton::~Bouton() {

}

void Bouton::reload(float coeffX, float coeffY) {
    charger(image_, chemin, Channels::RGBA);
    tailleX_ = tailleOriginaleX_ * coeffX;
    tailleY_ = tailleOriginaleY_ * coeffY;
    image_.resize(tailleX_, tailleY_);
}



