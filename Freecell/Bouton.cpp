#include <utility>
#include <iostream>

#include "pch.h"
#include "Bouton.h"
#include "stb_implement.h"

using namespace cimg_library;

Bouton::Bouton(std::string nom, int posX, int posY, const char *fileName) : nom_(std::move(nom)), positionX_(posX),
                                                                            positionY_(posY) {
    charger(image_, fileName, Channels::RGBA);
    tailleX_ = image_.width();
    tailleY_ = image_.height();
}

void Bouton::dessinerBouton(cimg_library::CImg<unsigned char> *fond) {
    CImg<unsigned char> render(image_.width(), image_.height(), couleurFond[0], couleurFond[1], couleurFond[2]);
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
    fond->draw_image(this->getpositionX(), this->getpositionY(), render);
}

bool Bouton::estCliquee(int mx, int my) {
    return mx >= getpositionX() && mx <= getpositionX() + getTailleX() && my >= getpositionY() &&
           my <= getpositionY() + getTailleY();
}

Bouton::~Bouton() {

}


