#include "pch.h"
#include "Liste.h"


Liste::Liste(list<Carte> LaListe, int taille)
{
	LaListe_ = LaListe;
	taille_ = taille;
}

Liste::Liste() {
}

Liste::~Liste()
{
}
 

void Liste::display() {
	if (LaListe_.empty()) {
		cerr << "affichage liste vide" << endl;
	}
	else {
		list<Carte>::iterator it;
		int i = 0;
		for (it = LaListe_.begin(); it != LaListe_.end();it++) {
			i++;
			cout << " Carte " << i << " : " <<endl;
			it->display();
		}
	}
}