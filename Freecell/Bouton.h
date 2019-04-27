#ifndef FREECELL_BOUTON_H
#define FREECELL_BOUTON_H

#include<string>
#include "CImg.h"
#include "Couleurs.h"

class Bouton {
public:
    Bouton(std::string nom, int posX, int posY, const char *fileName);

    ~Bouton();

    int getTailleX() { return tailleX_; };

    int getTailleY() { return tailleY_; };

    int getpositionX() { return positionX_; };

    int getpositionY() { return positionY_; };

    void setTailleX(int tX) { tailleX_ = tX; }

    void setTailleY(int tY) { tailleY_ = tY; }

    void setpositionX(int pX) { positionX_ = pX; }

    void setpositionY(int pY) { positionY_ = pY; }

    void dessinerBouton(cimg_library::CImg<unsigned char> *fond);

    bool estCliquee(int mx, int my);

    cimg_library::CImg<unsigned char> getImg() { return image_; };

private:
    int positionX_;
    int positionY_;
    int tailleX_;
    int tailleY_;
    cimg_library::CImg<unsigned char> image_;
    std::string nom_;
};


#endif //FREECELL_BOUTON_H
