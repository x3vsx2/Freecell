//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "PileCarte.h"
#include "Bouton.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>


using namespace std;
using namespace cimg_library;

FenetrePrincipale::FenetrePrincipale() : tableauxIdentifiants(15, vector<int>(0)) {
    vector<PileCarte *> piles;
    initialiserFond();
    //Declare un display pour afficher le fond
    disp = new CImgDisplay(*fond_, "FreeCell", 0, false, false);

    //Centrer la fenetre
    disp->move((CImgDisplay::screen_width() - disp->width()) / 2,
               (CImgDisplay::screen_height() - disp->height()) / 2);

    int choix;
    do {
        choix = afficherMenu();
        effacerFond();
        switch (choix) {
            case 0: {
                lancerJeu(true);
                disp->wait();
                fenetreSauvegarde();
                quitterPartie();
                break;
            }

            case 1: {
                if (fenetreChargement()) {
                    lancerJeu(false); // out of range
                    disp->wait();
                    fenetreSauvegarde();
                    quitterPartie();
                }
                break;
            }
            case 2:
                break;
        }
    } while (choix != 2 && !disp->is_closed() && !disp->is_keyESC() && !disp->is_keyQ());


}

/*!
 *Renvoie un vecteur avec le numero de la pile suivie du numéro de la carte selon la position du ponteur de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 * @return vector<int> numero pile et numero carte
 */
vector<int> FenetrePrincipale::getClicPositions(int mx, int my) {

    vector<int> positions;
    positions.push_back(-1);
    positions.push_back(-1);

    //Cherche si il y a une carte qui correspond à la position de la souris dans les piles_ de Jeu
    for (unsigned int i = 0; i < piles_.size(); i++) {
        positions[1] = piles_[i]->getClicPositionCarte(mx, my);
        if (positions[1] != -1) {
            positions[0] = i;
            return positions;
        }
    }

    //==================Partie utilisée dans le cas d'un dépôt  de carte=================================
    //Cherche si il y a une position Libre qui correspond à la position de la souris dans les piles_ Jeu
    for (unsigned int i = 0; i < piles_.size(); i++) {
        int pileX1 = piles_[i]->getPosX();
        int pileX2 = piles_[i]->getPosX() + 74;
        int pileY1 = piles_[i]->getPosY();
        int pileY2 = piles_[i]->getPosY() + 99;
        if (mx >= pileX1 && mx <= pileX2 && my >= pileY1 && my <= pileY2) {
            positions[0] = i;
            positions[1] = -2;
            return positions;
        }
    }
    return positions;
}

/*!
 * Initialise les piles et répartie les cartes entre les différentes piles
 */
