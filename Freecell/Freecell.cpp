// Freecell.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "pch.h"
#include <iostream>
#include "Fonctions.h"
#include "Carte.h"
#include "Liste.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

int main()
{
	//FenetrePrincipale fen;
	Carte MaCarte(Coeur, As);
	CImgDisplay carte(MaCarte, "Carte", 0, false, false);


	//Liste MaListe;
	//MaListe.add(MaCarte);
	//MaListe.display();
	//MaListe.pop();
	MaCarte.display();
	
    // Usefull colors
	return(0);
}

