#include "pch.h"
#include "PileCarte.h"

using namespace cimg_library;

PileCarte::PileCarte() {
    taille_ = 0;
    positionY_ = 0;
    positionX_ = 0;
    type_ = unknown;
}

PileCarte::PileCarte(int positionX, int positionY, Type type) : positionX_(positionX), positionY_(positionY),
                                                                type_(type), ecartOriginal_(30) {
    taille_ = 0;
    ecartEntreCartes_ = ecartOriginal_;
}

PileCarte::PileCarte(PileCarte &pileCopiee) : taille_(pileCopiee.taille_),
                                              positionX_(pileCopiee.positionX_), positionY_(pileCopiee.positionY_) {
    for (unsigned int i = 0; i < pileCopiee.taille_; i++) {
        listeCartes_.push_back(pileCopiee.listeCartes_[i]);
    }
}

/*!
 *Destructeur, supprime les cartes contenu dans listeCartes_
 */
PileCarte::~PileCarte() {
    for (unsigned int i = 0; i < listeCartes_.size(); i++) {
        delete listeCartes_[i];
    }
    listeCartes_.clear();
}

/*!
 *Deplace une carte d'une pile à une autre
 * @param pointeur vers la pile retrait
 */
void PileCarte::deplacerCartePile(PileCarte *pileRetrait) {
    //Quand la carte est ajoutée dans une pile sa coordonée en X est celle de la pile, sa coordonnée en Y est celle de
    //la pile multipliée par le nombre de carte dans la pilex30xcoeff
    if (pileRetrait->getTaille() == 0) { std::cout << "pile vide"; }
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosX(this->getPosX());
    if (this->getType() > 13 && this->getType() < 18) {
        //si c'est une pile valide on ne décale pas la postion sur y
        pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosY(this->getPosY());
    } else {
        pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosY(
                this->getPosY() + this->listeCartes_.size() * ecartEntreCartes_);
    }
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPileAppartenance(this);

    //Ajout de la carte dans sa nouvelle pile
    this->ajouterCarte(pileRetrait->getCarte(pileRetrait->taille_ - 1));

    //Suppresion de la carte de son ancienne pile
    pileRetrait->listeCartes_.pop_back();
    pileRetrait->taille_--;
}

/*!
 * Change les attributs positions d'une carte
 * @param x position horizontale de la souris
 * @param y position verticale
 */
void PileCarte::changerPositionPile(int x, int y) {
    this->setPosX(x);
    this->setPosY(y);
    for (unsigned int i = 0; i < listeCartes_.size(); i++) {
        listeCartes_[i]->setPosX(this->getPosX());
        listeCartes_[i]->setPosY(this->getPosY() + 20 * i);
    }
}

/*!
 * Change les attributs positions d'une carte
 * @param posX position horizontale
 */
void PileCarte::setPosX(int posX) {
    positionX_ = posX;
}

/*!
 * Change les attributs positions d'une carte
 * @param posY position verticale de la souris
 */
void PileCarte::setPosY(int posY) {
    positionY_ = posY;
}

/*!
 * Renvoie -1 si la souris n'est sur aucune carte
 * Sinon renvoie la position de la carte
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
int PileCarte::getClicPositionCarte(int mx, int my) {
    int position = -1;
    for (int i = listeCartes_.size() - 1; i >= 0; i--) {
        int imgX1 = listeCartes_[i]->getPosX();
        int imgX2 = listeCartes_[i]->getPosX() + listeCartes_[i]->getTailleX();
        int imgY1 = listeCartes_[i]->getPosY();
        int imgY2 = listeCartes_[i]->getPosY() + listeCartes_[i]->getTailleY();

        if (mx >= imgX1 && mx <= imgX2 && my >= imgY1 && my <= imgY2) {
            position = i;
            return position;
        }
    }
    return position;
}

/*!
 * Inverse l'ordre des éléments dans la liste de carte
 */
void PileCarte::inverserListeCartes() {
    std::reverse(listeCartes_.begin(), listeCartes_.end());
}

/*!
 * Ajoute une carte dans une liste
 * @param *carte pointeur sur la carte que l'on veut inclure dans une pile
 */
void PileCarte::ajouterCarte(Carte *carte) {
    listeCartes_.push_back(carte);
    taille_ = listeCartes_.size();
    carte->setPileAppartenance(this);
}

/*!
 * Renvoie si la carte qui precede position est un assemblage valide dans le jeu
 * renvoie true s'il n'y a pas de précédente
 * renvoie false si la poition est invalide
 * @param position
 * @return bool true s'il n'y a pas de précédente
 *         false si la poition est invalide
 */
bool PileCarte::precedentEstValide(unsigned int position) {
    if (position > taille_ - 1) { return false; }
    if (position == 0) { return true; }
    else {
        if (listeCartes_[position]->getHauteur() == listeCartes_[position - 1]->getHauteur() - 1 &&
            listeCartes_[position]->getCouleur() % 2 != listeCartes_[position - 1]->getCouleur() % 2) { return true; }
        else { return false; }
    }
}

/*!
 * Melange les cartes
 */
void PileCarte::brassagePile() {
    if (type_ == melange) {
        std::srand(std::time(nullptr));
        std::random_shuffle(listeCartes_.begin(), listeCartes_.end());
    }
}

void PileCarte::sauvegarderPile(std::ofstream &ofs) {

}

int PileCarte::trouverPosCarteId(int id) {
    int pos = -1;
    for (unsigned int i = 0; i < taille_; i++) {
        if (listeCartes_[i]->getIdentifiant() == id) {
            pos = i;
            break;
        }
    }
    return pos;
}

void PileCarte::deplacerCartePileAvecPosition(int posCarte1, int posCarte2, PileCarte *pile2) {
    pile2->listeCartes_[posCarte2]->setPosX(this->getPosX());
    pile2->listeCartes_[posCarte2]->setPosY(this->getPosY() + 20 * this->listeCartes_.size());
    pile2->listeCartes_[posCarte2]->setPileAppartenance(this);

    //On ajoute la carte à la position souhaitée
    this->listeCartes_.insert(this->listeCartes_.begin() + posCarte1, pile2->listeCartes_[posCarte2]);
    this->taille_++;
    //supprime la carte de la pile melange (ou de l'ancienne pile)
    pile2->listeCartes_.erase(pile2->listeCartes_.begin() + posCarte2);
    pile2->taille_--;
}

void PileCarte::setPositions(int posX, int posY) {
    this->setPosX(posX);
    this->setPosY(posY);
}

void PileCarte::reload(const float &coeffX, const float &coeffY) {
    ecartEntreCartes_ = (float) ecartOriginal_ * coeffY;
    for (auto itCarte = listeCartes_.begin(); itCarte != listeCartes_.end(); ++itCarte) {
        (*itCarte)->reload(coeffX, coeffY);
        (*itCarte)->setPosX(positionX_);
        (*itCarte)->setPosY(positionY_ + (ecartEntreCartes_ * (itCarte - listeCartes_.begin())));
    }
}

void PileCarte::dessinerPile(cimg_library::CImg<unsigned char> *visu) {
    for (auto itCarte = listeCartes_.begin(); itCarte != listeCartes_.end(); ++itCarte) {
        (*itCarte)->dessinerCarte(visu);
    }
}



