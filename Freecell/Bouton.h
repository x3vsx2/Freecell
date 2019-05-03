#ifndef FREECELL_BOUTON_H
#define FREECELL_BOUTON_H

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#include<string>
#include"CImg.h"
#include"Couleurs.h"

class Bouton {
public:
    Bouton(std::string nom, const char *fileName, float factorScale = 1);

    ~Bouton();

    int getTailleX() { return tailleX_; };

    int getTailleY() { return tailleY_; };

    int getpositionX() const { return positionX_; };

    int getpositionY() const { return positionY_; };

    void setTailleX(int tX) { tailleX_ = tX; }

    void setTailleY(int tY) { tailleY_ = tY; }

    void setpositionX(int pX) { positionX_ = pX; }

    void setpositionY(int pY) { positionY_ = pY; }

    void dessinerBouton(cimg_library::CImg<unsigned char> *fond, int posX, int posY);

    bool estCliquee(int mx, int my);

    void reload(float coeffX, float coeffY);

    cimg_library::CImg<unsigned char> getImg() { return image_; };

private:
    int positionX_;
    int positionY_;
    int tailleOriginaleX_;
    int tailleOriginaleY_;
    int tailleX_;
    int tailleY_;
    cimg_library::CImg<unsigned char> image_;
    std::string nom_;
    const char *chemin;
};


#endif //FREECELL_BOUTON_H
