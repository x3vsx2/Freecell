/*!
 *  @file FenetrePrincipale.h
 *  @brief Header de la classe de base
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <stdio.h>
#include <chrono>
#include "PileCarte.h"
#include "Bouton.h"

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

/*!
 * @class Classe FenetrePrincipale.
 * Cette classe de base est celle qui gère l'affichage, les mouvements, les règles et les intéractions utilisateurs.
 * Elle est agrégée à la classe PileCarte
 */
class FenetrePrincipale {

public:

    /*!
     *  Constructeur de la fenetrePrincipale
     *  @param tailleFenX longueur de la fenetre en pixels
     *  @param tailleFenY hauteur de la fenetre en pixels
     *  @param factorScaleCards facteur d'échelle des cartes
     *  @param factorScaleButtons facteur d'échelle des boutons
     */
    FenetrePrincipale(int tailleFenX, int tailleFenY, float factorScaleCards, float factorScaleButtons);

    /*!
     *  Destructeur de la fenetre principale
     *  Efface le pointeur vers disp
     */
    ~FenetrePrincipale();

    //FONCTIONS MENUS ET FENETRES

    /*!
     *  Fonction qui lance le jeu
     *  @param nouvellePartie : true si c'est une nouvelle partie, false si chargement
     *  @return true si victoire, false sinon
     */
    bool lancerJeu(bool nouvellePartie);

    /*!
     *  Affiche la fenetre de chargement
     *  @return true si le chargement a fonctionné, false sinon (quitter, mauvaise sauvegarde...)
     */
    bool fenetreChargement();

    /*!
     *  Affiche la fenetre de sauvegarde
     */
    void fenetreSauvegarde();

    /*!
     *  Affiche la fenetre de parametres (infos) pour changer la taille des éléments
     */
    void fenetreParametres();

    /*!
    *  Affiche la fenetre de victoire
    */
    void fenetreVictoire();

    //FONCTIONS D'INITIALISATION

    /*!
     *Initialise le plateau, le fond et visu selon la taille du jeu
     */
    void initialiserFond();

    /*!
     * Initialise les cartes (création) et ajout dans pileMelange
     */
    void initialiserCartes();

    /*!
     * Initialise les piles et répartie les cartes entre les différentes piles
     */
    void initialiserPiles(bool nouvellePartie);

    //FONCTIONS GESTION JEU
    /*!
 * Deplace un certain nombre de cartes dans la pile pileDeplacement selon la position de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
    void deplacerPile(int mx, int my);

    /*!
 *Renvoie un vecteur avec le numero de la pile suivie du numéro de la carte selon la position du ponteur de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 * @return vector<int> numero pile et numero carte
 */
    std::vector<int> getClicPositions(int mx, int my);

    bool estSaisieValide(int mx, int my);

    /*!
* Renvoie si le depot de cartes à l'emplacement indiqué par mx my est valide
* @param mx position horizontale de la souris
* @param my position verticale de la souris
*@return bool
*/
    bool estDepotValide(int mx, int my);

    /*!
* Renvoie si le joueur à remporter la partie
* @return bool
*/
    bool PartieEstGagnee();

    bool victoireAnticipee();

    void terminerPartie(bool postResize, Bouton &bQuitter, Bouton &bNbCoupsJoues, Bouton &bTime);

    bool commandeFermerFenetre();

    int getPosSourisX() { return disp->mouse_x(); };

    int getPosSourisY() { return disp->mouse_y(); };

    void mesurerTemps(const ClockTime &start_time, const ClockTime &end_time, std::vector<int> &tempsEcoule_);

    int trouverCarte(int id);

    //FONCTIONS D'AFFICHAGE
    void attendre();

    /*!
     * Redessine chaque carte selon sa position
     */
    void majAffichageJeu(bool postResize, Bouton &boutonQuitter, Bouton &bounNbCoups, Bouton &bTime);

    void majAffichageMenu(Bouton &boutonNouvelleP, Bouton &boutonCharger, Bouton &boutonQuitter, Bouton &boutonParam);

    /*!
 *Colorie une image
 * @param img - l'image que l'on veut colorier
 * @param r - couleur rouge 0 à 255
 * @param g - couleur verte 0 à 255
 * @param b - couleur bleu 0 à 255
 * @return vide
 */
    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    void dessinerEmplacementPiles();

    /*!
     *Initialise le plateau, le fond et visu
     * @return int, 1 pour nouvelle partie, 2 pour charger partie, 3 pour quitter
     */
    int afficherMenu();

    void majFenetre();

    void quitterFenetre();

    void supprimerPiles();

    //FONCTIONS SAUVEGARDE ET CHARGEMENT

    void ajouterPartieSauvegardee(std::string nomPartie);

    void sauvegarderPartie(std::string nomPartie);

    void chargerPartie(std::string nomPartie);

    void supprimerPartieChargee(const std::string &nomPartie);

    void chargerTableauParties();

    void sauverTableauParties();

    void sauverFichierSettings(int dispX, int dispY, float cardScale, float buttonScale);

private:
    int tailleFenOriginaleX_; /*!< longeur originale de la fenetre, récupérée dans le fichier settings.txt*/
    int tailleFenOriginaleY_;
    int tailleFenX_;
    int tailleFenY_;
    float facteurEchelleCartes_;
    float facteurEchelleBoutons_;
    float coeffX_;
    float coeffY_;
    int nbCoupsJoues_;
    ClockTime start_time_;
    ClockTime end_time_;
    std::vector<int> tempsEcoule_;
    std::vector<int> tempsEcouleSauvegarde_;
    cimg_library::CImg<unsigned char> *visu_{};
    cimg_library::CImg<unsigned char> *fond_{};
    cimg_library::CImg<unsigned char> *plateau_{};
    cimg_library::CImgDisplay *disp;
    std::vector<std::vector<int>> tableauxIdentifiants;
    std::vector<std::string> tableauParties;
    std::vector<PileCarte *> piles_;

    PileCarte *pileDeplacement{};
    PileCarte *pileMelange{};
    PileCarte *pileJeu1{};
    PileCarte *pileJeu2{};
    PileCarte *pileJeu3{};
    PileCarte *pileJeu4{};
    PileCarte *pileJeu5{};
    PileCarte *pileJeu6{};
    PileCarte *pileJeu7{};
    PileCarte *pileJeu8{};
    PileCarte *pileLibre1{};
    PileCarte *pileLibre2{};
    PileCarte *pileLibre3{};
    PileCarte *pileLibre4{};
    PileCarte *pileValide1{};
    PileCarte *pileValide2{};
    PileCarte *pileValide3{};
    PileCarte *pileValide4{};
};


#endif //FREECELL_FENETREPRINCIPALE_H
