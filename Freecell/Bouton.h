/*!
 *  @file Bouton.h
 *  @brief Fichier contenant la déclaration de la classe Bouton.
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_BOUTON_H
#define FREECELL_BOUTON_H

#ifdef _WIN32 //Si le systeme d'exploitation est windows
#define CLEAR "cls"
#else //Si c'est un autre OS
#define CLEAR "clear"
#endif

#include<string>
#include"CImg.h"
#include"Couleurs.h"

/*!
 * @class Classe Bouton.
 * Cette classe représente permet d'utiliser des boutons.
 * Elle est utilisée dans la classe Fenetre Principale.
 */
class Bouton {
public:
    /*!
     *  Constructeur de Bouton.
     *  @param nom nom du bouton
     *  @param fileName chemin vers l'image du bouton
     *  @param factorScale facteur d'échelle du bouton
     */
    Bouton(std::string nom, const char *fileName, float factorScale = 1);

    /*!
     *  Destructuer de Bouton.
     */
    ~Bouton();

    /*!
     *  Retoune la taille X du bouton
     *  @return la taille X du bouton
     */
    int getTailleX() { return tailleX_; };

    /*!
     *  Retoune la taille Y du bouton
     *  @return la taille Y du bouton
     */
    int getTailleY() { return tailleY_; };

    /*!
     *  Retoune la position X du bouton
     *  @return la position X du bouton
     */
    int getPosX() const { return positionX_; };

    /*!
     *  Retoune la position Y du bouton
     *  @return la position Y du bouton
     */
    int getPosY() const { return positionY_; };

    /*!
     *  Change la taille X du bouton
     *  @param tX la taille X du bouton
     */
    void setTailleX(int tX) { tailleX_ = tX; }

    /*!
     *  Change la taille Y du bouton
     *  @param tY la taille Y du bouton
     */
    void setTailleY(int tY) { tailleY_ = tY; }

    /*!
     *  Change la position X du bouton
     *  @param px position X du bouton
     */
    void setPosX(int pX) { positionX_ = pX; }

    /*!
     *  Change la position Y du bouton
     *  @param py position Y du bouton
     */
    void setPosY(int pY) { positionY_ = pY; }

    /*!
     *  Dessine le bouton sur le fond passé en paramètre selon ses attributs.
     *  @param fond plan sur lequel est dessiné le bouton
     *  @param posX position horizontale du bouton
     *  @param posY position verticale du bouton
     */
    void dessinerBouton(cimg_library::CImg<unsigned char> *fond, int posX, int posY);

    /*!
     *  Permet de savoir si la souris est sur le bouton
     *  @param mx position horizontale de la souris
     *  @param my position verticale de la souris
     *  @return true si la souris est sur le bouton, false sinon
     */
    bool estCliquee(int mx, int my);

    /*!
     *  Recharge une image selon les coefficients.
     *  @param coeffX coefficient de redimensionnement de la largeur
     *  @param coeffY coefficient de redimensionnement de la hauteur
     */
    void reload(float coeffX, float coeffY);

private:
    int positionX_; /*!< Position Horizontale*/
    int positionY_; /*!< Position Verticale*/
    int tailleOriginaleX_; /*!< Largeur originale*/
    int tailleOriginaleY_; /*!< Hauteur originale*/
    int tailleX_; /*!< Largeur*/
    int tailleY_; /*!< Hauteur*/
    cimg_library::CImg<unsigned char> image_; /*!< Image représentant la carte*/
    std::string nom_; /*!< Nom*/
    const char *chemin_; /*!< Chemin vers l'image de la carte*/
};

#endif //FREECELL_BOUTON_H