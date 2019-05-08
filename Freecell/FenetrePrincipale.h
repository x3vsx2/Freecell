/*!
 *  @file FenetrePrincipale.h
 *  @brief Header de la classe de base
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

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

    //===========================================FONCTIONS MENUS ET FENETRES=========================================

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

    //===============================FONCTIONS D'INITIALISATION=========================================================

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

    //=========================================FONCTIONS GESTION JEU==================================================
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

    /*!
     * Permet de savoir si la carte correspondant au pointeur de la souris est récupérable
     * @param mx position horizontale de la souris
     * @param my position verticale de la souris
     * @return true si la carte est déplaçable
     */
    bool estSaisieValide(int mx, int my);

    /*!
     * //TODO commentaire
     * @param mx position horizontale de la souris
     * @param my position verticale de la souris
     *@return bool
    */
    bool estDepotValide(int mx, int my);

    /*!
     * Permet de savoir si le joueur à remporter la partie
     * @return bool
     */
    bool PartieEstGagnee();

    //TODO commentaire
    bool victoireAnticipee();

    //TODO commentaire
    void terminerPartie(bool postResize, Bouton &bQuitter, Bouton &bNbCoupsJoues, Bouton &bTime);

    /*!
     * Permet de savoir si l'utilisateur a fermé la fenetre, appuyé sur q ou sur échap
     * @return bool, true si une des touches a été utilisée
     */
    bool commandeFermerFenetre();

    /*!
     * Retourne la position horizontale de la souris
     * @return entier correspondant à la position horizontale du pointeur
     */
    int getPosSourisX() const { return disp->mouse_x(); };

    /*!
     * Retourne la position verticale de la souris
     * @return entier correspondant à la position verticale du pointeur
     */
    int getPosSourisY() const { return disp->mouse_y(); };

    /*!
     * Mesure la différence de temps entre deux temps, et l'enregistre dans un vecteur
     * @param start_time temps au lancement de la partie
     * @param end_time dernier temps mesuré
     * @param tempsEcoule_ vecteur qui contient le temps écoule en HH:MM:SS
     */
    void mesurerTemps(const ClockTime &start_time, const ClockTime &end_time, std::vector<int> &tempsEcoule_);

    //TODO commentaire
    int trouverCarte(int id);

    //==================================FONCTIONS D'AFFICHAGE===========================================================

    /*!
     * Attend une intéraction de l'utilisateur
     */
    void attendre();

    /*!
     * Redessine le plateau de jeu, les boutons, les cartes, l'emplacement des piles.
     * Dans le cas d'un resize de la fenetre, tous les éléments cartes et boutons sont rechargés
     * @param postResize true si on fait une maj suite à un resize de fenetre
     * @param bQuitter
     * @param bNbCoups
     * @param bTime
     */
    void majAffichageJeu(bool postResize, Bouton &bQuitter, Bouton &bNbCoups, Bouton &bTime);

    /*!
     * Redessine le menu.Dans le cas d'un resize de la fenetre, tous les boutons sont rechargés
     * @param postResize true si on fait une maj suite à un resize de fenetre
     * @param bNouvellePartie
     * @param bCharger
     * @param bQuitter
     * @param bParam
     */
    void majAffichageMenu(Bouton &bNouvellePartie, Bouton &bCharger, Bouton &bQuitter, Bouton &bParam);

    /*!
     *Colorie une image
     * @param img - l'image que l'on veut colorier
     * @param r - couleur rouge 0 à 255
     * @param g - couleur verte 0 à 255
     * @param b - couleur bleu 0 à 255
     */
    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    /*!
     * Dessine l'emplacement des piles selon la taille et la position de ces dernières.
     * Les dimensions d'une piles sont définies grâce à la dimension des cartes.
     */
    void dessinerEmplacementPiles();

    /*!
     *Affiche le menu principale, avec les boutons correspondants.
     * @return int, 1 pour nouvelle partie, 2 pour charger partie, 3 pour quitter
     */
    int afficherMenu();

    /*!
     *Fonction appelée lors d'un resize. Met à jour les dimensions de la fenetre.
     * Enregistre les nouveaux coefficients pour recharger les éléments dans la bonne dimension
     */
    void majFenetre();

    /*!
     * Destructeur d'affichage. Efface les pointeurs fond, le plateau et visu.
     */
    void quitterFenetre();

    /*!
     * Destructeur des piles. Efface toutes les piles du jeu. Fais appel au destructeur de PileCarte.
     */
    void supprimerPiles();

    /*!
     * Affiche chargement
     */
    void infoChargement();
    //===============================FONCTIONS SAUVEGARDE ET CHARGEMENT=================================================

    /*!
     * Ajoute le nom d'une partie sauvegardee au vecteur des sauvegarde
     * @param nomPartie le nom de la partie enregistrée
     */
    void ajouterPartieSauvegardee(const std::string &nomPartie);

    /*!
     * Enregistre une partie en créant un fichier selon le nom.
     * Enregistre le temps, le nombre de coups et la position des cartes
     * @param nomPartie le nom de la partie enregistrée
     */
    void sauvegarderPartie(const std::string &nomPartie);

    /*!
     * Charge une partie en lisant le fichier correspondant à nomPartie.
     * Charge le temps, le nombre de coups et la position des cartes
     * @param nomPartie le nom de la partie chargée
     */
    void chargerPartie(const std::string &nomPartie);

    /*!
     * Supprime une partie sauvegardée du disque et du tableau de parties.
     * @param nomPartie le nom de la partie chargée
     */
    void supprimerPartieChargee(const std::string &nomPartie);

    /*!
     * Charge le fichier sauvegardes qui contient toutes les parties enregistrées
     */
    void chargerTableauParties();

    /*!
     * Sauvegarde le fichier sauvegardes qui contient toutes les parties enregistrées
     */
    void sauverTableauParties();

    /*!
     * Enregistre la taille choisie par l'utilisateur pour le fenetre et les facteurs d'échelle.
     */
    void sauverFichierSettings(int dispX, int dispY, float cardScale, float buttonScale);

