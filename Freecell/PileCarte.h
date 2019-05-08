/*!
 *  @file PileCarte.h
 *  @brief Fichier contenant la déclaration de la classe PileCarte.
 *  @date 07/05/2019
 *  @authors Jean-Baptiste JACQUET (jean-Baptiste.jacquet@etu.univ-st-etienne.fr),
 *  Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_PILECARTE_H
#define FREECELL_PILECARTE_H

#include <vector>
#include <fstream>
#include "pch.h"
#include "Carte.h"

using namespace cimg_library;

//TODO commentaire
typedef enum {
    // il est strictement interdit de changer l'odre des types
            unknown,
    melange,
    jeu1,
    jeu2,
    jeu3,
    jeu4,
    jeu5,
    jeu6,
    jeu7,
    jeu8,
    libre1,
    libre2,
    libre3,
    libre4,
    valide1,
    valide2,
    valide3,
    valide4,
    deplacement
} Type;


class Carte;

/*!
 * @class Classe PileCarte.
 * Cette classe gère une liste de cartes.
 * Elle est agrégée à la classe Carte et est un agrégat de FenetrePrincipale
 */
class PileCarte {

public:
    /*!
     *  Constructeur de PileCarte
     *  @param tailleFenX longueur de la fenetre en pixels
     *  @param tailleFenY hauteur de la fenetre en pixels
     *  @param factorScaleCards facteur d'échelle des cartes
     *  @param factorScaleButtons facteur d'échelle des boutons
     */
    PileCarte();

    PileCarte(int positionX, int positionY, Type type);

    PileCarte(PileCarte &pileCopiee);

    ~PileCarte();

    void reload(const float &coeffX, const float &coeffY);

    void dessinerPile(cimg_library::CImg<unsigned char> *visu);

    void ajouterCarte(Carte *carte);

    unsigned int getTaille() { return listeCartes_.size(); };

    int getPosX() { return positionX_; };

    int getPosY() { return positionY_; };

    void changerPositionPile(int x, int y);

    void setPosX(int posX);

    void setPosY(int posY);

    void deplacerCartePile(PileCarte *pileRetrait);

    int getClicPositionCarte(int mx, int my);

    void inverserListeCartes();

    bool precedentEstValide(unsigned int position);

    bool EstTriee();

    Carte *getCarte(int position) { return listeCartes_[position]; };

    void brassagePile();

    Type getType() { return type_; }

    void deplacerCartePileAvecPosition(int posCarte1, int posCarte2, PileCarte *pile2);

    int trouverPosCarteId(int id);

    void sauvegarderPile(std::ofstream &ofs);

    void setPositions(int posX, int posY);

    void agrandirPile();

    void setTailleX(const int tailleX);

    void setTailleY(const int tailleY);

    int getTailleX() const;

    int getTailleY() const;


private:
    unsigned int taille_;
    int tailleX_{};
    int tailleY_{};
    int ecartOriginal_{};
    int ecartEntreCartes_{};
    std::vector<Carte *> listeCartes_;
    int positionX_;
    int positionY_;
    Type type_;
};

#endif //FREECELL_PILECARTE_H