void FenetrePrincipale::initialiserPiles(bool nouvellePartie) {
    pileDeplacement = new PileCarte(0, 0, deplacement);
    pileJeu1 = new PileCarte(0.10 * disp->width(), 300, jeu1);
    pileJeu2 = new PileCarte(0.20 * disp->width(), 300, jeu2);
    pileJeu3 = new PileCarte(0.30 * disp->width(), 300, jeu3);
    pileJeu4 = new PileCarte(0.40 * disp->width(), 300, jeu4);
    pileJeu5 = new PileCarte(0.50 * disp->width(), 300, jeu5);
    pileJeu6 = new PileCarte(0.60 * disp->width(), 300, jeu6);
    pileJeu7 = new PileCarte(0.70 * disp->width(), 300, jeu7);
    pileJeu8 = new PileCarte(0.80 * disp->width(), 300, jeu8);

    piles_.clear();
    piles_.push_back(pileJeu1);
    piles_.push_back(pileJeu2);
    piles_.push_back(pileJeu3);
    piles_.push_back(pileJeu4);
    piles_.push_back(pileJeu5);
    piles_.push_back(pileJeu6);
    piles_.push_back(pileJeu7);
    piles_.push_back(pileJeu8);

    if (nouvellePartie) {//On mélange et répartie les cartes seulement si c'est une nouvelle partie
        pileMelange->brassagePile();
        for (unsigned int i = 0; i < 6; i++) {
            pileJeu1->deplacerCartePile(pileMelange);
            pileJeu2->deplacerCartePile(pileMelange);
            pileJeu3->deplacerCartePile(pileMelange);
            pileJeu4->deplacerCartePile(pileMelange);
            pileJeu5->deplacerCartePile(pileMelange);
            pileJeu6->deplacerCartePile(pileMelange);
            pileJeu7->deplacerCartePile(pileMelange);
            pileJeu8->deplacerCartePile(pileMelange);
        }
        pileJeu1->deplacerCartePile(pileMelange);
        pileJeu2->deplacerCartePile(pileMelange);
        pileJeu3->deplacerCartePile(pileMelange);
        pileJeu4->deplacerCartePile(pileMelange);
    } else {//Initialise les piles selon le chargement
        for (unsigned int i = 0; i < 15; i++) {
            for (unsigned int j = 0; j < tableauxIdentifiants[i].size(); j++) {
                int idAchercher = tableauxIdentifiants[i][j];
                if (idAchercher == 0) {
                    break;
                }
                int posPileMelange = -1;
				if (i > 7) {
					cout << " C'est là cette fois" << endl;
				}
                //On regarde dans la pile Melange pour trouver sa position
                posPileMelange = pileMelange->trouverPosCarteId(idAchercher);
                piles_[i]->deplacerCartePileAvecPosition(piles_[i]->getTaille(), posPileMelange, pileMelange); //pile.size = 8 donc out of range pour i>8
                etatChargement();
            }
        }
    }

    pileLibre1 = new PileCarte(0.08 * disp->width(), 50, libre1);
    pileLibre2 = new PileCarte(0.18 * disp->width(), 50, libre2);
    pileLibre3 = new PileCarte(0.28 * disp->width(), 50, libre3);
    pileLibre4 = new PileCarte(0.38 * disp->width(), 50, libre4);
    pileValide1 = new PileCarte(0.52 * disp->width(), 50, valide1);
    pileValide2 = new PileCarte(0.62 * disp->width(), 50, valide2);
    pileValide3 = new PileCarte(0.72 * disp->width(), 50, valide3);
    pileValide4 = new PileCarte(0.82 * disp->width(), 50, valide4);

    piles_.push_back(pileLibre1);
    piles_.push_back(pileLibre2);
    piles_.push_back(pileLibre3);
    piles_.push_back(pileLibre4);

    piles_.push_back(pileValide1);
    piles_.push_back(pileValide2);
    piles_.push_back(pileValide3);
    piles_.push_back(pileValide4);

    delete pileMelange;

    dessinerEmplacementPiles();

}

bool FenetrePrincipale::estSaisieValide(int mx, int my) {

    vector<int> positionsCartecliquee = getClicPositions(mx, my);
    //On verifie si on a clique sur une pile qui serait vide, c'est à dire qu'il n'y a plus de cartes dedans
    //Laisser ce test en PREMIER, sinon on cherche à accéder à des éléments non existants

    if (positionsCartecliquee[0] == -1)return false;
    if (positionsCartecliquee[1] == -2 || positionsCartecliquee[0] == -1) {
        //La pile est VIDE (JEU ou LIBRES), on ne peut pas prendre de carte
        //OU
        //Aucune carte ne correspond à la position de la souris
        return false;
    } else {
        if (positionsCartecliquee[1] ==
            piles_[positionsCartecliquee[0]]->getTaille()) { return true; }// si il y a une seul carte return true
        else {
            bool validite = true;
            for (unsigned int k = piles_[positionsCartecliquee[0]]->getTaille() - 1;
                 k > positionsCartecliquee[1]; k--) {
                validite &= piles_[positionsCartecliquee[0]]->precedentEstValide(k);
            }
            return (validite);
        }
    }
    return false;
}

