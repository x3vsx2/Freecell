/*!
 *  @file PileCarte.h
 *  @brief Fichier contenant la déclaration de la classe PileCarte.
 *  @date 07/05/2019
 *  @authors Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr),
 *  Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_PILECARTE_H
#define FREECELL_PILECARTE_H

#include <vector>
#include <fstream>
#include "pch.h"
#include "Carte.h"

using namespace cimg_library;

//Définition des type de pile possible
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
 * Elle est un agrégat de FenetrePrincipale
 */
class PileCarte {

public:
    /*!
     *  Constructeur par défaut de pile Carte
     */
    PileCarte();

    /*!
     *  Constructeur de PileCarte.
     *  @param positionX position en x de la pile
     *  @param positionY position en y de la pile
     *  @param type type de la pile
     */
    PileCarte(int positionX, int positionY, Type type);

    /*!
     *  Destructeur de PileCarte.
     *  Détruit la pile en supprimant toutes les cartes à l'intérieur.
     *  Fait appel au destructeur de Carte
     */
    ~PileCarte();

    /*!
     *  Recharge les cartes contenues dans la pile.
     *  @param coeffX coefficient de redimensionnement en X
     *  @param coeffY coefficient de redimensionnement en Y
     */
    void reload(const float &coeffX, const float &coeffY);

    /*!
     *  Dessine les cartes sur l'affichage
     *  @param visu, le plan sur lequel vont être déssinées les cartes
     */
    void dessinerPile(cimg_library::CImg<unsigned char> *visu);

    /*!
     *  Ajoute une carte dans la pile.
     *  @param pointeur vers une carte
     */
    void ajouterCarte(Carte *carte);

    /*!
     *  Renvoie le nombre de Cartes dans la pile
     *  @return nombre de cartes dans la pile
     */
    unsigned int getTaille() const { return listeCartes_.size(); };

    /*!
     *  Retourne la position horizontale de la pile
     *  @return position en x de la pile
     */
    int getPosX() const { return positionX_; };

    /*!
     *  Retourne la position verticale de la pile
     *  @return position en y de la pile
     */
    int getPosY() const { return positionY_; };

    /*!
     * Change les attributs positions d'une pile. Appelle setPosX et setPosY
     * @param x nouvelle position horizontale
     * @param y nouvelle position verticale
     */
    void changerPositionPile(int x, int y);

    /*!
     * Change l'attibut positionX_ d'une pile
     * @param posX position horizontale
     */
    void setPosX(int posX);

    /*!
     * Change l'attibut positionY_ d'une pile
     * @param posY position verticale
     */
    void setPosY(int posY);

    /*!
     * Deplace une carte d'une pile à une autre
     * @param pointeur vers la pile retrait
     */
    void deplacerCartePile(PileCarte *pileRetrait);

    /*!
     * Renvoie -1 si la souris n'est sur aucune carte
     * Sinon renvoie la position de la carte
     * @param mx position horizontale de la souris
     * @param my position verticale de la souris
     * @return position
     */
    int getClicPositionCarte(int mx, int my);

    /*!
     * Inverse l'ordre des éléments dans la liste de carte
     */
    void inverserListeCartes();

    /*!
     * Renvoie si la carte qui precede position est un assemblage valide dans le jeu
     * renvoie true s'il n'y a pas de précédente
     * renvoie false si la poition est invalide
     * @param position
     * @return bool true s'il n'y a pas de précédente
     *         false si la poition est invalide
     */
    bool precedentEstValide(unsigned int position);

    /*!
     * Renvoie si la pile est triée au sens des règles du jeu
     * @return bool true si la pile est triée, false sinon
     */
    bool EstTriee();

    /*!
     * Renvoie le pointeur vers la carte ayant la position passée en paramètre
     * @param position d'une carte dans la pile
     * @return pointeur vers une carte
     */
    Carte *getCarte(int position) { return listeCartes_[position]; };

    /*!
     * Melange les cartes
     */
    void brassagePile();

    /*!
     * Retourne le type de la pile
     * @return type de pile
     */
    Type getType() { return type_; }

    /*!
     * Deplace une carte d'une pile à une autre selon les positions souhaitées
     * @param posCarte1 nouvelle position de la carte dans la nouvelle pile
     * @param posCarte2 position de la carte dans la pile de retrait
     * @param pile2 pointeur vers la pile de retrait
     */
    void deplacerCartePileAvecPosition(int posCarte1, int posCarte2, PileCarte *pile2);

    /*
     * Renvoie la postion de la carte identifié par l'identifiant id
     * @param id
     * @return position
     */
    int trouverPosCarteId(int id);

    /*
     * Affecte la position de la pile à posX, posY
     * @param posX : position selon X
     * @param posY : position selon Y
     */
    void setPositions(int posX, int posY);

    /*
     * Set largeur de la base de la pile
     * @param tailleX Largeur
     */
    void setTailleX(const int tailleX);

    /*
     * Set hauteur de la base de la pile
     * @param tailleY Hauteur
     */
    void setTailleY(const int tailleY);

    /*
     * Retourne la largeur de la base de la pile
     * @return Largeur
     */
    int getTailleX() const;

    /*
     * Retourne la hauteur de la base de la pile
     * @return Hauteur
     */
    int getTailleY() const;


private:
    unsigned int nbCartesPile_; /*!< Nombre de cartes dans la pile*/
    int tailleX_; /*!< Largeur de la base de la pile*/
    int tailleY_; /*!< Hauteur de la base de la pile*/
    int ecartOriginal_; /*!< Ecart original entre les cartes dans la pile, par défaut à 30*/
    int ecartEntreCartes_; /*!< Ecart actuel entre les cartes dans la pile*/
    std::vector<Carte *> listeCartes_; /*!< Vecteur contenant les pointeurs vers les cartes de la pile*/
    int positionX_; /*!< Position horizontale de la pile*/
    int positionY_; /*!< Position verticale de la pile*/
    Type type_; /*!< Type de la pile*/
};

#endif //FREECELL_PILECARTE_H
