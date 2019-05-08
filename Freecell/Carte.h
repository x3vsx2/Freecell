/*!
 *  @file Carte.h
 *  @brief Fichier contenant la déclaration de la classe Carte.
 *  @date 07/05/2019
 *  @authors Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr),
 *  Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_CARTE_H
#define FREECELL_CARTE_H

#include "pch.h"
#include "CImg.h"
#include "PileCarte.h"
#include <iostream>

class PileCarte;

//TODO commentaire
typedef enum {
    Coeur, Pique, Carreau, Trefle
} TypeCouleur;
//TODO commentaire
typedef enum {
    As, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi
} TypeHauteur;

using namespace cimg_library;

/*!
 * @class Classe Carte.
 * Cette classe représente une carte de jeu. Elle contient des méthodes pour la dessiner, changer ses attributs...
 * Elle est un agrégat de la classe PileCarte.
 */
class Carte {
public:
    /*!
     *  Constructeur de Carte.
     *  @param idCarte identifiant de la carte
     *  @param Couleur couleur de la carte
     *  @param Hauteur hauteur de la carte
     *  @param fileName chemin vers l'image de la carte
     *  @param factorScale facteur d'échelle de la carte
     *  @param coeffX coefficient longueur image, prends 1 lors d'une première partie sans redimensionnement
     *  @param coeffY coefficient hauteur image, prends 1 lors d'une première partie sans redimensionnement
     */
    Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur,
          const char *fileName,
          PileCarte *pileAppartenance, float factorScale, float coeffX, float coeffY);

    /*!
     *  Constructeur par défaut de pile Carte
     */
    Carte();

    /*!
     *  Destructeur de Carte. Fais pointé pileAppartenance_ vers nullptr.
     *  Les destructions des images est implicite et réalisé par CImg
     */
    ~Carte();

    /*!
     *  Dessine la carte sur le plan souhaité selon sa position.
     *  @param visu plan sur lequel est dessinée la carte
     */
    void dessinerCarte(cimg_library::CImg<unsigned char> *visu);

    /*!
     *  Retoune l'identifiant de la carte
     *  @return identifiant de la carte
     */
    int getIdentifiant();

    /*!
     *  Retoune la position X de la carte
     *  @return la position X de la carte
     */
    int getPosX() const { return positionX_; };

    /*!
     *  Retoune la position Y de la carte
     *  @return la position Y de la carte
     */
    int getPosY() const { return positionY_; };

    /*!
     *  Retoune la taille X de la carte
     *  @return la taille X de la carte
     */
    int getTailleX() const { return tailleX_; };

    /*!
     *  Retoune la taille Y de la carte
     *  @return la taille Y de la carte
     */
    int getTailleY() const { return tailleY_; };

    /*!
     *  Change la taille X de la carte
     *  @param newTailleX la taille X de la carte
     */
    void setTailleX(int newTailleX) { tailleX_ = newTailleX; };

    /*!
     *  Change la taille Y de la carte
     *  @param newTailleY la taille Y de la carte
     */
    void setTailleY(int newTailleY) { tailleY_ = newTailleY; };

    /*!
     *  Change la position X de la carte
     *  @param posX position X de la carte
     */
    void setPosX(int posX) { positionX_ = posX; };

    /*!
     *  Change la position Y de la carte
     *  @param posY position Y de la carte
     */
    void setPosY(int posY) { positionY_ = posY; };

    /*!
     *  Retoune la couleur de la carte
     *  @return la couleur de la carte
     */
    TypeCouleur getCouleur() { return Couleur_; }

    /*!
     *  Retoune la hauteur de la carte
     *  @return la hauteur de la carte
     */
    TypeHauteur getHauteur() { return Hauteur_; }

    /*!
     *  Change la pile d'appartenance d'une carte
     *  @param pile pointeur vers la nouvelle pile d'appartenance
     */
    void setPileAppartenance(PileCarte *pile) { pileAppartenance_ = pile; };

    /*!
     *  Recharge une image selon les coefficients.
     *  @param coeffX coefficient de redimensionnement de la largeur
     *  @param coeffY coefficient de redimensionnement de la hauteur
     */
    void reload(float coeffX, float coeffY);

private:
    int idCarte_ = 0; /*!< Identifiant*/
    TypeCouleur Couleur_{}; /*!< Type Couleur*/
    TypeHauteur Hauteur_{}; /*!< Type hauteur*/
    int positionX_ = 0; /*!< Position Horizontale*/
    int positionY_ = 0; /*!< Position Verticale*/
    int OriginalTailleX_ = 0; /*!< Largeur originale*/
    int OriginalTailleY_ = 0; /*!< Hauteur originale*/
    int tailleX_ = 0; /*!< Largeur*/
    int tailleY_ = 0; /*!< Hauteur*/
    CImg<unsigned char> image_; /*!< Image représentant la carte*/
    PileCarte *pileAppartenance_{};
    const char *chemin_{}; /*!< Chemin vers l'image de la carte*/
};

#endif //FREECELL_CARTE_H