/*!
* Renvoie si le depot de cartes à l'emplacement indiqué par mx my est valide
* @param mx position horizontale de la souris
* @param my position verticale de la souris
*@return bool
*/
bool FenetrePrincipale::estDepotValide(int mx, int my) {
    vector<int> positionsCiblee = getClicPositions(mx, my);
    if (positionsCiblee[0] == -1) { return false; }
    else {
        if (piles_[positionsCiblee[0]]->getType() > 1 && piles_[positionsCiblee[0]]->getType() < 10) {
            //si c'est une pile jeu
			if (positionsCiblee[1] == -2) { return true; } // si la pile est vide alors le dépot est autorisé
            if (pileDeplacement->getCarte(0)->getCouleur() % 2 !=
                piles_[positionsCiblee[0]]->getCarte(piles_[positionsCiblee[0]]->getTaille() - 1)->getCouleur() %
                2 && pileDeplacement->getCarte(0)->getHauteur() == piles_[positionsCiblee[0]]->getCarte(
                    piles_[positionsCiblee[0]]->getTaille() - 1)->getHauteur() - 1) {
                // condition 1 : les couleurs sont oppsées
                // condition 2 : les hauteurs se suivent dans le bon ordre
                return true;
            } else { return false; }
        }
        if (piles_[positionsCiblee[0]]->getType() >= 10 && piles_[positionsCiblee[0]]->getType() <= 13) {
            // si c'est une pile libre
            if (pileDeplacement->getTaille() == 1 && piles_[positionsCiblee[0]]->getTaille() == 0) {
                return true;
            } else {
                return false;
            }

        }
        if (piles_[positionsCiblee[0]]->getType() >= 14 && piles_[positionsCiblee[0]]->getType() <= 17) {
            // si c'est une pile valide
            if (pileDeplacement->getTaille() == 1) {
                //si pris une seul carte
                if (piles_[positionsCiblee[0]]->getTaille() == 0) {
                    // si pile valide vide alors on accepte que des as
                    if (pileDeplacement->getCarte(0)->getHauteur() == As) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (pileDeplacement->getCarte(0)->getHauteur() == piles_[positionsCiblee[0]]->getCarte(
                            piles_[positionsCiblee[0]]->getTaille() - 1)->getHauteur() + 1 &&
                        pileDeplacement->getCarte(0)->getCouleur() == piles_[positionsCiblee[0]]->getCarte(
                                piles_[positionsCiblee[0]]->getTaille() - 1)->getCouleur()) {
                        //condition 1 : les hauteurs se succèdent
                        //condition 2 : les cartes sont de meme couleur
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
        return false;
    }
}

/*!
* Renvoie si le joueur à remporter la partie
* @return bool
*/
bool FenetrePrincipale::PartieEstGagnee() {
	//TODO : faire le calcule nombre de carte placee
	unsigned int nombreDeCartePlacee = 0;
	if (nombreDeCartePlacee == 52) {
		return true;
	}
	else {
		return(false);
	}
}

void FenetrePrincipale::etatChargement() {
//Debug
    //Liste souhaitée
    for (unsigned int x = 0; x < tableauxIdentifiants.size(); x++) {
        for (unsigned int y = 0; y < tableauxIdentifiants[x].size(); y++) {
            cout << tableauxIdentifiants[x][y] << " ";
        }
    }
    cout << endl;
    //Liste actuelle
    for (unsigned int k = 0; k < piles_.size(); k++) {
        for (unsigned int l = 0; l < piles_[k]->getTaille(); l++) {
            cout << piles_[k]->getCarte(l)->getIdentifiant() << " ";
        }
    }
    cout << endl;
    cout << endl;
}

void FenetrePrincipale::quitterPartie() {
    delete visu_;
    delete plateau_;
    delete fond_;
    for (vector<PileCarte *>::iterator itPile = piles_.begin(); itPile != piles_.end(); ++itPile) {
        delete *itPile;
    }
    delete pileDeplacement;
}

bool FenetrePrincipale::fenetreChargement() {
    initialiserFond();
    unsigned char white[] = {255, 255, 255};        // Define a purple color
    unsigned char couleurFond[] = {26, 83, 92};        // Define a purple color

    Bouton partiesSauvegardees("titre", disp->width() / 2 - 400, 10,
                               "icones_et_boutons/partiesSauvegardees.png");
    partiesSauvegardees.dessinerBouton(visu_);

    Bouton bchargerPartie("chargerPartie", disp->width() / 2 + 100, disp->height() - 200,
                          "icones_et_boutons/chargerPartie.png");
    bchargerPartie.dessinerBouton(visu_);

    Bouton bsupprimerSauvegarde("supprimerSauvegarde", disp->width() / 2 - 400, disp->height() - 200,
                                "icones_et_boutons/supprimerSauvegarde.png");
    bsupprimerSauvegarde.dessinerBouton(visu_);

    Bouton bQuitter("Quitter", disp->width() - 85, disp->height() - 100,
                    "icones_et_boutons/miniQuitter.png");
    bQuitter.dessinerBouton(visu_);

    chargerTableauParties();
    for (unsigned int i = 0; i < tableauParties.size(); i++) {
        string nom = tableauParties[i].substr(0, tableauParties[i].length() - 4);
        visu_->draw_text(disp->width() / 2 - 400, 200 + 30 * i, nom.data(), white, couleurFond, 1, 20);
    }
    visu_->display(*disp);

    disp->wait();
    do {
        if (disp->button()) {//Test si clique
            //Recuperation positions de la souris
            //mx = position souris en x, my = position souris en y
            const int mx = disp->mouse_x() * (*fond_).width() / disp->width(),
                    my = disp->mouse_y() * (*fond_).height() / disp->height();
            if (bchargerPartie.estCliquee(mx, my)) {
                cout << "Entrez le nom de la sauvegarde que vous voulez charger et appuyez sur entrée" << endl;
                string nomSauvegarde;
                cin >> nomSauvegarde;
                nomSauvegarde.append(".txt");
                bool trouvee = false;
                for (vector<string>::iterator it = tableauParties.begin(); it != tableauParties.end(); ++it) {
                    if (*it == nomSauvegarde) {
                        chargerPartie(nomSauvegarde);
                        trouvee = true;
                        break;
                    }
                }
                if (!trouvee) cout << nomSauvegarde << " n'existe pas. Veuillez recommencez." << endl;
                else { return true; }
            } else if (bsupprimerSauvegarde.estCliquee(mx, my)) {
                cout << "Entrez le nom de la sauvegarde que vous voulez supprimer et appuyez sur entrer"
                     << endl;
                string nomSauvegarde;
                cin >> nomSauvegarde;
                nomSauvegarde.append(".txt");
                bool trouvee = false;
                for (vector<string>::iterator it = tableauParties.begin(); it != tableauParties.end(); ++it) {
                    if (*it == nomSauvegarde) {
                        supprimerPartieChargee(nomSauvegarde);
                        trouvee = true;
                        break;
                    }
                }
                if (!trouvee) cout << nomSauvegarde << " n'existe pas. Veuillez recommencez." << endl;
                else { return false; }
            } else if (bQuitter.estCliquee(mx, my)) {
                return false;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
        }
    } while (true);
}

void FenetrePrincipale::fenetreSauvegarde() {
    initialiserFond();

    Bouton question("question", disp->width() / 2 - 150, 100,
                    "icones_et_boutons/question_enregistrer.png");
    question.dessinerBouton(visu_);

    Bouton non("non", disp->width() / 2 - 400, 400,
               "icones_et_boutons/non.png");
    non.dessinerBouton(visu_);

    Bouton oui("oui", disp->width() / 2 + 100, 400,
               "icones_et_boutons/oui.png");
    oui.dessinerBouton(visu_);

    Bouton intructions("intstructions", disp->width() / 2 + 100, 500,
                       "icones_et_boutons/instructions.png");
    string nomSauvegarde;
    visu_->display(*disp);
    disp->wait();
    do {
        if (disp->button()) {//Test si clique
            //Recuperation positions de la souris
            //mx = position souris en x, my = position souris en y
            const int mx = disp->mouse_x() * (*fond_).width() / disp->width(),
                    my = disp->mouse_y() * (*fond_).height() / disp->height();
            if (mx >= oui.getpositionX() &&
                mx <= oui.getpositionX() + oui.getTailleX()
                && my >= oui.getpositionY() &&
                my <= oui.getpositionY() + oui.getTailleY()) {
                intructions.dessinerBouton(visu_);
                visu_->display(*disp);

                cout << "Entrez le nom de la sauvegarde (sans espaces) et appuyez sur entrée" << endl;
                cin >> nomSauvegarde;
                nomSauvegarde.append(".txt");
                ajouterPartieSauvegardee(nomSauvegarde);
                sauvegarderPartie(nomSauvegarde);
                sauverTableauParties();
                break;
            } else if (mx >= non.getpositionX() &&
                       mx <= non.getpositionX() + non.getTailleX()
                       && my >= non.getpositionY() &&
                       my <= non.getpositionY() + non.getTailleY()) {
                break;
            }
        }
    } while (true);
}

void FenetrePrincipale::ajouterPartieSauvegardee(std::string nomPartie) {
    tableauParties.insert(tableauParties.begin(), nomPartie);
}

void FenetrePrincipale::sauvegarderPartie(string nomPartie) {
    ofstream ofs(nomPartie);
    for (unsigned int i = 0; i < piles_.size(); i++) {
        ofs << "PILE" << endl;
        ofs << piles_[i]->getTaille() << endl;
        for (unsigned int j = 0; j < piles_[i]->getTaille(); j++) {
            ofs << piles_[i]->getCarte(j)->getIdentifiant() << " ";
        }
        if (piles_[i]->getTaille() == 0) {
            ofs << 0 << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

void FenetrePrincipale::chargerPartie(string nomPartie) {
    ifstream ifs(nomPartie);
    ifs.seekg(0, std::ios::beg);//Debut du fichier
    string contenu;
    for (unsigned int i = 0; i < 15; i++) {
        if (!tableauxIdentifiants[i].empty()) {
            tableauxIdentifiants[i].clear();
        }
        getline(ifs, contenu);
        int taillePile;
        if (contenu == "PILE") {
            ifs >> taillePile;
            int iDcarte;
            for (unsigned int j = 0; j < taillePile; j++) {
                ifs >> iDcarte;
                tableauxIdentifiants[i].push_back(iDcarte);
            }
            if (taillePile == 0) {
                ifs >> iDcarte;//on balance dans le vide
            }
            ifs.ignore();
            ifs.ignore();
        }
    }
    ifs.close();
}

void FenetrePrincipale::supprimerPartieChargee(std::string nomPartie) {
    for (vector<string>::iterator it = tableauParties.begin(); it != tableauParties.end(); ++it) {
        if (*it == nomPartie) {
            it->erase();
            break;
        }
    }
    if (remove(nomPartie.data()) != 0)
        perror("Error deleting file");
    else
        cout << "File successfully deleted" << endl;
    sauverTableauParties();
}

void FenetrePrincipale::chargerTableauParties() {
    tableauParties.clear();

    ifstream ifs("sauvegardes.txt");
    ifs.seekg(0, std::ios::beg);//Debut du fichier
    int taille;
    ifs >> taille;
    ifs.ignore();
    string contenu;
    for (unsigned int i = 0; i < taille; i++) {
        getline(ifs, contenu);
        tableauParties.push_back(contenu);
    }
    ifs.close();
}

void FenetrePrincipale::sauverTableauParties() {
    ofstream ofs("sauvegardes.txt");
    ofs << tableauParties.size() << endl;
    string contenu;
    for (unsigned int i = 0; i < tableauParties.size(); i++) {
        ofs << tableauParties[i] << endl;
    }
    ofs.close();
}
