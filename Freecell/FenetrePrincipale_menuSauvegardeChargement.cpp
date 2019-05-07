//
// Created by kamilcaglar on 29/04/19.
//
#include"pch.h"
#include"FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

bool FenetrePrincipale::fenetreChargement() {
    initialiserFond();

    Bouton partiesSauvegardees("titre", "icones_et_boutons/partiesSauvegardees.png", facteurEchelleBoutons_);
    partiesSauvegardees.dessinerBouton(visu_, disp->width() / 2 - partiesSauvegardees.getTailleX() / 2,
                                       disp->height() * 0.1);

    Bouton bchargerPartie("chargerPartie", "icones_et_boutons/chargerPartie.png", facteurEchelleBoutons_);
    bchargerPartie.dessinerBouton(visu_, disp->width() / 2 + bchargerPartie.getTailleX() * 0.1,
                                  disp->height() * 0.7);

    Bouton bsupprimerSauvegarde("supprimerSauvegarde", "icones_et_boutons/supprimerSauvegarde.png",
                                facteurEchelleBoutons_);
    bsupprimerSauvegarde.dessinerBouton(visu_, disp->width() / 2 - bsupprimerSauvegarde.getTailleX() * 1.1,
                                        disp->height() * 0.7);

    Bouton bQuitter("Quitter", "icones_et_boutons/miniQuitter.png", facteurEchelleBoutons_ / 2);
    bQuitter.dessinerBouton(visu_, disp->width() - bQuitter.getTailleX() * 1.1,
                            disp->height() - bQuitter.getTailleY() * 1.1);

    Bouton bInstructions("Instructions", "icones_et_boutons/instructionsSuppression.png", facteurEchelleBoutons_ / 2);

    chargerTableauParties();
    for (unsigned int i = 0; i < tableauParties.size(); i++) {
        string nom = tableauParties[i].substr(0, tableauParties[i].length() - 4);
        visu_->draw_text(partiesSauvegardees.getpositionX(),
                         partiesSauvegardees.getpositionY() + partiesSauvegardees.getTailleY() + 30 * (i + 1),
                         nom.data(), couleurBlanche, couleurFond, 1, 20);
    }
    visu_->display(*disp);
    do {
        if (disp->button()) {//Test si clique
            const int mx = getPosSourisX();
            const int my = getPosSourisY();

            if (bchargerPartie.estCliquee(mx, my)) {
                bInstructions.dessinerBouton(visu_, disp->width() / 2 - bInstructions.getTailleX() / 2,
                                             disp->height() / 2 - bInstructions.getTailleY() / 2);
                system(CLEAR);
                cout << "Entrez le nom de la sauvegarde que vous voulez charger et appuyez sur entrée" << endl;
                string nomSauvegarde;
                cin >> nomSauvegarde;
                nomSauvegarde.append(".txt");
                bool trouvee = false;
                for (auto &tableauPartie : tableauParties) {
                    if (tableauPartie == nomSauvegarde) {
                        chargerPartie(nomSauvegarde);
                        trouvee = true;
                        break;
                    }
                }
                if (!trouvee) cout << nomSauvegarde << " n'existe pas. Veuillez recommencez." << endl;
                else {
                    quitterFenetre();
                    return true;
                }
            } else if (bsupprimerSauvegarde.estCliquee(mx, my)) {
                bInstructions.dessinerBouton(visu_, disp->width() / 2 - bInstructions.getTailleX() / 2,
                                             disp->height() / 2 - bInstructions.getTailleY() / 2);
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
                else {
                    quitterFenetre();
                    return false;
                }
            } else if (bQuitter.estCliquee(mx, my)) {
                quitterFenetre();
                return false;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
        }
        attendre();
    } while (true);
}

void FenetrePrincipale::fenetreSauvegarde() {
    initialiserFond();

    Bouton question("question", "icones_et_boutons/question_enregistrer.png", facteurEchelleBoutons_);
    question.dessinerBouton(visu_, disp->width() / 2 - question.getTailleX() / 2,
                            disp->height() * 0.1);

    Bouton non("non", "icones_et_boutons/non.png", facteurEchelleBoutons_);
    non.dessinerBouton(visu_, disp->width() / 2 - non.getTailleX() * 1.1,
                       disp->height() * 0.7);

    Bouton oui("oui", "icones_et_boutons/oui.png", facteurEchelleBoutons_);
    oui.dessinerBouton(visu_, disp->width() / 2 + oui.getTailleX() * 0.1,
                       disp->height() * 0.7);

    Bouton intructions("intstructions", "icones_et_boutons/instructions.png", facteurEchelleBoutons_);
    string nomSauvegarde;
    visu_->display(*disp);
    do {
        if (disp->button()) {//Test si clique
            if (oui.estCliquee(getPosSourisX(), getPosSourisY())) {
                intructions.dessinerBouton(visu_, disp->width() / 2 - intructions.getTailleX() / 2,
                                           disp->height() / 2 - intructions.getTailleY() / 2);
                visu_->display(*disp);
                cout << "Entrez le nom de la sauvegarde (sans espaces) et appuyez sur entrée" << endl;
                cin >> nomSauvegarde;
                nomSauvegarde.append(".txt");
                ajouterPartieSauvegardee(nomSauvegarde);
                sauvegarderPartie(nomSauvegarde);
                sauverTableauParties();
                break;
            } else if (non.estCliquee(getPosSourisX(), getPosSourisY())) {
                break;
            }
        }
        attendre();
    } while (true);

    supprimerPiles();
    quitterFenetre();
}

void FenetrePrincipale::fenetreVictoire() {
    initialiserFond();
    Bouton boutonGagne("BoutonGagne", "icones_et_boutons/fireworks.png", 1);
    boutonGagne.dessinerBouton(visu_, disp->width() / 2 - boutonGagne.getTailleX() / 2,
                               disp->height() * 0.1);
    Bouton bQuitter("Quitter", "icones_et_boutons/miniQuitter.png", facteurEchelleBoutons_ / 2);
    bQuitter.dessinerBouton(visu_, disp->width() - bQuitter.getTailleX() * 1.1,
                            disp->height() - bQuitter.getTailleY() * 1.1);

    visu_->display(*disp);
    do {
        if (disp->button()) {//Test si clique
            if (bQuitter.estCliquee(getPosSourisX(), getPosSourisY())) {
                break;
            }
        }
    } while (!commandeFermerFenetre());
    quitterFenetre();
}

void FenetrePrincipale::ajouterPartieSauvegardee(std::string nomPartie) {
    if (std::find(tableauParties.begin(), tableauParties.end(), nomPartie) != tableauParties.end()) {
        /* tableauParties contains nomPartie */
    } else {
        /* tableauParties does not contain nomPartie */
        tableauParties.insert(tableauParties.begin(), nomPartie);
    }
}

void FenetrePrincipale::sauvegarderPartie(string nomPartie) {
    ofstream ofs(nomPartie);
    if (!ofs.is_open()) cerr << "Erreur d'ouverture de " << nomPartie << endl;
    else {
        ofs << nbCoupsJoues_ << endl;
        ofs << tempsEcoule_[0] << endl;
        ofs << tempsEcoule_[1] << endl;
        ofs << tempsEcoule_[2] << endl;
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
        if (!ofs.good()) cout << "Erreur d'écriture sur" << nomPartie << endl;
        ofs.close();
    }

}

void FenetrePrincipale::chargerPartie(string nomPartie) {
    ifstream ifs(nomPartie);
    if (!ifs.is_open()) cerr << "Erreur d'ouverture" << endl;
    else {
        ifs.seekg(0, std::ios::beg);//Debut du fichier
        string contenu;
        ifs >> nbCoupsJoues_;
        ifs.ignore();
        ifs >> tempsEcouleSauvegarde_[0];
        ifs.ignore();
        ifs >> tempsEcouleSauvegarde_[1];
        ifs.ignore();
        ifs >> tempsEcouleSauvegarde_[2];
        ifs.ignore();
        for (unsigned int i = 0; i < 16; i++) {
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
        if (!ifs.good()) cerr << "Erreur de lecture du fichier" << nomPartie << endl;
        ifs.close();
    }

}

void FenetrePrincipale::supprimerPartieChargee(const std::string &nomPartie) {
    for (vector<string>::iterator itTab = tableauParties.begin(); itTab != tableauParties.end(); ++itTab) {
        if (*itTab == nomPartie) {
            tableauParties.erase(itTab);
            break;
        }
    }
    if (remove(nomPartie.data()) != 0)
        perror("Error deleting file");
    else
        cout << "File successfully deleted" << endl;
    sauverTableauParties();
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

void FenetrePrincipale::chargerTableauParties() {
    tableauParties.clear();
    ifstream ifs("sauvegardes.txt");
    if (!ifs.is_open()) cerr << "Erreur d'ouverture " << "sauvegardes.txt" << endl;
    else {
        ifs.seekg(0, std::ios::beg);//Debut du fichier
        int taille;
        ifs >> taille;
        ifs.ignore();
        string contenu;
        for (unsigned int i = 0; i < taille; i++) {
            getline(ifs, contenu);
            tableauParties.push_back(contenu);
        }
        if (!ifs.good()) cerr << "Erreur de lecture du fichier sauvegardes.txt" << endl;
        ifs.close();
    }

}

void FenetrePrincipale::sauverTableauParties() {
    ofstream ofs("sauvegardes.txt");
    if (!ofs.is_open()) cerr << "Erreur d'ouverture de " << " sauvegardes.txt" << endl;
    else {
        ofs << tableauParties.size() << endl;
        string contenu;
        for (const auto &tableauPartie : tableauParties) {
            ofs << tableauPartie << endl;
        }
        ofs.close();
    }

}