private:
    int tailleFenOriginaleX_; /*!< longueur originale de la fenetre, récupérée dans le fichier settings.txt*/
    int tailleFenOriginaleY_; /*!< hauteur originale de la fenetre, récupérée dans le fichier settings.txt*/
    int tailleFenX_; /*!< longueur actuelle de la fenetre*/
    int tailleFenY_; /*!< hauteur actuelle de la fenetre*/
    float facteurEchelleCartes_; /*!< facteur d'échelle pour la taille de chargement et d'affichage des boutons*/
    float facteurEchelleBoutons_; /*!< facteur d'échelle pour la taille de chargement et d'affichage des cartes*/
    float coeffX_; /*!< Facteur de redimensionnement de la fenetre en longueur*/
    float coeffY_; /*!< Facteur de redimensionnement de la fenetre en hauteur*/
    int nbCoupsJoues_; /*!< Nombre de coups joués*/
    ClockTime start_time_; /*!< Horloge qui contient le temps où la partie a débutée en ns*/
    ClockTime end_time_; /*!< Horloge qui permet de faire des comparaison avec le temps où la partie a débutée en ns*/
    std::vector<int> tempsEcoule_; /*!< Vecteur qui contient le temps écoulée depuis le début de la partie*/
    std::vector<int> tempsEcouleSauvegarde_; /*!< Vecteur qui contient le temps écoulée si c'est une partie chargée*/
    cimg_library::CImg<unsigned char> *visu_{}; /*!< Premier plan du jeu*/
    cimg_library::CImg<unsigned char> *fond_{}; /*!< Arrière plan du jeu*/
    cimg_library::CImgDisplay *disp; /*!< display sur lequel on dessine notre fond et visu*/
    std::vector<std::vector<int>> tabIdCartesChargement_; /*!< Vecteur qui contient l'ordre des cartes lors d'un chargement*/
    std::vector<std::string> tabParties_; /*!< Vecteur contenant toutes les parties sauvegardées*/
    std::vector<PileCarte *> piles_; /*!< Vecteur contenant toutes les piles Jeu, Libres, Valides*/

    PileCarte *pileDeplacement{}; /*!< Pile qui contient les cartes que l'utilisateur est en train de déplacer*/
    PileCarte *pileMelange{}; /*!< Pile tampon utilisée lors de l'initialisation du jeu*/
    PileCarte *pileJeu1{};/*!< Pile de jeu*/
    PileCarte *pileJeu2{};/*!< Pile de jeu*/
    PileCarte *pileJeu3{};/*!< Pile de jeu*/
    PileCarte *pileJeu4{};/*!< Pile de jeu*/
    PileCarte *pileJeu5{};/*!< Pile de jeu*/
    PileCarte *pileJeu6{};/*!< Pile de jeu*/
    PileCarte *pileJeu7{};/*!< Pile de jeu*/
    PileCarte *pileJeu8{};/*!< Pile de jeu*/
    PileCarte *pileLibre1{};/*!< Pile tampon pour faire des échanges*/
    PileCarte *pileLibre2{};/*!< Pile tampon pour faire des échanges*/
    PileCarte *pileLibre3{};/*!< Pile tampon pour faire des échanges*/
    PileCarte *pileLibre4{};/*!< Pile tampon pour faire des échanges*/
    PileCarte *pileValide1{};/*!< Pile triée vallide*/
    PileCarte *pileValide2{};/*!< Pile triée vallide*/
    PileCarte *pileValide3{};/*!< Pile triée vallide*/
    PileCarte *pileValide4{};/*!< Pile triée vallide*/
};

#endif //FREECELL_FENETREPRINCIPALE_H