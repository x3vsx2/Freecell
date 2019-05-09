/*!
 *  @file PileCarte.cpp
 *  @brief Défintiion des focntions de la classe PileCarte.
 *  @date 07/05/2019
 *  @authors Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr),
 *  Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr)
*/
#include <random>
#include "pch.h"
#include "PileCarte.h"

using namespace cimg_library;

PileCarte::PileCarte() : type_(unknown), tailleY_(0), tailleX_(0), ecartOriginal_(0), nbCartesPile_(0), listeCartes_(0),
                         positionY_(0), positionX_(0), ecartEntreCartes_(30) {
}

PileCarte::PileCarte(int positionX, int positionY, Type type) : positionX_(positionX), positionY_(positionY),
                                                                type_(type), ecartOriginal_(30) {
    nbCartesPile_ = 0;
    ecartEntreCartes_ = ecartOriginal_;
    tailleX_ = 0;
    tailleY_ = 0;
}

PileCarte::~PileCarte() {
    for (auto &carte : listeCartes_) {
        delete carte;
    }
    listeCartes_.clear();
}

void PileCarte::deplacerCartePile(PileCarte *pileRetrait) {
    //Quand la carte est ajoutée dans une pile sa coordonée en X est celle de la pile, sa coordonnée en Y est celle de
    //la pile multipliée par le nombre de carte dans la pilex30xcoeff
    if (pileRetrait->getTaille() == 0) { std::cout << "pile vide"; }
    pileRetrait->getCarte(pileRetrait->nbCartesPile_ - 1)->setPosX(this->getPosX());
    if (this->getType() > 13 && this->getType() < 18) {
        //si c'est une pile valide on ne décale pas la postion sur y
        pileRetrait->getCarte(pileRetrait->nbCartesPile_ - 1)->setPosY(this->getPosY());
    } else {
        pileRetrait->getCarte(pileRetrait->nbCartesPile_ - 1)->setPosY(
                this->getPosY() + this->listeCartes_.size() * ecartEntreCartes_);
    }
    pileRetrait->getCarte(pileRetrait->nbCartesPile_ - 1)->setPileAppartenance(this);

    //Ajout de la carte dans sa nouvelle pile
    this->ajouterCarte(pileRetrait->getCarte(pileRetrait->nbCartesPile_ - 1));

    //Suppresion de la carte de son ancienne pile
    pileRetrait->listeCartes_.pop_back();
    pileRetrait->nbCartesPile_--;
}

void PileCarte::changerPositionPile(int x, int y) {
    this->setPosX(x);
    this->setPosY(y);
    for (unsigned int i = 0; i < listeCartes_.size(); i++) {
        listeCartes_[i]->setPosX(this->getPosX());
        listeCartes_[i]->setPosY(this->getPosY() + ecartEntreCartes_ * i);
    }
}

void PileCarte::setPosX(int posX) {
    positionX_ = posX;
}

void PileCarte::setPosY(int posY) {
    positionY_ = posY;
}

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

void PileCarte::inverserListeCartes() {
    std::reverse(listeCartes_.begin(), listeCartes_.end());
}

void PileCarte::ajouterCarte(Carte *carte) {
    listeCartes_.push_back(carte);
    nbCartesPile_ = listeCartes_.size();
    carte->setPileAppartenance(this);
}

bool PileCarte::precedentEstValide(unsigned int position) {
    if (position > nbCartesPile_ - 1) { return false; }
    if (position == 0) { return true; }
    else {
        if (listeCartes_[position]->getHauteur() == listeCartes_[position - 1]->getHauteur() - 1 &&
            listeCartes_[position]->getCouleur() % 2 != listeCartes_[position - 1]->getCouleur() % 2) { return true; }
        else { return false; }
    }
}

bool PileCarte::EstTriee() {
    bool validite = true;
    if (this->getTaille() <= 1) {
        return true;
    } else {
        for (unsigned int k = this->getTaille() - 1; k > 0; k--) {
            validite &= precedentEstValide(k);
        }
        return validite;
    }
}

void PileCarte::brassagePile() {
    if (type_ == melange) {
        std::srand(std::time(nullptr));
        std::random_shuffle(listeCartes_.begin(), listeCartes_.end());
    }
}

int PileCarte::trouverPosCarteId(int id) {
    int position = -1;
    for (unsigned int i = 0; i < nbCartesPile_; i++) {
        if (listeCartes_[i]->getIdentifiant() == id) {
            position = i;
            break;
        }
    }
    return position;
}

void PileCarte::deplacerCartePileAvecPosition(int posCarte1, int posCarte2, PileCarte *pile2) {
    // mise à jour des variables Pos
    pile2->listeCartes_[posCarte2]->setPosX(this->getPosX());
    if (this->getType() > 13 && this->getType() < 18) {
        pile2->listeCartes_[posCarte2]->setPosY(this->getPosY());
    } else {
        pile2->listeCartes_[posCarte2]->setPosY(this->getPosY() + 20 * this->listeCartes_.size());
    }
    pile2->listeCartes_[posCarte2]->setPileAppartenance(this);

    //Réalisation du déplacement
    //On ajoute la carte à la position souhaitée
    this->listeCartes_.insert(this->listeCartes_.begin() + posCarte1, pile2->listeCartes_[posCarte2]);
    this->nbCartesPile_++;
    //supprime la carte de la pile melange (ou de l'ancienne pile)
    pile2->listeCartes_.erase(pile2->listeCartes_.begin() + posCarte2);
    pile2->nbCartesPile_--;
}

void PileCarte::setPositions(int posX, int posY) {
    this->setPosX(posX);
    this->setPosY(posY);
}

void PileCarte::reload(const float &coeffX, const float &coeffY) {
    ecartEntreCartes_ = static_cast<int>(ecartOriginal_ * coeffY);
    for (auto itCarte = listeCartes_.begin(); itCarte != listeCartes_.end(); ++itCarte) {
        (*itCarte)->reload(coeffX, coeffY);
        (*itCarte)->setPosX(positionX_);
        if (type_ != valide1 && type_ != valide2 && type_ != valide3 && type_ != valide4) {
            (*itCarte)->setPosY(positionY_ + (ecartEntreCartes_ * (itCarte - listeCartes_.begin())));
        } else {
            if (itCarte - listeCartes_.begin() == listeCartes_.size() - 1) {
                (*itCarte)->setPosY(positionY_);
            }
        }
    }
}

void PileCarte::dessinerPile(cimg_library::CImg<unsigned char> *visu) {
    for (auto itCarte = listeCartes_.begin(); itCarte != listeCartes_.end(); ++itCarte) {
        (*itCarte)->dessinerCarte(visu);
    }
}

void PileCarte::setTailleX(const int tailleX) {
    tailleX_ = tailleX;
}

void PileCarte::setTailleY(const int tailleY) {
    tailleY_ = tailleY;
}

int PileCarte::getTailleX() const {
    return tailleX_;
}

int PileCarte::getTailleY() const {
    return tailleY_;
}